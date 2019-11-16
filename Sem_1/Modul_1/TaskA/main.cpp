// Напишите программу, печатающую набор строк в лексикографическом порядке.
// Строки разделяются символом перевода строки ’∖n’.
// Если последний символ в потоке ввода ’∖n’, считать, что после него нет пустой строки.
// Известно, что либо n<100, либо n≤1000, но при этом число инверсий в данном наборе строк меньше 100.
// Максимальная длина строки 255 символов. Написать свою функцию сравнения строк.
// T(n) = O(n^2); M(n) = O(n);
#include <iostream>
#include <vector>

// перегрузка оператора меньше для строк
bool operator <(const std::string &s1, const std::string &s2){
    for (int i = 0; (i < s1.length()) && (i < s2.length()); ++i){
        if (s1[i] != s2[i]){
            return s1[i] < s2[i];
        }
    }
    return s1.length() < s2.length();
}

// сортировка вставками
void InsertionSort(std::vector <std::string> &lines, const int n){
    for (int i = 1; i < n; i++){
        for (int j = i; j > 0 && lines[j] < lines[j - 1]; --j){
            std::swap(lines[j], lines[j - 1]);
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector <std::string> lines(n);
    for (int i = 0; i < n; ++i){
        std::cin >> lines[i];
    }
    InsertionSort(lines, n);
    for (int i = 0; i < n; ++i){
        std::cout << lines[i] << std::endl;
    }
    return 0;
}