// Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
// Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
// Напишите нерекурсивный алгоритм.
// Требования к дополнительной памяти: O(n).
// Требуемое среднее время работы: O(n).
// Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
// Описание для случая прохода от начала массива к концу:
// Выбирается опорный элемент.
// Опорный элемент меняется с последним элементом массива.
// Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного.
// Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. Последним элементом лежит опорный.
// Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
// Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
// Шаг алгоритма. Рассматривается элемент, на который указывает j.
// Если он больше опорного, то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
// В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.
// 3_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
// Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
#include <iostream>
#include <vector>
using std::vector;
using std:: cin;
using std:: cout;
using std:: swap;

// Медиана трех
int SelectPivot(int left, int right, vector<int> &array){
  int middle = (left + right) / 2;
  if (array[left] > array[middle]) {
    if (array[right] > array[left])
      return left;
    return (array[right] > array[middle]) ? right : middle;
  }
  if (array[right] > array[middle])
    return middle;
  return (array[right] > array[left]) ? right : left;
}

// Два итератора от конца массива к началу
int Partition(int left, int right, vector<int> &array){
  int pivot = SelectPivot(left, right, array);
  swap(array[pivot], array[left]);
  int i = right;
  for (int j = right; j > left; --j){
    if (array[j] > array[left]) {
      swap(array[i], array[j]);
      --i;
    }
  }
  swap(array[i], array[left]);
  return i;
}

int KStat(int n, vector<int> &array, int k){
  int left = 0;
  int right = n - 1;
  int partition_result = -1;
  while (k != partition_result){
    partition_result = Partition(left, right, array);
    if (partition_result > k){
      right = partition_result - 1;
    } else {
      left = partition_result + 1;
    }
  }
  return array[k];
}

int main() {
  int n;
  int k;
  cin >> n >> k;
  vector<int> array(n);
  for ( int i = 0; i < n; ++i){
    cin >> array[i];
  }
  int a = KStat(n, array, k);
  cout << a;
  return 0;
}