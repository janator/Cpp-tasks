#include <iostream>
#include <vector>

std::string RecoveStrByZ(std::vector<int> &z) {
    if (z.empty())
        return "";
    std::string str = "a";
    std::vector<char> alphabet(26);
    int right_border = 0, left_border = 0;
    char after_block = 0;
    for (int i = 1; i < z.size(); ++i) {
        // если ноль и мы не в блоке, то используем первое из разрешенных
        if (z[i] == 0 && right_border < i) {
            if (after_block) {
                int j = 1;
                for (; alphabet[j]; ++j);
                str += (char) (j + 'a');
                after_block = 0;
            } else {
                str += 'b';
            }
        } else {
            if (right_border == z[i] + i - 1) {
                alphabet[str[z[i]] - 'a'] = 1;
            }
            if (right_border < z[i] + i - 1) {
                right_border = z[i] + i - 1;
                left_border = i;
                alphabet.assign(26, 0);
                if (z[i] < str.size()) {
                    alphabet[str[z[i]] - 'a'] = 1;
                }
                after_block = 1;
            }
            str += str[i - left_border];
        }
    }
    return str;
}

//std::vector<int> buildZByStr(const std::string & str) {
//    std::vector<int> z(str.length());
//    z[0] = 0;
//
//    // Границы z-блока с максимальной правой границей
//    size_t left = 0;
//    size_t right = 0;
//    for (size_t i = 1; i < str.length(); i++) {
//        // Выбираем из трех случаев:
//        // 1) i > right, j = 0 - пробегаемся от начала строки и ищем первый символ,
//        // который отличается от соответсвующего символа в z-блоке;
//        // 2) i <= right и right >= z[i - left] + i, j = right - i - пробегаемся по z-блоку
//        // от позиции right и ищем первое несовпадение;
//        // 3) i <= right и right < z[i - left] + i, j = z[i - left] - в этом случае значение
//        // z-функции равно z[i - left].
//        size_t j = (size_t)std::max(0, std::min((int)(right - i), (int)z[i - left]));
//
//        while (i + j < str.size() && str[j] == str[i + j]) {
//            j++;
//        }
//
//        // Перемещаем right, если необходимо
//        if (i + j >= right) {
//            left = i;
//            right = i + j;
//        }
//
//        z[i] = j;
//    }
//    return z;
//}

int main() {
    std::vector<int> z;
    int i;
    while (std::cin >> i) {
        z.push_back(i);
    }
    std::cout << RecoveStrByZ(z);

//    std::string str;
//    std::cin >> str;
//    z = buildZByStr(str);
//    for (int i : z) {
//        std::cout << i << " ";
//    }
//    std::cout << std::endl;
//    std::string my_str = RecoveStrByZ(z);
//    std::cout << my_str << std::endl;
//    z = buildZByStr(my_str);
//    for (int i : z) {
//        std::cout << i << " ";
//    }
    return 0;
}