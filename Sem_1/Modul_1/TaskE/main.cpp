// Дан массив неотрицательных целых 64-разрядных чисел.
// Количество чисел не больше 1000000.
// Отсортировать массив методом MSD по битам (бинарный QuickSort).
// T(n) = O(n logn), M(n) = O(n)
#include <vector>
#include <stdio.h>
using std::swap;

long long ExtractKthBit(long long number, int k) {
    return number >> k & 1;
}

void BinaryQuickSort(long long *array, int k, int left, int right) {
    if (right <= left || k < 0) {
        return;
    }
    int i = left;
    int j = right;
    while (i <= j) {
        for (; ExtractKthBit(array[i], k) == 0 && i <= j; ++i) {}
        for (; ExtractKthBit(array[j], k) == 1 && j >= i; --j) {}
        if (i < j) {
            swap(array[i], array[j]);
        }
    }
    BinaryQuickSort(array, k - 1, left, i - 1);
    BinaryQuickSort(array, k - 1, i, right);
}

int main() {
    int n;
    scanf("%d", &n);
    long long *array = new long long[n];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &array[i]);
    }
    BinaryQuickSort(array, 63, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%lld\n", array[i]);
    }
    delete[] array;
    return 0;
}
