// Шаблон поиска задан строкой длины m, в которой кроме обычных символов могут встречаться символы “?”.
// Найти позиции всех вхождений шаблона в тексте длины n. Каждое вхождение шаблона предполагает,
// что все обычные символы совпадают с соответствующими из текста, а вместо символа “?” в тексте встречается произвольный символ.
// Время работы - O(n + m + Z), где Z - общее -число вхождений подстрок шаблона “между вопросиками” в исходном тексте. m ≤ 5000, n ≤ 2000000.
#include <iostream>
#include <vector>

int const alphabet_size = 26;

class AhoCorasick {
public:
    AhoCorasick() : trie_(1, Node(0, -1)), vocabulary_() {}

    // строит автомат, если бы нам дали слова по отдельности, в задаче не ипользуется, просто для правильной реализации карасика
    AhoCorasick(std::vector<std::string> &vocabulary) : trie_(1, Node(0, -1)), vocabulary_("") {
        trie_[0].sufflink = 0;
        for (int i = 0; i < vocabulary.size(); ++i) {
            std::pair current_start_end(-1, -1);
            current_start_end.first = vocabulary_.length();
            vocabulary_ += vocabulary[i];
            current_start_end.second = vocabulary_.length() - 1;
            start_end.push_back(current_start_end);
        }
        for (int i = 0; i < start_end.size(); ++i) {
            AddWordIntoBor(start_end[i], i);
        }
    }

    // возвращает вхождения слов из словаря в текст
    std::vector<std::vector<int>> GetEntries(const std::string &text) {
        std::vector<std::vector<int>> entries(start_end.size());
        int current_vertex = 0;
        for (int i = 0; i < text.length(); ++i) {
            // переходим в боре по символу из текста
            current_vertex = GoToVertexBySymbol(current_vertex, text[i] - 'a');
            // спустимся по суффиксным ссылкам до корня, проверяя их на терминальность
            int suff_vertex = current_vertex;
            do {
                if (trie_[suff_vertex].is_terminal) {
                    // проходим по всем словам, для которых данная вершина является терминальной
                    for (int j : trie_[suff_vertex].patterns) {
                        // jое слово входит в текст на позиции (i - длина слова)
                        entries[j].push_back(i - start_end[j].second + start_end[j].first);
                    }
                }
                suff_vertex = GetSufflink(suff_vertex);
            } while (suff_vertex != 0);
        }
        return entries;
    }

protected:
    // вершина бора
    struct Node {
        Node(int parent, char transit_symbol) : transit_symbol(transit_symbol), parent(parent), sufflink(-1),
                                                is_terminal(false) {
            for (int i = 0; i < alphabet_size; ++i) {
                edges[i] = -1;
                saved_move[i] = -1;
            }
        }

        // исходящие вершины
        int edges[alphabet_size];
        // если мы уже из этой вершины искали куда перейти по заданному символу, сохраним, чтобы экономить время
        int saved_move[alphabet_size];
        int sufflink;
        int parent;
        // символ по которому переходили из родителя
        char transit_symbol;
        bool is_terminal;
        // номера шаблонов, для которых данная вершина является терминальной
        std::vector<int> patterns;
    };

    // вектор вершин бора
    std::vector<Node> trie_;

    void AddWordIntoBor(const std::pair<int, int> &start_end_pos, int word_number) {
        int current_vertex = 0;
        for (int i = start_end_pos.first; i <= start_end_pos.second; ++i) {
            char symbol = vocabulary_[i] - 'a';
            if (trie_[current_vertex].edges[symbol] == -1) {
                trie_.emplace_back(current_vertex, symbol);
                trie_[current_vertex].edges[symbol] = trie_.size() - 1;
            }
            current_vertex = trie_[current_vertex].edges[symbol];
        }
        trie_[current_vertex].is_terminal = true;
        trie_[current_vertex].patterns.push_back(word_number);
    }

    int GetSufflink(int index) {
        if (trie_[index].sufflink == -1) {
            if (trie_[index].parent == 0 || index == 0) {
                trie_[index].sufflink = 0;
            } else {
                trie_[index].sufflink = GoToVertexBySymbol(GetSufflink(trie_[index].parent),
                                                           trie_[index].transit_symbol);
            }
        }
        return trie_[index].sufflink;
    }

    int GoToVertexBySymbol(int index, char symbol) {
        // если еще не искали путь из этой вершины по этому символу
        if (trie_[index].saved_move[symbol] == -1) {
            // если есть переход в следующую вершину в боре, то идем туда
            if (trie_[index].edges[symbol] != -1) {
                trie_[index].saved_move[symbol] = trie_[index].edges[symbol];
            } else if (index != 0) {
                // иначе если мы не в корне то идем по суфф ссылке
                trie_[index].saved_move[symbol] = GoToVertexBySymbol(GetSufflink(index), symbol);
            } else {
                // для корня оставим ноль
                trie_[index].saved_move[symbol] = 0;
            }
        }
        return trie_[index].saved_move[symbol];
    }

    std::vector<std::pair<int, int>> start_end;
    std::string vocabulary_;

};

class PatternWithQuestion : AhoCorasick {
public:
    PatternWithQuestion(const std::string &pattern) : AhoCorasick() {
        trie_[0].sufflink = 0;
        vocabulary_ = pattern;
        DivideIntoWords(pattern);
        for (int i = 0; i < start_end.size(); ++i) {
            AddWordIntoBor(start_end[i], i);
        }
    }

    std::vector<int> GetPatternEntries(const std::string &text) {
        std::vector<std::vector<int>> entries = GetEntries(text);
        std::vector<int> text_mark(text.length());
        std::vector<int> pattern_entries;
        for (int i = 0; i < entries.size(); ++i) {
            for (int j = 0; j < entries[i].size(); ++j) {
                if (entries[i][j] - start_end[i].first >= 0 &&
                    entries[i][j] - start_end[i].first + vocabulary_.length() <= text.length())
                    ++text_mark[entries[i][j] - start_end[i].first];
            }
        }
        for (int i = 0; i < text_mark.size(); ++i) {
            if (text_mark[i] == start_end.size()) {
                pattern_entries.push_back(i);
            }
        }
        return pattern_entries;
    }

private:
    void DivideIntoWords(const std::string &pattern) {
        int start = 0;
        for (; pattern[start] == '?'; ++start);
        for (int i = start; i < pattern.size() - 1; ++i) {
            if (pattern[i] == '?') {
                if (start != -1) {
                    start_end.emplace_back(start, i - 1);
                    start = -1;
                }
                if (pattern[i + 1] != '?') {
                    start = i + 1;
                }
            }
        }
        // последний элемент проверим отдельно
        if (start != -1) {
            if (pattern[pattern.size() - 1] == '?') {
                start_end.emplace_back(start, pattern.size() - 2);
            } else {
                start_end.emplace_back(start, pattern.size() - 1);
            }
        }
    }

};

int main() {
    std::string pattern, text;
    std::cin >> pattern >> text;

    PatternWithQuestion patternWithQuestion(pattern);

    std::vector<int> entries = patternWithQuestion.GetPatternEntries(text);
    for (int i : entries) {
        std::cout << i << " ";
    }

    return 0;
}
