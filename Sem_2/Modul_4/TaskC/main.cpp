// Задано дерево с корнем, содержащее    (1 ≤    ≤ 100 000) вершин,
// пронумерованных от 0 до   −1.
// Требуется ответить на    (1 ≤    ≤ 10 000 000) запросов о наименьшем общем предке для пары вершин.
// Запросы генерируются следующим образом. Заданы числа   1,   2 и числа   ,    и   .
// Числа   3, . . . ,   2   генерируются следующим образом:      = (  ·    −2+  ·    −1+  ) mod   .
// Первый запрос имеет вид ⟨  1,   2⟩. Если ответ на   −1-й запрос равен   , то   -й запрос имеет вид ⟨(  2  −1 +   ) mod   ,   2  ⟩.
// Для решения задачи можно использовать метод двоичного подъёма.
// Для решения задачи будем использовать метод двоичного подъёма.
// Построим таблицу SP[a][i] - вершина, в которой мы окажемся, поднвшись на 2^i шагов.
// Таблица заполняется рекурентно:
// SP[a][i] = SP[SP[a][i-1][i-1], i > 0; родитель при i = 0;
// Чтобы отвечать на запросы, на каждом шаге будем подниматься на максимальное 2^k шагов, такое, что
// при таком подьеме SP[a][k] не является предком b.
// Заметим, что k может только строго уменьшаться, уменьшение следует из того, что берем максималное,
// строгое уменьшение, из того, что 2^k + 2^k = 2^(k+1)
// Если на каком то шаге такого k найти нельзя, то значит, что родитель a(поднимаемся от a)
// и является наименьшим общим предком.
#include <iostream>
#include <vector>
#include <cmath>

// Считаем логарифм с округлением вверх
unsigned Log(unsigned long n) {
    unsigned ans = 0;
    unsigned current = n;
    while (current > 0) {
        current >>= 1;
        ++ans;
    }
    return n == (1 << (ans - 1)) ? ans - 1 : ans;
}

// Класс для генирации следующего запроса, если предпосчитать сразу все a[i],
// то memory limit
// a[i] = (x * a[i-2] + y * a[i-1] + z) % n)
// Запрос генерируется так:
// <(a[2i-1] + prev_result) % n, a[2i]>
class NextQuery{
private:
    unsigned _a, _b, _n;
    unsigned long _x, _y, _z;
public:
    NextQuery(unsigned a, unsigned b, unsigned long x,
              unsigned long y, unsigned long z, unsigned n) :
            _a(a), _b(b), _x(x), _y(y), _z(z), _n(n) {}

    std::pair<unsigned, unsigned> operator()(unsigned result){
        // считаем запрос
        std::pair<unsigned, unsigned> ans((_a + result) % _n, _b);
        // Обновляем a[i], a[i+1]
        _a = (_a * _x + _b * _y + _z) % _n;
        _b = (_b * _x + _a * _y + _z) % _n;
        return ans;
    }
};

// LCA - поиск наименьшего общего предка, подробнее - далее в описаниях функций
class LCA{
private:
    // Счетчик для обхода в глубину и проверки IsAncestor
    unsigned _time = 0;
    size_t _size;
    unsigned _size_of_sp;
    // Для каждой вершины хранит детей
    std::vector<std::vector<int>>& _matrix;
    // Время входа в каждую вершину в DFS
    std::vector<unsigned> _in;
    // Время выхода
    std::vector<unsigned> _out;
    // SP[a][i] хранит вершину, в которую попадем при подьеме на 2^i шагов
    std::vector<std::vector<unsigned>> _sparse_table;

    // DFS и препроцессинг, заполняем табличку
    void DFS(unsigned node, unsigned parent) {
        // Время входа в данную вершину, время увеличиваем на 1
        _in[node] = _time++;
        // Ставим родителя на этом шаге
        _sparse_table[node][0] = parent;
        // Рекурентно считаем куда попадаем на 2^i подьеме
        // SP[a][i] = SP[SP[a][i - 1]][i - 1]
        for (int i = 1; i <= _size_of_sp; i++)
            _sparse_table[node][i] = _sparse_table[_sparse_table[node][i - 1]][i - 1];
        // Запускаем DFS для детей
        for (int i = 0; i < _matrix[node].size(); ++i) {
            unsigned to = _matrix[node][i];
            if (to != parent)
                DFS(to, node);
        }
        // Фиксируем время выхода
        _out[node] = _time++;
    }
    // a будет предком b если в a при DFS зашли раньше, а вышли позже
    bool IsAncestor(unsigned a, unsigned b) {
        return _in[a] <= _in[b] && _out[b] <= _out[a];
    }
public:
    LCA(std::vector<std::vector<int>>& parents) :
            _matrix(parents), _size(parents.size()),
            _size_of_sp(Log(_size)),
            _in(_size), _out(_size),
            _sparse_table(_size, std::vector<unsigned>(_size_of_sp + 1))
    {
        DFS(0, 0);
    }

    // Ищем онаименьшего общего предка методом двоичного подьема.
    // Хотим подниматься на максимально возможное 2^k такое, что
    // при таком подьеме по ветке a всё равно не является предком для b.
    // Заметим, что на каждом следующем шаге k строго уменьшается.
    // Это потому, что на каждом шаге мы ищем максимальное такое k, и если бы
    // на каком-то шаге k не изменилось, то мы могли бы сделать сразу шаг 2^k + 2^k = 2^(k+1).
    // Тогда будем в от i = log2(n) до i=0 идти, и пробовать поднятся на 2^i шагов.
    // Если это возможно, то a = SP[a][i].
    // Если на каком то шаге невозможно найти такое k, что a = SP[a][k] не является предком для b,
    // причем само a тоже не является предком для b, это значит, что предок a является наименьшим общим предком.
    // Так как k строго уменьшается, мы перебрали все k в цикле, то в конце останется именно то a, чей предок является искомым.
    unsigned LeastCommonAncestor(unsigned a, unsigned b) {
        if (IsAncestor(a, b))
            return a;
        if (IsAncestor(b, a))
            return b;
        for (int i = _size_of_sp; i >= 0; --i)
            if (!IsAncestor(_sparse_table[a][i], b))
                a = _sparse_table[a][i];
        return _sparse_table[a][0];
    }
};

int main() {
    unsigned n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> parents(n);
    for (int i = 1; i < n; i++) {
        unsigned parent;
        std::cin >> parent;
        parents[parent].push_back(i);
    }
    unsigned a, b;
    unsigned long x, y, z;
    std::cin >> a >> b >> x >> y >> z;
    NextQuery nextQuery(a, b, x, y, z, n);
    LCA lca(parents);
    unsigned long answer = 0;
    unsigned result = 0;
    for (int i = 0; i < m; i++) {
        std::pair<unsigned, unsigned> current = nextQuery(result);
        result = lca.LeastCommonAncestor(current.first, current.second);
        answer += result;
    }
    std::cout << answer;
    return 0;
}
