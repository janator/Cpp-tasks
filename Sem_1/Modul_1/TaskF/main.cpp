// Дан массив целых чисел в диапазоне [0..10^9].
// Размер массива кратен 10 и ограничен сверху значением 2.5 * 10^7 элементов.
// Все значения массива являются элементами псевдо-рандомной последовательности.
// Необходимо отсортировать элементы массива за минимально время и вывести каждый десятый элемент отсортированной последовательности.
// Реализуйте сортировку, основанную на QuickSort.
// Минимальный набор оптимизаций, который необходимо реализовать:
// 1. Оптимизация ввода/вывода
// 2. Оптимизация выбора опорного элемента
// 3. Оптимизация Partition
// 4. Оптимизация рекурсии
// 5. Оптимизация концевой рекурсии
// T(n) = O(nlogn), M(n) = O(nlogn).
#include <iostream>
#include <stack>
using std::stack;
using std::swap;
using std::cin;
using std::cout;

// Медиана пяти
int SelectPivot(int *array, int first, int second, int third, int fourth, int fifth) {
    int first_pair_max, first_pair_min;
    if (array[first] < array[second]) {
        first_pair_max = second;
        first_pair_min = first;
    } else {
        first_pair_max = first;
        first_pair_min = second;
    }
    int second_pair_max, second_pair_min;
    if (array[third] < array[fourth]) {
        second_pair_max = fourth;
        second_pair_min = third;
    } else {
        second_pair_max = third;
        second_pair_min = fourth;
    }
    if (array[second_pair_max] < array[first_pair_max]) {
        if (array[first_pair_min] > array[fifth]) {
            if (array[first_pair_min] > array[second_pair_max])
                return array[second_pair_max] > array[fifth] ? second_pair_max : fifth;
            return array[first_pair_min] > array[second_pair_min] ? first_pair_min : second_pair_min;
        }
        if (array[fifth] > array[second_pair_max])
            return array[first_pair_min] > array[second_pair_max] ? first_pair_min : second_pair_max;
        return array[second_pair_min] > array[fifth] ? second_pair_min : fifth;
    }
    if (array[second_pair_min] > array[fifth]) {
        if (array[first_pair_max] > array[second_pair_min])
            return array[second_pair_min] > array[first_pair_min] ? second_pair_min : first_pair_min;
        return array[first_pair_max] > array[fifth] ? first_pair_max : fifth;
    }
    if (array[first_pair_max] > array[fifth])
        return array[first_pair_min] > array[fifth] ? first_pair_min : fifth;
    return array[first_pair_max] > array[second_pair_min] ? first_pair_max : second_pair_min;
}

void MyQuickSort(int *array, int size) {
    stack<int> stack_of_left;
    stack<int> stack_of_right;
    stack_of_left.push(0);
    stack_of_right.push(size - 1);
    while (!stack_of_left.empty()) {
        int left = stack_of_left.top();
        stack_of_left.pop();
        int right = stack_of_right.top();
        stack_of_right.pop();
        while (left < right) {
            int i = left;
            int j = right - 1;
            int pivot = SelectPivot(array,
                                    left,
                                    (4 * right + left) / 5,
                                    (3 * right + 2 * left) / 5,
                                    (2 * right + 3 * left) / 5,
                                    (right + 4 * left) / 5);
            swap(array[pivot], array[right]);
            while (i <= j) {
                for (; array[i] < array[right]; ++i);
                for (; j >= 0 && array[j] >= array[right]; --j);
                if (i < j)
                    swap(array[i++], array[j--]);
            }
            swap(array[right], array[i]);
            if (i + 1 < right) {
                stack_of_left.push(i + 1);
                stack_of_right.push(right);
            }
            right = i;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int *array = new int[25000000];
    int number;
    int size = 0;
    while (cin >> number) {
        array[size++] = number;
    }
    MyQuickSort(array, size);
    for (int i = 9; i < size; i += 10) {
        cout << array[i] << "\n";
    }
    delete[] array;
    return 0;
}
