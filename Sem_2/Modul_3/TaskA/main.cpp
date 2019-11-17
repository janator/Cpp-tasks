// Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
// Вариант 1. С помощью алгоритма Прима.
// Алгоритм Прима выбирает на каждом шаге ребро минимального веса, из вершин, которые уже в остове, в вершины, которые нет.
// Чтобы находить минимум каждый раз, будем для каждой вершины хранить вес минимального ребра, ведущего из неё в остов.
// Для этого при выборе вершины, смотрим все вершины, соединенные с ней, и если вес ребра меньше, то обновляем мин растояние для этой вершины.
// После этого добавляем эту вершину в сет пар <мин раст, номер вершины>.
#include <iostream>
#include <vector>
#include <set>
const int INF = 10000000;

long long AlgorithmPrima(std::vector<std::vector<std::pair<int, int>>> &graph) {
    // Вектор минимальных растояний, изначально для всех вершин INF
    std::vector<int> min_e(graph.size(), INF);
    // Вектор посещений
    std::vector<char> visited(graph.size(), 0);
    min_e[0] = 0;
    int answer = 0;
    // Очередь
    std::set<std::pair<int, int>> queue;
    queue.insert(std::make_pair(0, 0));
    int num_of_visited = 0;
    // Пока не наберем n веершин
    while (num_of_visited < graph.size()) {
        std::pair<int, int> vertex = *queue.begin();
        queue.erase(queue.begin());
        if (visited[vertex.second] == 0) {
            answer += vertex.first;
            for (std::pair<int, int> j : graph[vertex.second]) {
                if (visited[j.first] == 0) {
                    if (j.second < min_e[j.first]) {
                        queue.erase(std::make_pair(min_e[j.first], j.first));
                        min_e[j.first] = j.second;
                        queue.insert(std::make_pair(min_e[j.first], j.first));
                    }
                }
            }
            ++num_of_visited;
            visited[vertex.second] = 1;
        }
    }
    return answer;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::pair<int, int>>> graph(n);
    int from, to, weight;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from].emplace_back(to, weight);
        graph[to].emplace_back(from, weight);
    }
    std::cout << AlgorithmPrima(graph);
    return 0;
}
