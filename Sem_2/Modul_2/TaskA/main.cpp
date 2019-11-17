// Задача 1
// Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.
//
// Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
// N ≤ 10000, M ≤ 250000.
// Длина каждой дороги ≤ 10000.
// Решение - алгоритм Дейкстры.
// Алгоритм Дейкстры организован как обход в ширину, только вместо очереди - куча с приоритетом по растояниям до вершин.
// Для каждой вершины будем хранить минимальное растояние до нее, также храним кучу с приоритетом по этим растояниям.
// Изначально для всех вершин растояние бесконечно большое, кроме стартовой.
// На каждом шаге достаем из кучи веришну с минимальным растоянием, смотрим детей этой вершины, и если для какой то из этих
// вершин ее минимальное растояние оказывается больше чем растояние до рассматриваемой вершины + вес ребра между ними, то 
// уменьшаем это растояние и закидываем вершину в кучу.
#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <limits>

class ListGraph {
 private:
  int _number_of_vertex;

  // Для каждой вершины будем хранить списком пар смежные вершины <вес, от какой вершины>
  std::vector<std::list<std::pair<int, int>>> _adjacent_vertices;
 public:

  // Конструктор
  ListGraph(int number_of_vertex)
      : _number_of_vertex(number_of_vertex), _adjacent_vertices(number_of_vertex) {}
      
  // Деструктор будет сгенерирован по умолчанию
  ~ListGraph() = default;

  // Добавление ребра
  void AddEdge(int from, int to, int weight) {
    _adjacent_vertices[from].emplace_back(weight, to);
    _adjacent_vertices[to].emplace_back(weight, from);
  }

  // Возвращаем кол-во вершин
  int VerticesCount() const {
    return _number_of_vertex;
  }

  // Возвращаем вектор смежных вершин c весами
  void GetNextVertices(int vertex, std::vector<std::pair<int, int>> &vertices) const {
    vertices.clear();
    for (std::pair<int, int> i : _adjacent_vertices[vertex]) {
      vertices.push_back(i);
    }
  }
};

// Алгоритм Дейкстры
int FindShortestWay(ListGraph &graph, int from, int to) {
  // Растояние до всех вершин изначально - бесконечность
  const int infinite = std::numeric_limits<int>::max();
  std::vector<int> distant(graph.VerticesCount(), infinite);

  // Куча с приоритетом, храним растояние до вершины(вес) и номер вершины
  // pair = <вес, номер вершины>
  std::set<std::pair<int, int>> priority_queue;
  distant[from] = 0;
  priority_queue.emplace(0, from);
  
  while(!priority_queue.empty()) {
    std::pair<int, int> current_vertex = *priority_queue.begin();
    priority_queue.erase(priority_queue.begin());
    std::vector<std::pair<int, int>> vertices;
    graph.GetNextVertices(current_vertex.second, vertices);
    for (std::pair<int, int> i : vertices) {
    
      // Если можно в эту вершину пройти быстрее, то меняем растояние до нее, и добавляем в очередь
      if (distant[i.second] > current_vertex.first + i.first) {
        priority_queue.erase(std::make_pair(distant[i.second], i.second));
        distant[i.second] = current_vertex.first + i.first;
        priority_queue.emplace(distant[i.second], i.second);
      }
    }
  }
  return distant[to];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  ListGraph graph(n);
  int from, to;
  for (int i = 0; i < m; ++i) {
    int weight;
    std::cin >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }
  std::cin >> from >> to;
  std::cout << FindShortestWay(graph, from, to);
  return 0;
}