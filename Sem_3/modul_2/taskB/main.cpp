// Даны строки s и t. Постройте сжатое суффиксное дерево, которое содержит все суффиксы строки s и строки t.
// Найдите такое дерево, которое содержит минимальное количество вершин.
#include <string>
#include <iostream>
#include <vector>
#include <map>

struct Vertex {
    size_t parent;
    int str_number;
    int left;
    int right;

    Vertex(size_t parent, int str_number, int left, int right) : parent(parent), str_number(str_number), left(left),
                                                              right(right) {};
};

struct CNode {
    CNode(std::string::iterator start, std::string::iterator end, int str_number) :
            start(start), end(end), suffixLink(nullptr), str_number(str_number) {}
    ~CNode() = default;
    
    std::map<char, CNode *> next_vertices;
    std::string::iterator start;
    std::string::iterator end;
    CNode *suffixLink;
    int str_number;
};

class SuffixTree {
 public:

    SuffixTree(const std::string &str1, const std::string &str2) :
            _strings{str1, str2}, _root(new CNode(_strings[0].end(), _strings[0].end(), 0)), _remainder(0) {

        for (int i = 0; i < 2; ++i) {
            _active_edge = _strings[i].begin();
            _active_node = _root;
            _root->suffixLink = _root;
            _current_sufflink = _root;
            _active_length = 0;
            _remainder = 0;
            for (std::string::iterator suffix = _strings[i].begin(); suffix != _strings[i].end(); ++suffix)
                construct(suffix, i);
        }
    }

    ~SuffixTree() {
        destroy(_root);
    }

    void GetVertices(std::vector<Vertex> &vertices) {
        getVertices(_root, vertices, 0);
    }

 private:
    void getVertices(CNode *node, std::vector<Vertex> &tree, size_t parent) {

        tree.emplace_back(parent, node->str_number, std::distance(_strings[node->str_number].begin(), node->start),
                          std::distance(_strings[node->str_number].begin(), node->end));
        if (node->next_vertices.empty()) {
            return;
        }
        parent = tree.size() - 1;
        for (auto i : node->next_vertices) {
            getVertices(i.second, tree, parent);
        }
    }

    void destroy(CNode *node) {
        for (auto it : node->next_vertices)
            destroy(it.second);
        delete node;
    }

    void addSuffLink(CNode *node) {
        if (_current_sufflink != _root) 
            _current_sufflink->suffixLink = node;
        _current_sufflink = node;
    }

    void construct(std::string::iterator begin, int str_number) {
        ++_remainder;
        _current_sufflink = _root;

        while (_remainder) {
            if (!_active_length)
                _active_edge = begin;

            // Проверяем есть ли из текущей вершины путь по символу
            auto vertex = _active_node->next_vertices.find(*_active_edge);
            CNode *next;
            // Если нет, то создаём новый лист идущий из этой вершины
            if (vertex == _active_node->next_vertices.end()) {
                CNode *leaf = new CNode(begin, _strings[str_number].end(), str_number);
                _active_node->next_vertices[*_active_edge] = leaf;
                addSuffLink(_active_node);
            } else {
                next = vertex->second;
                // Идем по какому-то ребру, тут будет несколько вариантов, мы идем по листу, тогда мы не можем перейти в следующую вершину
                // или мы идем по внутреннему ребру, и тут может возникнуть ситуация, что мы перешли через вершину
                // для этого и введем length, т к листья уже все с самого начала стоят до конца строки, то
                // length = min(begin + 1 - next->start(в том случае если мы идем по листу), next.end - next.start(идем по внутреннему ребру)
                int length;
                if (begin + 1 < next->end && begin + 1 > next->start) {
                    length = begin + 1 - next->start;
                } else {
                    length = next->end - next->start;
                }
                // Если прошли через следующую вершину, то обновляем active points
                if (_active_length >= length) {
                    _active_edge += length;
                    _active_length -= length;
                    _active_node = next;
                    continue;
                }

                // Если использовали правило 3. то переходим к следующей итерации
                if (*begin == *(next->start + _active_length)) {
                    addSuffLink(_active_node);
                    ++_active_length;
                    break;
                }
                
                // Тогда используем правило 2.
                CNode *inner = new CNode(next->start, next->start + _active_length, next->str_number);
                CNode *leaf = new CNode(begin, _strings[str_number].end(), str_number);
                _active_node->next_vertices[*_active_edge] = inner;
                inner->next_vertices[*begin] = leaf;
                next->start += _active_length;
                inner->next_vertices[*next->start] = next;
                addSuffLink(inner);
            }

            // Создали лист - уменьшили remainder
            --_remainder;
            if (_active_node == _root && _active_length > 0) {
                --_active_length;
                _active_edge = begin + 1 - _remainder;
            } else {
                if (_active_node->suffixLink != nullptr) {
                    _active_node = _active_node->suffixLink;
                } else {
                    _active_node = _root;
                }
            }
        }
    }
    std::vector<std::string> _strings;
    CNode *_root;
    CNode *_current_sufflink;
    CNode *_active_node;
    int _remainder;
    int _active_length;
    std::string::iterator _active_edge;
};

int main() {
    std::string str1, str2;
    std::cin >> str1 >> str2;

    SuffixTree suffixTree(str1, str2);
    std::vector<Vertex> tree;
    suffixTree.GetVertices(tree);
    std::cout << tree.size() << std::endl;
    for (size_t i = 1; i < tree.size(); ++i) {
        printf("%ld %d %d %d\n", tree[i].parent, tree[i].str_number, tree[i].left, tree[i].right);
    }
    return 0;
}