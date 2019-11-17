// 2_2. Последовательность единиц. Дан массив из нулей и единиц a0, a1, ..., an-1.
// Для каждого запроса [left, right] найдите такой подотрезок al, al+1, ..., ar  этого массива (0 <= left <= l <= r  <= right < n),
// что числа al, al+1, …,  ar являются максимально возможной последовательностью единиц.
// Требуемое время ответа на запрос - O(log n).
// Построим дерево отрезков. Чтобы длина последовательности была равна степени двойки заполняем нулями в конце.
// СNode - вершины этого дерева, которые хранят длина подотрезка, длину префикса единиц - максимальное число единиц, идущих с начала этого отрезка
// Длину суффикса, и длину максимально возможной последовательности единиц на этом отрезке.
// Заполнять дерево будем рекурентно. Для листьев - это просто один символ последовательности.
// Далее для i-го элемента считаем так:
// Для детей [2 * i + 1] и [2 * i + 2] уже посчитано.
// Длина - сумма длин.
// Префикс - если левый ребенок состоит целиком из единиц, то добавляем к префиксу его длину, если нет, то длина префикса левого ребенка.
// Суффикс соответственно также, только через правого ребенка.
// Максимальная длина последовательности единиц - максимум из максимумов детей и префикса левого + суффикс второго.
// Таким образом заполняется дерево отрезков.
// Далее чтобы отвечать на запросы будем идти снизу вверх по дереву отрезков.
// Начинаем с листьев которые отвечают границам отрезка.
// Будем хранить ответ для левого указателя и для правого отдельно.
// Если на текущем шаге левый указатель является правым ребенком, то учитываем его в ответ, присоединяя к нему справа
// если правый указатель является левым ребенком, то тоже учитываем его в свой ответ слева.
// Поднимаеся на уровень выше: left /= 2, right = (right - 2) / 2.
// Делаем это пока левый указатель не сравняется с правым.
// Потом левый ответ присоединяем справа к вершине в которой сравнялись указатели, потом присоединяем всё это слева к правому ответу.
#include <iostream>
#include <vector>

// Логарифм с округлением вверх
int Log(unsigned long n) {
    unsigned ans = 0;
    unsigned current = n;
    while (current > 0) {
        current >>= 1;
        ++ans;
    }
    return n == (1 << (ans - 1)) ? ans - 1 : ans;
}

struct CNode{
    int length = 0;
    int prefix = 0;
    int suffix = 0;
    int max_length = 0;
};
// Строим рекурсией сверху
void BuildTree(const std::vector<int> &a, std::vector<CNode> &tree, int i, int left, int right) {
    if (left == right)
        return;
    // Когда дошли до листа
    if (right - left == 1) {
        tree[i].length = 1;
        tree[i].max_length = a[left];
        tree[i].prefix = a[left];
        tree[i].suffix = a[left];
    } else {
        // Если это не лист то бьём еще на два отрезка, считаем для них рекурсивно
        int middle = (left + right) / 2;
        BuildTree(a, tree, 2 * i + 1, left, middle);
        BuildTree(a, tree, 2 * i + 2, middle, right);
        // Теперь слияем эти отрезки
        // Длина - сумма длин
        tree[i].length = tree[2 * i + 1].length + tree[2 * i + 2].length;
        // Максимальная длина - макс(макс левого, макс правого, суфф левого + преф правого)
        tree[i].max_length = std::max(std::max(tree[2 * i + 1].max_length, tree[2 * i + 2].max_length), tree[2 * i + 1].suffix + tree[2 * i + 2].prefix);
        // Длина префикса - либо длина префикса левого, либо если левый полностью из единиц, то длина префикса левого и суффикса правого
        if (tree[2 * i + 1].prefix == tree[2 * i + 1].length) {
            tree[i].prefix = tree[2 * i + 1].prefix + tree[2 * i + 2].prefix;
        } else {
            tree[i].prefix = tree[2 * i + 1].prefix;
        }
        // Тоже самое для суффикса
        if (tree[2 * i + 2].suffix == tree[2 * i + 2].length) {
            tree[i].suffix = tree[2 * i + 1].suffix + tree[2 * i + 2].suffix;
        } else {
            tree[i].suffix = tree[2 * i + 2].suffix;
        }
    }
}

// Ищем максимальную длину
int MaxLength(const std::vector<CNode> &tree, int left, int right) {
    CNode left_answer;
    CNode right_answer;
    while (left < right) {
        // Если left - правый сын своего родителя, учитываем его
        if (left % 2 == 0){
            left_answer.length += tree[left].length;
            left_answer.max_length = std::max(std::max(left_answer.max_length, tree[left].max_length), tree[left].prefix + left_answer.suffix);
            if (tree[left].suffix == tree[left].length) {
                left_answer.suffix += tree[left].suffix;
            } else {
                left_answer.suffix = tree[left].suffix;
            }
        }
        // Если right - левый сын
        if (right % 2 == 1) {
            right_answer.length += tree[right].length;
            right_answer.max_length = std::max(std::max(right_answer.max_length, tree[right].max_length), tree[right].suffix + right_answer.prefix);
            if (tree[right].prefix == tree[right].length) {
                right_answer.prefix += tree[right].prefix;
            } else {
                right_answer.prefix = tree[right].prefix;
            }
        }
        left /= 2;
        right = (right - 2) / 2;
    }
    // Момент когда правый и левый сливаются в одно, это присоединяем справа к left_answer и слева к right_answer
    left_answer.length += tree[left].length;
    left_answer.max_length = std::max(std::max(left_answer.max_length, tree[left].max_length), tree[left].suffix + left_answer.prefix);
    if (tree[left].prefix == tree[left].length) {
        left_answer.prefix += tree[left].prefix;
    } else {
        left_answer.prefix = tree[left].prefix;
    }
    left_answer.max_length = std::max(std::max(left_answer.max_length, right_answer.max_length), left_answer.suffix + right_answer.prefix);
    return left_answer.max_length;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    // Чтобы последовательность была длины степени двойки дополняем ее нулями в конце
    std::vector<int> a(1 << Log(n));
    std::vector<CNode> tree(1 << (Log(n) + 1));
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    BuildTree(a, tree, 0, 0, 1 << Log(n));
    int left = 0, right = 0;
    for (int i = 0; i < m; ++i) {
        std::cin >> left >> right;
        left += (1 << Log(n)) - 1;
        right += (1 << Log(n)) - 1;
        std::cout << MaxLength(tree, left, right) << std::endl;
    }
    return 0;
}