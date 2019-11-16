// Дана последовательность целых чисел из диапазона (-1000000000 .. 1000000000).
// Длина последовательности не больше 1000000. Числа записаны по одному в строке.
// Количество чисел не указано. Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
// Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
// Указание: количество инверсий может быть больше 4*1000000000 - используйте int64_t.
// T(n) = O(nlogn), M(n) = O(n)
#include <iostream>
using namespace std;

void MergeSort(int *a, unsigned int left, unsigned int right, long long &inversions_number){
    unsigned int middle = (left + right) / 2;
    if (left < middle) {
        MergeSort(a, left, middle, inversions_number);
    }
    if (middle + 1 < right) {
        MergeSort(a, middle + 1, right, inversions_number);
    }
// слияние двух массивов
    int i = left;
    int j = middle + 1;
    int k = left;
    int *b = new int[right + 1];
    while ( i <= middle && j <= right) {
        if (a[i] <= a[j]){
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
            inversions_number += middle - i + 1;
        }
    }
    while (i <= middle) {
        b[k++] = a[i++];
    }
    while (j <= right) {
        b[k++] = a[j++];
    }
    for (int p = left; p <= right; ++p){
        a[p] = b[p];
    }
    delete[] b;
}

void Resize(int *&a, int &size) {
    int *b = new int[10 * size];
    for (int i = 0; i < size; ++i) {
        b[i] = a[i];
    }
    delete[] a;
    a = b;
    size *= 10;
}

int main() {
    int size = 10000;
    int *a = new int[size];
    unsigned int n = 0;
    int number;
    while (cin >> number) {
        if (n == size) {
            Resize(a, size);
        }
        a[n++] = number;
    }
    long long inversions_number = 0;
    MergeSort(a, 0, n - 1, inversions_number);
    cout << inversions_number;
    delete[] a;
    return 0;
}