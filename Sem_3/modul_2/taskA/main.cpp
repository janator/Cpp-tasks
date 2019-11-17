// Дана строка длины n. Найти количество ее различных подстрок. Используйте суффиксный массив.
// Построение суффиксного массива выполняйте за O(n log n). Вычисление количества различных подстрок выполняйте за O(n).

#include <iostream>
#include <vector>

const int alphabet_size = 27;
const char zero_el = 'a' - 1;

class NumberOfDifferentStrings {
private:
    std::string _str;

    void buildSuffixArray() {
        firstCountingSort();
        std::vector<int> second_elems(_str.size()), new_classes(_str.size());
        for (int k = 0; (1 << k) < _str.size(); ++k) {
            for (int i = 0; i < _str.size(); ++i) {
                second_elems[i] = (_str.size() + _suffix_array[i] - (1 << k)) % _str.size();
            }
            std::vector<int> counting_sort(_classes_number);
            for (int i = 0; i < _str.size(); ++i) {
                ++counting_sort[_classes[second_elems[i]]];
            }
            for (int i = 1; i < _classes_number; ++i) {
                counting_sort[i] += counting_sort[i - 1];
            }
            for (int i = _str.size() - 1; i >= 0; --i) {
                _suffix_array[--counting_sort[_classes[second_elems[i]]]] = second_elems[i];
            }
            _classes_number = 1;
            for (int i = 1; i < _str.size(); ++i) {
                int sec_part1 = (_suffix_array[i] + (1 << k)) % _str.size();
                int sec_part2 = (_suffix_array[i - 1] + (1 << k)) % _str.size();
                if (_classes[_suffix_array[i]] != _classes[_suffix_array[i - 1]] ||
                    _classes[sec_part1] != _classes[sec_part2]) {
                    ++_classes_number;
                }
                new_classes[_suffix_array[i]] = _classes_number - 1;
            }
            _classes = new_classes;
        }
    };

    void firstCountingSort() {
        std::vector<int> counting_sort(alphabet_size);
        for (char i : _str) {
            ++counting_sort[i - zero_el];
        }
        for (int i = 1; i < alphabet_size; ++i) {
            counting_sort[i] += counting_sort[i - 1];
        }
        for (int i = _str.size() - 1; i >= 0; --i) {
            _suffix_array[--counting_sort[_str[i] - zero_el]] = i;
        }
        _classes_number = 1;
        _classes[_suffix_array[0]] = 0;
        for (int i = 1; i < _str.size(); ++i) {
            if (_str[_suffix_array[i]] != _str[_suffix_array[i - 1]]) {
                ++_classes_number;
            }
            _classes[_suffix_array[i]] = _classes_number - 1;
        }
    };

    void countLCP() {
        // Строим suf^-1
        for (int i = 0; i < _str.size(); ++i) {
            _pos[_suffix_array[i]] = i;
        }
        int k = 0;
        for (int i = 0; i < _str.size(); ++i) {
            if (k > 0) {
                --k;
            }
            if (_pos[i] == _str.size() - 1) {
                _lcp[_str.size() - 1] = -1;
                k = 0;
            } else {
                int j = _suffix_array[_pos[i] + 1];
                for (; i + k < _str.size() && j + k < _str.size() && _str[i + k] == _str[j + k]; ++k);
                _lcp[_pos[i]] = k;
            }
        }
    }

    void countDifferentStrings() {
        for (int i = 1; i < _str.size(); ++i) {
            _number_of_different_strings += _str.size() - 1 - _suffix_array[i] - _lcp[i - 1];
        }
    }

    std::vector<int> _suffix_array;
    std::vector<int> _classes;
    int _classes_number;
    std::vector<int> _lcp;
    std::vector<int> _pos;
    int _number_of_different_strings;
public:
    NumberOfDifferentStrings(const std::string &str) : _str(str + zero_el), _suffix_array(str.size() + 1),
                                                       _classes(str.size() + 1), _lcp(_str.size()), _pos(_str.size()),
                                                       _number_of_different_strings(0) {
        buildSuffixArray();
        countLCP();
        countDifferentStrings();
    };

    int GetNumberOfDifferentStrings() const {
        return _number_of_different_strings;
    }
};

int main() {
    std::string str;
    std::cin >> str;
    NumberOfDifferentStrings numberOfDifferentStrings(str);
    std::cout << numberOfDifferentStrings.GetNumberOfDifferentStrings();
    return 0;
}