#include <iostream>
#include <vector>
// В одном из отделов крупной организации работает n человек.
// Как практически все сотрудники этой организации,
// они любят пить чай в перерывах между работой.
// При этом они достаточно дисциплинированы и делают в день ровно один перерыв,
// во время которого пьют чай. Для того, чтобы этот перерыв был максимально приятным,
// каждый из сотрудников этого отдела обязательно пьет чай одного из своих любимых сортов.
// В разные дни сотрудник может пить чай разных сортов.
// Для удобства пронумеруем сорта чая числами от 1 до m.
// Недавно сотрудники отдела купили себе большой набор чайных пакетиков,
// который содержит a1 пакетиков чая сорта номер 1, a2 пакетиков чая сорта номер 2, ..., am
// пакетиков чая сорта номер m.
// Теперь они хотят знать, на какое максимальное число дней им может хватить купленного набора так,
// чтобы в каждый из дней каждому из сотрудников доставался пакетик чая одного из его любимых сортов.
// Каждый сотрудник отдела пьет в день ровно одну чашку чая, которую заваривает из одного пакетика.
// При этом пакетики чая не завариваются повторно.

// Решение:
// Будем искать максимум бин поиском. Т к если макс число дней n, то люди могут пить чай n - 1 день, и не могут n + 1.
// Будем хранить две границы left и right, и проверять с помощью алгоритма Диницы могут ли люди пить чай (left + right)/2 дней.
// Если могут то сдвигаем левую границу, если нет то правую.
// Для проверки могут ли люди пить чай n дней сделаем граф.
// исток -> люди -> их предпочтения в чае -> сток. Причем ребра из истока в людей идут с пропускной способностью равной
// кол-ву дней, из людей в чаи с пропускной способностью INF, из чаёв в сток с пропускной способностью равной кол-ву пакетиков.
// Тогда если максимальный поток будет равен кол-во людей * кол-во дней, то они могут пить чай столько дней.
// Алгоритм Диницы взят из предыдущей задачи.

const int INF = 1000000000; // константа-бесконечность
const int MAXDAYS = 100000000;
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

bool CanDrink(int num_of_days, std::vector<std::vector<int>> &graph, std::vector<Edge> &edges, int n) {
    // ставим пропускную способность для ребер соединяющих исток с людьми равной кол-во дней
    for (int i = 0; i < 2 * n; i+=2) {
        edges[i].capacity = num_of_days;
    }
    for (int i = 0; i < edges.size(); ++i) {
        edges[i].flow = 0;
    }
    return Dinic(graph, edges) == n * num_of_days;
}


int CountNumberOfDays(std::vector<std::vector<int>> &graph, std::vector<Edge> &edges, int n) {
    int left = 0;
    int right = MAXDAYS;
    while (right - left > 1) {
        int middle = (right + left) / 2;
        if (CanDrink(middle, graph, edges, n)) {
            left = middle;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> graph(n + m + 2);
    // соединяем исток с людьми пока что ребрами с нулевой пропускной способностью
    for (int i = 1; i <= n; ++i) {
        AddEdge(0, i, 0, graph, edges);
    }
    // считываем кол-во пакетиков и соединяем пакетики со стоком
    int num_of_bags;
    for (int i = 1; i <= m; ++i) {
        std::cin >> num_of_bags;
        AddEdge(n + i, n + m + 1, num_of_bags, graph, edges);
    }
    // устанавливаем связи между людьми и пакетиками
    int from, to, num_of_tea, k;
    for (int i = 1; i <= n; ++i) {
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            std::cin >> num_of_tea;
            AddEdge(i, n + num_of_tea, INF, graph, edges);
        }
    }
    std::cout << CountNumberOfDays(graph, edges, n);
    return 0;
}