// В большой IT-фирме есть только одна переговорная комната.
// Желающие посовещаться заполняют заявки с желаемым временем начала и конца.
// Ваша задача определить максимальное количество заявок, которое может быть удовлетворено.
// Число заявок ≤ 100000.
// Отсортируем массив интервалов по времени окончания, и каждый раз будем брать подходящий интервал с самым ранним окончанием.
// Д - во: допустим до шага k жадный алгоритм работал оптимальным образом, но на шаге k он выбирает интервал Ak не из оптимального решения (Ak').
// Но т к каждый раз жадный алгоритм выбирает подходящий интервал с самым ранним временем окончания, то Ak <= Ak',
// оба интервала подходят по времени начала, интервал Ak заканчивает раньше или совпадает с Ak' => они равносильны.
#include <iostream>
#include <vector>
#include <algorithm>
using std::pair;
using std::vector;

bool cmp(const pair<int, int> &value_1, const pair<int, int> &value_2) {
  return value_1.second < value_2.second;
}

int CountMeeting(vector<pair<int, int>> &schedule) {
  int count = 1;
  int current_finish = schedule[0].second;
  for (int i = 1; i < schedule.size(); ++i) {
    if (schedule[i].first >= current_finish) {
      ++count;
      current_finish = schedule[i].second;
    }
  }
  return count;
}

int main() {
  vector<pair<int, int>> schedule;
  pair<int, int> meeting;
  while ((std::cin >> meeting.first)) {
    std::cin >> meeting.second;
    schedule.push_back(meeting);
  }
  std::sort(schedule.begin(), schedule.end(), cmp);
  std::cout << CountMeeting(schedule);
  return 0;
}