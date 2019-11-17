// Найдите все вхождения шаблона в строку.
// Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
// p <= 30000, n <= 300000.
// Использовать один из методов:
// - С помощью префикс-функции;
// - С помощью z-функции.
#include <iostream>
#include <vector>

void CountPrefixFuction(const std::string &str, std::vector<int> &prefix_func) {
    for (int i = 1; i < str.length(); ++i) {
        int current_pi = prefix_func[i - 1];
        while (current_pi > 0 && str[i] != str[current_pi]) {
            current_pi = prefix_func[current_pi - 1];
        }
        if (str[i] == str[current_pi])
            ++current_pi;
        prefix_func[i] = current_pi;
    }
}

void KnutMorrisPratt(const std::string &pattern, const std::string &text, std::vector<int> &matches) {
    std::vector<int> prefix_func(pattern.length());
    CountPrefixFuction(pattern, prefix_func);
    matches.clear();
    int previous_pi = 0;
    for (int i = 0; i < text.length(); ++i) {
        int current_pi = previous_pi;
        while (pattern[current_pi] != text[i] && current_pi > 0) {
            current_pi = prefix_func[current_pi - 1];
        }
        if (text[i] == pattern[current_pi]) {
            ++current_pi;
        }
        if (current_pi == pattern.length()) {
            matches.push_back(i + 1 - pattern.length());
        }
        previous_pi = current_pi;
    }
}

int main() {
    std::string pattern, text;
    std::cin >> pattern >> text;
    std::vector<int> matches;
    KnutMorrisPratt(pattern, text, matches);
    for (int i : matches) {
        std::cout << i << " ";
    }
    return 0;
}
