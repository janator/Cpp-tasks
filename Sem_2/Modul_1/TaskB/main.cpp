// Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
// Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
// Ввод: v:кол-во вершин(макс. 50000), n:кол-во ребер(макс. 200000), n пар реберных вершин, пара вершин v, w для запроса.
// Вывод:количество кратчайших путей от v к w
#include <iostream>
#include <vector>
#include <list>
#include <queue>
class ListGraph {
private:
    int _number_of_vertex;

    // Для каждой вершины будем хранить списком смежные вершины
    std::vector<std::list<int>> _adjacent_vertices;
public:

    // Конструктор
    ListGraph(int number_of_vertex)
            : _number_of_vertex(number_of_vertex), _adjacent_vertices(number_of_vertex) {}
    // Деструктор будет сгенерирован по умолчанию
    ~ListGraph() = default;
    // Добавление ребра
    void AddEdge(int from, int to) {
        _adjacent_vertices[from].push_front(to);
        _adjacent_vertices[to].push_front(from);
    }

    // Возвращаем кол-во вершин
    int VerticesCount() const {
        return _number_of_vertex;
    }

    // Возвращаем вектор смежных вершин
    void GetAdjacentVertices(int vertex, std::vector<int> &vertices) const {
        vertices.clear();
        for (int i : _adjacent_vertices[vertex]) {
            vertices.push_back(i);
        }
    }
};

struct Pair {
    int number_of_paths = 0;
    int distance = 0;
};

// Функция для подсчета кратчайших путей
// В векторе vertices будем хранить кол-во кратчайших путей до данной вершины от стартовой вершины
// и растояние от стартовой вершины.
// Будем обходить граф в ширину
// Если видим вершину в первый раз, то ставим кол-во путей до нее равное кол-ву путей до ее родителя, растояние на один больше
// и добавляем ее в очередь вызовов.
// Если вершины уже была рассмотрена, проверяем растояние до нее, и в зависимости от этого добавляем кол-во путей.
int CountPath(int from, int to, ListGraph &graph) {
    std::vector<Pair> vertices(graph.VerticesCount());
    std::queue<int> queue;
    queue.push(from);
    vertices[from].number_of_paths = 1;

    while (!queue.empty()) {
        std::vector<int> next_vertices;
        int current_vertex = queue.front();
        queue.pop();
        graph.GetAdjacentVertices(current_vertex, next_vertices);
        for (int i : next_vertices) {
            if (vertices[i].number_of_paths == 0) {
                vertices[i].number_of_paths = vertices[current_vertex].number_of_paths;
                vertices[i].distance = vertices[current_vertex].distance + 1;
                queue.push(i);
            } else if (vertices[i].distance == vertices[current_vertex].distance + 1) {
                vertices[i].number_of_paths += vertices[current_vertex].number_of_paths;
            }
        }
    }
    return vertices[to].number_of_paths;
}

int main() {
    int number_of_vertices, number_of_edges;
    std::cin >> number_of_vertices;
    ListGraph graph(number_of_vertices);
    std::cin >> number_of_edges;

    // Считываем граф
    for (int i = 0; i < number_of_edges; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    int from, to;
    std::cin >> from >> to;
    std::cout << CountPath(from, to, graph);
    return 0;
}


