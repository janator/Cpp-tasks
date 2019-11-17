// Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z.
#include <iostream>
#include <vector>

std::string RecoverStrByPi(const std::vector<int> &pi) {
    if (pi.empty())
        return "";
    std::string str = "a";
    for (int i = 1; i < pi.size(); ++i) {
        if (pi[i] != 0) {
            str += str[pi[i] - 1];
        } else {
            // просмотрим все символы которые не могут стоять на этом месте,
            // для этого рекурсивно спустимся вниз по значениям пи,
            std::vector<char> alphabet(26);
            int cur = pi[i - 1];
            while (cur > 0) {
                alphabet[str[cur] - 'a'] = 1;
                cur = pi[cur - 1];
            }
            cur = 1;
            while (alphabet[cur]) {
                ++cur;
            }
            str += (char) (cur + 'a');
        }
    }
    return str;
}

int main() {
    std::vector<int> pi;
    int i;
    while (std::cin >> i) {
        pi.push_back(i);
    }
    std::cout << RecoverStrByPi(pi);
    return 0;
}
