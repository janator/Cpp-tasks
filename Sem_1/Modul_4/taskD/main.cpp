// Дано невзвешенное дерево. Расстоянием между двумя вершинами будем называть количество ребер в пути,
// соединяющем эти две вершины. Для каждой вершины определите сумму расстояний до всех остальных вершин.
// Время работы должно быть O(n).
#include <iostream>
#include <vector>

struct Tree {
    long long length;
    std::vector <int> children;
    int number_of_children;
    int parent;
    long long length_to_children;
    Tree () : parent(0), number_of_children(0), length(0), length_to_children(0) {}
};

void Insert(std::vector<Tree> &tree, int son, int parent) {
    tree[parent].children.push_back(son);
    tree[son].parent = parent;
}

// Считаем для каждой вершины количество детей
void CountNumberOfChildren(std::vector<Tree> &tree) {
    for (int i = tree.size() - 1; i >= 0; --i) {
        for (int j = 0; j < tree[i].children.size(); ++j) {
            // Просматриваем каждого ребенка i-ой вершины, так как у ребенка номер больше,
            // то для него уже посчитано колличество детей.
            tree[i].number_of_children += tree[tree[i].children[j]].number_of_children + 1;
        }
    }
}

// Посчитаем длину для корня
void SummaryLength (std::vector<Tree> &tree) {
    for (int i = tree.size() - 1; i >= 0; --i) {
        for (int j = 0; j < tree[i].children.size(); ++j) {
            tree[i].length_to_children += tree[tree[i].children[j]].length_to_children;
        }
        tree[i].length_to_children += tree[i].number_of_children;
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector <Tree> tree(n);
    for (int i = 0; i < n - 1; ++i) {
        int first_top = 0, second_top = 0;
        std::cin >> first_top >> second_top;
        int x = 1;
        Insert(tree, std::max(first_top, second_top), std::min(first_top, second_top));
        int y = 1;
    }
    CountNumberOfChildren(tree);
    SummaryLength(tree);
    tree[0].length = tree[0].length_to_children;
    std::cout << tree[0].length << std::endl;
    for (int i = 1; i < n; ++i) {
        tree[i].length = tree[tree[i].parent].length + n - 2 * tree[i].number_of_children - 2;
        std::cout << tree[i].length << std::endl;
    }
    return 0;
}