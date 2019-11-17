// Дано N кубиков.
// Требуется определить каким количеством способов можно выстроить из этих кубиков пирамиду.
#include <iostream>
#include <vector>

long long CountDifferentPyramids(int n, int k, std::vector<std::vector<long long>> &array) {
  if (k < 0 || n < 0) {
    return 0;
  }
  if (k == 1) {
    if (n == 1) {
      return 1;
    }
    return 0;
  } else if (n <= 2) {
    return 1;
  }
  if (k > n)
    k = n;
  if (array[n][k] != -1)
    return array[n][k];
  array[n][k] = CountDifferentPyramids(n, k - 1, array) + CountDifferentPyramids(n - k, k - 1, array);
  return array[n][k];
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::vector<long long>> array(n + 1);
  for (int i = 0; i <= n; ++i) {
    array[i].resize(n + 1, -1);
  }
  std::cout << CountDifferentPyramids(n, n, array);
  return 0;
}