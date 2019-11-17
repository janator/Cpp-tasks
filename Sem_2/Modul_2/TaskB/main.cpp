// Необходимо написать торгового советника для поиска арбитража.
// Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах.
// Например, есть следующие курсы валют:
// GBP/USD: 0.67
// RUB/GBP: 78.66
// USD/RUB: 0.02
// Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4
// Время работы – O(VE).
// Решение - алгоритм Беллмана-Форда
// Арбитраж существует, если существует отрицательный цикл, в нашем случае цикл, в котором будет увеличиваться прибыль.
// Заведем массив кратчайших растояний d, в нашем случае это растояние - наибольшая возможная выгода для валюты.
// Граф может быть несвязным, поэтому запускаем от каждой вершины.
// В массиве d ставим все значения -1, а текущей стартовой вершине 1.
// На каждой фазе просматривам все ребра графа, и по возможности увеличиваем значения для валют.
// Т е если для ребра (a, b) значение d[b] < d[a] *c, то увеличиваем значение d[b].
// Если отричательного цикла нет, то достаточно n - 1 итерации алгоритма. Если же цикл есть, то при n итерации значение
// арбитража для какой нибудь вершины увеличится.
#include <iostream>
#include <vector>

class MatrixGraph {
private:
    int _number_of_vertex;
    std::vector<std::vector<double>> _edges;
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
    void AddEdge(int from, int to, double weight) {
        _edges[from][to] = weight;
    }

    // Возвращает кол-во вершин
    int VerticesCount() const {
        return _number_of_vertex;
    }

    // Возвращаем предыдущие вершины и вес
    void GetPrevVertices(int vertex, std::vector<std::pair<int, double>> &vertices) const {
        vertices.clear();
        for (int i = 0; i < _number_of_vertex; ++i) {
            if (_edges[i][vertex] != -1) {
                vertices.emplace_back(i, _edges[i][vertex]);
            }
        }
    }
};

// Воспользуемся алгоритмом Беллмана — Форда для поиска отрицательных циклов.
bool IsArbitrageTrade(MatrixGraph &graph) {

    // Делаем старт от каждой вершины, потому что граф может быть несвязным
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<double> arbitrage(graph.VerticesCount(), -1);
        arbitrage[i] = 1;

        // n - 1 итерация цикла
        for (int j = 0; j < graph.VerticesCount() - 1; ++j) {

            // Перебираем все ребра, считаем арбитражы для каждой вершины
            for (int vertex = 0; vertex < graph.VerticesCount(); ++vertex) {
                std::vector<std::pair<int, double>> vertices;
                // Расматриваем не следующие вершины, а предыдущие, если из какой то вершины можно выгоднее получить
                // значение для текущей, то увеличиваем значение
                graph.GetPrevVertices(vertex, vertices);
                for (std::pair<int, double> prev_vertex : vertices) {
                    if (arbitrage[prev_vertex.first] != -1
                        && arbitrage[vertex] < arbitrage[prev_vertex.first] * prev_vertex.second)
                        arbitrage[vertex] = arbitrage[prev_vertex.first] * prev_vertex.second;
                }
            }
        }

        // Если при этой итерации какой то путь уменьшится(в нашем случае значение арбитража увеличится), то такой цикл есть
        for (int vertex = 0; vertex < graph.VerticesCount(); ++vertex) {
            std::vector<std::pair<int, double>> vertices;
            graph.GetPrevVertices(vertex, vertices);
            for (std::pair<int, double> prev_vertex : vertices) {
                if (arbitrage[prev_vertex.first] != -1 && arbitrage[vertex] < arbitrage[prev_vertex.first] * prev_vertex.second)
                    return true;
            }
        }
    }
    return false;
}

int main() {
    int n;
    std::cin >> n;
    MatrixGraph graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                double weight;
                std::cin >> weight;
                graph.AddEdge(i, j, weight);
            }
        }
    }
    IsArbitrageTrade(graph) ? std::cout << "YES" : std::cout << "NO";
    return 0;
}