// Дан невзвешенный неориентированный граф. Определить, является ли он двудольным. Требуемая сложность O(V+E).
// Ввод: v:кол-во вершин(макс. 50000), n:кол-во ребер(макс. 200000), n пар реберных вершин.
// Вывод: YES если граф является двудольным, NO - если не является.
// Алгоритм решения:
// Для проверки двудольности достаточно в каждой компоненте связности выбрать любую вершину и помечать оставшиеся вершины
// во время обхода графа поиском в ширину поочерёдно как чётные и нечётные.
// Если при этом не возникнет конфликта, все чётные вершины образуют множество U, а все нечётные — V.
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
// Структура для представления вершины
struct Pair {
    int mark = 0;
    bool is_visited = false;
};

// Рассматриваем каждую вершину, если она уже посещена, то ничего не делаем, если нет, то запускаем от неё BFS.
bool IsBipartite(ListGraph &graph) {
    std::vector<Pair> vertices(graph.VerticesCount());
    for (int vertex = 0; vertex < graph.VerticesCount(); ++vertex) {
        if (!vertices[vertex].is_visited) {
            vertices[vertex].is_visited = true;
            std::queue<int> queue;
            queue.push(vertex);

            // BFS от этой вершины
            while (!queue.empty()) {
                int current_vertex = queue.front();
                queue.pop();
                std::vector<int> adjacent_vertices;
                graph.GetAdjacentVertices(current_vertex, adjacent_vertices);
                for (int next_vertex : adjacent_vertices) {
                    if (!vertices[next_vertex].is_visited) {
                        vertices[next_vertex].mark = vertices[current_vertex].mark ^ 1;
                        vertices[next_vertex].is_visited = true;
                        queue.push(next_vertex);
                    } else if (vertices[next_vertex].mark == vertices[current_vertex].mark) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
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
    IsBipartite(graph) ? std::cout << "YES" : std::cout << "NO";
    return 0;
}
