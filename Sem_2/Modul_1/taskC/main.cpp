// Задача B
// Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины.
// Ввод: v:кол-во вершин(макс. 50000), n:кол-во ребер(макс. 200000), n пар реберных вершин
// Вывод: одно целое число равное длине минимального цикла. Если цикла нет, то вывести -1.
#include <iostream>
#include <vector>
#include <list>
#include <queue>

class ListGraph {
private:
    int _number_of_vertex;

    // Для каждой вершины будем хранить список смежных вершины
    std::vector<std::list<int>> _adjacent_vertices;
public:
    // Конструктор
    ListGraph(int number_of_vertex);

    ~ListGraph();

    void AddEdge(int from, int to);
    int VerticesCount() const;

    void GetAdjacentVertices(int vertex, std::vector<int> &vertices) const;
};

// Создадим структуру, в которой будет хранится растояние в обходе до вершины, предыдущая вершина(отец), и посещена/не посещена
struct Vertex {
    int distance = 0;
    int previous;
    bool is_visited = false;
};

// Если запустим этот BFS от вершины, которая находится в минимальном цикле, то функция вернет длину этого цикла.
// Однако если вершина не находится в цикле, то функция вернет длину > длины цикла
// Если вершина не рассматривалась, то растояние в обходе до нее = растояние до предыдущей + 1, если вершина рассматривала,
// то проверяем не является ли эта вершина предыдущей для текущей вершины, т к граф неориентированный, и если нет,
// то мы нашли цикл.
int BFS(int vertex, ListGraph &graph) {
    std::vector<Vertex> vertices(graph.VerticesCount());
    std::queue<int> queue;
    queue.push(vertex);
    vertices[vertex].is_visited = true;
    while (!queue.empty()) {
        int current_vertex = queue.front();
        queue.pop();
        std::vector<int> next_vertices(graph.VerticesCount());
        graph.GetAdjacentVertices(current_vertex, next_vertices);
        for (int next_vertex : next_vertices) {
            if (!vertices[next_vertex].is_visited) {
                vertices[next_vertex].distance = vertices[current_vertex].distance + 1;
                vertices[next_vertex].previous = current_vertex;
                vertices[next_vertex].is_visited = true;
                queue.push(next_vertex);
            } else if (vertices[current_vertex].previous != next_vertex) {
                return vertices[current_vertex].distance + 1 + vertices[next_vertex].distance;
            }
        }
    }
    return graph.VerticesCount() + 1;
}

// Запустим BFS от каждой вершины, и среди возвращенных циклов найлем минимальный
int FindMinCycle(ListGraph &graph) {
    int min_cycle = graph.VerticesCount() + 1;
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        min_cycle = std::min(BFS(i, graph), min_cycle);
    }
    return min_cycle != graph.VerticesCount() + 1 ? min_cycle : -1;
}

int main() {
    int number_of_vertices, number_of_edges;
    std::cin >> number_of_vertices >> number_of_edges;
    ListGraph graph(number_of_vertices);
    for (int i = 0; i < number_of_edges; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    std::cout << FindMinCycle(graph);
    return 0;
}

// ----------------------------------------------------------------------------------
// Реализация графа
// Деструктор будет сгенерирован по умолчанию, т к нет динамического выделения памяти
ListGraph::~ListGraph() = default;

ListGraph::ListGraph(int number_of_vertex)
        : _number_of_vertex(number_of_vertex), _adjacent_vertices(number_of_vertex) {}

// Возвращает кол-во вершин
int ListGraph::VerticesCount() const {
    return _number_of_vertex;
}

// Возвращаем вектор сo смежными вершинами
void ListGraph::GetAdjacentVertices(int vertex, std::vector<int> &vertices) const {
    vertices.clear();
    for (int i : _adjacent_vertices[vertex]) {
        vertices.push_back(i);
    }
}

// Добавление ребра
void ListGraph::AddEdge(int from, int to) {
    _adjacent_vertices[from].push_front(to);
    _adjacent_vertices[to].push_front(from);
}
