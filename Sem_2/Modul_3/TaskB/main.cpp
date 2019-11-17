#include <iostream>
#include <vector>
// Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью.
// Найдите максимальный поток из вершины с номером 1 в вершину с номером n
// 2 вариант - с помощью алгоритма Диницы
// Алгоритм Диницы:
// 1) Ставим везде поток 0.
// 2) Строим слоистую сеть обходом в ширину, если ее нельзя построить, то макс поток найден
// 3) Ищем блокирующий поток в слоистой сети с помощью DFS
// 4) Добавляем этот поток в граф, переходим к шагу 2.

const int INF = 1000000000; // константа-бесконечность

struct Edge {
    int from;
    int to;
    int capacity;
    int flow;
};

void AddEdge(int from, int to, int capacity, std::vector<std::vector<int>> &graph, std::vector<Edge> &edges) {
    Edge e1 = {from, to, capacity, 0};
    Edge e2 = {to, from, 0, 0};
    // graph - список смежности, но хранит не сами ребра, и не номер ребенка, а индекс ребра в массиве всех ребер
    graph[from].push_back((int) edges.size());
    edges.push_back(e1);
    graph[to].push_back((int) edges.size());
    edges.push_back(e2);
}

bool BFS(std::vector<std::vector<int>> &graph, std::vector<int> &layered_net, std::vector<Edge> &edges) {
    std::vector<int> queue(graph.size());
    // qt увеличиваем только когда добавляем в обход, qh увеличиваем когда просматриваем вершины уже в обходе
    int qh = 0, qt = 0;
    queue[qt++] = 0;
    // массив слоёв
    layered_net.assign(graph.size(), -1);
    // исток на 0 слое
    layered_net[0] = 0;
    while (qh < qt && layered_net[graph.size() - 1] == -1) {
        // следующая по очереди
        int vertex = queue[qh++];
        // смотрим все вершины выходящие из vertex
        for (size_t i = 0; i < graph[vertex].size(); ++i) {
            // to - куда
            int id = graph[vertex][i],
                    to = edges[id].to;
            // если не посещена и не насыщена
            if (layered_net[to] == -1 && edges[id].flow < edges[id].capacity) {
                // добавляем в очередь
                queue[qt++] = to;
                // ставим значение слоя + 1
                layered_net[to] = layered_net[vertex] + 1;
            }
        }
    }
    return layered_net[graph.size() - 1] != -1;
}

int DFS(int vertex,
        int flow,
        std::vector<std::vector<int>> &graph,
        std::vector<Edge> &edges,
        std::vector<int> &ptr,
        std::vector<int> &layered_net) {
    if (!flow) return 0;
    // если дошли до стока
    if (vertex == graph.size() - 1) return flow;
    // смотрим все исходящие вершины
    for (; ptr[vertex] < graph[vertex].size(); ++ptr[vertex]) {
        // смотрим ребенка
        int id = graph[vertex][ptr[vertex]],
                to = edges[id].to;
        // если это не следующий слой то пропускаем и смотрим след ребенка
        if (layered_net[to] != layered_net[vertex] + 1) continue;
        // рекурсивно вызываем
        int pushed = DFS(to, std::min(flow, edges[id].capacity - edges[id].flow), graph, edges, ptr, layered_net);
        // если не нулем пробили то добавляем поток
        if (pushed) {
            edges[id].flow += pushed;
            // обратное ребро
            edges[id + 1].flow -= pushed;
            return pushed;
        }
    }
    return 0;
}

int Dinic(std::vector<std::vector<int>> &graph, std::vector<Edge> &edges) {
    int flow = 0;
    std::vector<int> layered_net(graph.size());
    std::vector<int> ptr(graph.size());
    for (;;) {
        // строим слоистую сеть, насыщенные ребра не включаем
        if (!BFS(graph, layered_net, edges)) break;
        // массив, считающий кол-во уже проверенных ребер-детей для каждой вершины
        ptr.assign(graph.size(), 0);
        // пока что то можно пропихнуть
        while (int pushed = DFS(0, INF, graph, edges, ptr, layered_net))
            flow += pushed;
    }
    return flow;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> graph(n);
    int from, to, capacity;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> capacity;
        AddEdge(--from, --to, capacity, graph, edges);
    }
    std::cout << Dinic(graph, edges);
    return 0;
}