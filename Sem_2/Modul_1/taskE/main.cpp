// Дан ориентированный граф. Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным.
// В графе возможны петли.
// В первой строке указывается число вершин графа V, во второй – число ребер E, в последующих – E пар вершин, задающих ребра.
// Алгоритм:
// 1) Ищем связные компоненты алгоритмом Косарайя
// 2) Считаем каждую компоненту новой цельной вершиной, создаем доп вектор компонент,
// где для каждой компоненты храним входит ли в неё кто нибудь и выходит ли кто нибудь.
// 3) Проходим по всем детям каждой вершины, и если вершина и ее ребенок из разных компонент,
// то ставим true соответсвующие поля в векторе компонент.
// 4) Посчитаем {X} - кол-во компонент, в которые никто не входит, и {Y} - кол-во компонент, из которых никто не выходит.
// Ответом является максимум(X, Y). Меньше быть не может, т к тогда будет существовать компонента, в которую никакая другая компонента
// не входит, или никакая другая не выходит, а значит граф не сильносвязный.
#include <iostream>
#include <vector>
#include <list>

class ListGraph {
private:
    int _number_of_vertex;

    // Для каждой вершины будем хранить списком смежные вершины
    std::vector<std::list<int>> _parents;
    std::vector<std::list<int>> _children;
public:

    // Конструктор
    ListGraph(int number_of_vertex)
            : _number_of_vertex(number_of_vertex), _parents(number_of_vertex), _children(number_of_vertex) {}

    // Деструктор будет сгенерирован по умолчанию
    ~ListGraph() = default;

    // Добавление ребра
    void AddEdge(int from, int to) {
        _children[from].push_front(to);
        _parents[to].push_front(from);
    }

    // Возвращаем кол-во вершин
    int VerticesCount() const {
        return _number_of_vertex;
    }

    // Возвращаем вектор детей
    void GetNextVertices(int vertex, std::vector<int> &vertices) const {
        vertices.clear();
        for (int i : _children[vertex]) {
            vertices.push_back(i);
        }
    }
    // Возвращает вектор родителей
    void GetPrevVertices(int vertex, std::vector<int> &vertices) const {
        vertices.clear();
        for (int i : _parents[vertex]) {
            vertices.push_back(i);
        }
    }
};

// DFS для транспонированного графа(вместо детей идем в родителей), возвращает вектор order - вектор выхода с вершин
void TranspointedDFS(int vertex, ListGraph &graph, std::vector<bool> &is_visited, std::vector<int> &order) {
    is_visited[vertex] = true;
    std::vector<int> vertices;
    graph.GetPrevVertices(vertex, vertices);
    for (int i : vertices) {
        if (!is_visited[i]) {
            TranspointedDFS(i, graph, is_visited, order);
        }
    }
    order.push_back(vertex);
}

// Обычный DFS
void DFS(int vertex,
         ListGraph &graph,
         std::vector<bool> &is_visited,
         std::vector<int> &components,
         int const &current_component) {
    is_visited[vertex] = true;
    components[vertex] = current_component;
    std::vector<int> vertices;
    graph.GetNextVertices(vertex, vertices);
    for (int i : vertices) {
        if (!is_visited[i]) {
            DFS(i, graph, is_visited, components, current_component);
        }
    }
}

// Алгоритм Косарайя. Возвращаем вектор компонент и кол-во компонент.
// Сначала вызывает DFS для транспонированного графа, потом в обратном порядке order обходит DFS вершины.
int Kosaraju(ListGraph &graph, std::vector<int> &components) {
    std::vector<bool> is_visited(graph.VerticesCount());
    std::vector<int> order;
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        if (!is_visited[i]) {
            TranspointedDFS(i, graph, is_visited, order);
        }
    }
    is_visited.assign(graph.VerticesCount(), false);
    int current_component = 0;
    for (int i = order.size() - 1; i >= 0; --i) {
        if (!is_visited[order[i]]) {
            DFS(order[i], graph, is_visited, components, current_component);
            ++current_component;
        }
    }
    return current_component;
}

// Сначала вызываем алгоритм Косарайя, который возвращем кол-во компонент и вектор,
// в котором для каждой вершины хранится в какой она компоненте. Для каждой компоненты храним вектор пар(in, out).
int MakeStronglyConnected(ListGraph &graph) {
    std::vector<int> components(graph.VerticesCount());
    int number_of_components = Kosaraju(graph, components);
    struct Pair {
        bool in = false;
        bool out = false;
    };
    if (number_of_components != 1) {
        std::vector<Pair> strongly_connected_componets(number_of_components);
        for (int i = 0; i < graph.VerticesCount(); ++i) {
            std::vector<int> next_vertices;
            graph.GetNextVertices(i, next_vertices);

            // Смотрим все дочерние вершины данной вершины, если вершина и ее ребенок из разных компонент,
            // то устанавливаем соответствующие компоненты true.
            for (int j : next_vertices) {
                if (components[i] != components[j]) {
                    strongly_connected_componets[components[i]].out = true;
                    strongly_connected_componets[components[j]].in = true;
                }
            }
        }

        // Считаем компоненты, из которых ничего не выходит, и в которые ничего не входит.
        int x = 0, y = 0;
        for (Pair i : strongly_connected_componets) {
            if (!i.in)
                ++x;
            if (!i.out)
                ++y;
        }

        // Возвращаем максимум из них
        return std::max(x, y);
    } else {

        // Если весь граф уже сильносвязный
        return 0;
    }
}

int main() {
    int number_of_vertices, number_of_edges;
    std::cin >> number_of_vertices >> number_of_edges;
    ListGraph graph(number_of_vertices);
    for (int i = 0; i < number_of_edges; ++i) {
        int from, to;
        std::cin >> from >> to;
        if (from != to) {
            graph.AddEdge(--from, --to);
        }
    }
    std::cout << MakeStronglyConnected(graph);
    return 0;
}

