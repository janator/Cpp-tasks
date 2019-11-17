#include <iostream>
#include <vector>
#include <algorithm>
// Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.
// Для решения задачи используйте структуру данных Sparse Table.
// Требуемое время обработки каждого диапазона O(1).
// Время подготовки структуры данных O(n log n).
// Алгоритм:
// Решать задачу будем как для минимального числа на отрезке, только для каждого отрезка
// Будем хранить не минимум, а два минимальных элемента.
// Препроцессинг:
// Заполняем таблицу пар, для отрезков длины один оба значения в паре - одно и то же число
// ST[i][j] = min(a[i] ... a[i + 2^j - 1])
// Заполняем рекурентно: ST[i][j] = min(ST[i - 1][j], ST[j + 2^(i - 1)][j - 1])
// Теперь чтобы найти минимум на любом отрезке:
// min(ST[k][l], ST[k][r - 2^k + 1]), где k = log(r - l) - 1
// Здесь min - это минимальные два элемента из двух пар.

// Функция выбора минимальных двух различных элементов из четырех
std::pair<int, int> getMinPair(std::pair<int, int> a, std::pair<int, int> b) {
    std::pair<int, int> ans;
    std::vector<int> helper{a.first, a.second, b.first, b.second};
    std::sort(helper.begin(), helper.end());
    // Берем первый элемент и следующий не равный ему
    ans.first = helper[0];
    for (int i = 1; i < 4; ++i) {
        if (helper[i] != helper[0]) {
            ans.second = helper[i];
            return ans;
        }
    }
};

// Инициализируем логарифм, чтобы каждый раз не считать логарифм, предпосчитаем для каждого числа <= n
// Логарифм берем с округлением вверх, т е в цикле идем и заполняем 2^k чисел значением k.
void logInitializing(int size, std::vector<int> &log) {
    int current_log = 2;
    int index = 2;
    log[2] = 1;
    while (index <= size) {
        for (int i = index + 1; i <= (index << 1) && i <= size; ++i) {
            log[i] = current_log;
        }
        index <<= 1;
        current_log += 1;
    }
};

// Передаем в эту функцию основной массив, а также массив запросов, возвращаем массив ответов
void R2Q(const std::vector<int> &array, std::vector<int> &answer, std::vector<std::pair<int, int>> &ranges)
{
    std::vector<int> log(array.size() + 1);
    logInitializing(array.size(), log);
    std::vector<std::vector<std::pair<int, int>>> _sparse_table(log[array.size()]);
    for (int i = 0; i < log[array.size()]; ++i) {
        _sparse_table[i].assign(array.size(), std::make_pair(0, 0));
    }
    for (int i = 0; i < array.size(); ++i) {
        _sparse_table[0][i].first = array[i];
        _sparse_table[0][i].second = array[i];
    }
    for (int i = 1; i < _sparse_table.size(); ++i)
        for (int j = 0; j < array.size() - (1 << i) + 1; ++j) {
            _sparse_table[i][j] = getMinPair(_sparse_table[i - 1][j], _sparse_table[i - 1][j + (1 << (i - 1))]);
        }
    for (int i = 0; i < ranges.size(); ++i) {
        int k = log[ranges[i].second - ranges[i].first + 1] - 1;
        answer.push_back(getMinPair(_sparse_table[k][ranges[i].first], _sparse_table[k][ranges[i].second - (1 << k) + 1]).second);
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }
    std::vector<std::pair<int, int>> ranges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        ranges.emplace_back(a - 1, b - 1);
    }
    std::vector<int> answer;
    R2Q(array, answer, ranges);
    for (int i : answer) {
        std::cout << i << std::endl;
    }
    return 0;
}