// Полный ориентированный взвешенный граф задан матрицей смежности.
// Постройте матрицу кратчайших путей между его вершинами.
// Гарантируется, что в графе нет циклов отрицательного веса.
// Решение - динамический алгоритм Флойда.
// Заведем матрицу d, d(k, i, j) - кратчайший путь от i к j проходящий через k.
// d(0, i, j) - вес ребра (i, j). Тогда на каждом шаге заполняем таблицу:
// d(k, i, j) = min(d(k - 1, i, j), d(k - 1, i, k) + d(k - 1, k, j)), т е
// либо кратчайший путь не проходит через k, либо проходит и тогда равен сумме от i до k, и от k до j.
#include <iostream>
#include <vector>

class MatrixGraph {
private:
    int _number_of_vertex;
    std::vector<std::vector<int>> _edges;
public:
    // Деструктор будет сгенерирован по умолчанию, т к нет динамического выделения памяти
    ~MatrixGraph() = default;

    // Конструктор
    MatrixGraph(int number_of_vertex) :
            _number_of_vertex(number_of_vertex),
            _edges(number_of_vertex) {
        for (int i = 0; i < number_of_vertex; ++i) {
            _edges[i].resize(number_of_vertex, -1);
        }
    }

    // Добавление ребра в матрицу
    void AddEdge(int from, int to, int weight) {
        _edges[from][to] = weight;
    }

    // Возвращает кол-во вершин
    int VerticesCount() const {
        return _number_of_vertex;
    }

    // Возращает вектор весов для всех вершин
    void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        vertices.clear();
        for (int i : _edges[vertex]) {
            vertices.push_back(i);
        }
    }

    friend std::istream &operator>>(std::istream &in, MatrixGraph &graph) {
        for (int i = 0; i < graph._number_of_vertex; ++i) {
            for (int j = 0; j < graph._number_of_vertex; ++j) {
                in >> graph._edges[i][j];
            }
        }
        return in;
    }
};

// Алгоритм Флойда
void Floyd(MatrixGraph &graph, std::vector<std::vector<int>> &short_distance) {
    // копируем матрицу смежности
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        graph.GetNextVertices(i, short_distance[i]);
    }
    for (int k = 0; k < graph.VerticesCount(); ++k) {
        for (int i = 0; i < graph.VerticesCount(); ++i) {
            for (int j = 0; j < graph.VerticesCount(); ++j) {
                short_distance[i][j] = std::min(short_distance[i][j], short_distance[i][k] + short_distance[k][j]);
            }
        }
    }
}
int main() {
    int n;
    std::cin >> n;
    MatrixGraph graph(n);
    std::cin >> graph;
    std::vector<std::vector<int>> short_distance(n);
    Floyd(graph, short_distance);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cout << short_distance[i][j] << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}