// Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
// Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
// Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
// Добавление узла в декартово дерево выполняйте следующим образом:
// При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
// Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
// а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y).
// Новый узел вставьте на место узла P.
// Построить также наивное дерево поиска по ключам Xi.
// Т.е., при добавлении очередного числа K в наивное дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
//
// Вычислить разницу глубин наивного дерева поиска и декартового дерева.
// Разница может быть отрицательна, необходимо вывести модуль разности.
#include <iostream>
#include <cmath>

class BinaryTree {
private:
    struct Node {
        int key;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int key) : key(key) {}
    };
    Node *root = nullptr;
    void deleteTree(Node *node);
    void insert(Node *&top, int key);
    int depthCount(Node *root);
public:
    ~BinaryTree() {
        deleteTree(root);
    }
    void Insert(int key) {
        insert(root, key);
    }
    int DepthCount() {
        return depthCount(root);
    }
};

int BinaryTree::depthCount(Node *root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(depthCount(root->left), depthCount(root->right));
}

void BinaryTree::deleteTree(Node *node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
    }
    delete node;
}

void BinaryTree::insert(Node *&top, int key) {
    if (top == nullptr) {
        top = new Node(key);
        return;
    }
    if (key < top->key) {
        if (top->left == nullptr) {
            top->left = new Node(key);
        } else {
            insert(top->left, key);
        }
        return;
    }
    if (top->right == nullptr)
        top->right = new Node(key);
    else insert(top->right, key);
}

class Treap {
private:
    struct CNode {
        int key = 0;
        int priority = 0;
        CNode *left = nullptr;
        CNode *right = nullptr;
        CNode(int key, int priority) : key(key), priority(priority) {}
    };
    CNode *root = nullptr;
    void split(int x, CNode *top, CNode *&left, CNode *&right);
    void insert(CNode *&top, int key, int priority);
    void deleteTreap(CNode *node);
    int depthCount(CNode *top);
public:
    ~Treap() {
        deleteTreap(root);
    }
    void Insert(int key, int priority) {
        insert(root, key, priority);
    }
    int DepthCount() {
        return depthCount(root);
    }
};

void Treap::insert(CNode *&top, int key, int priority) {
    if (top == nullptr) {
        top = new CNode(key, priority);
        return;
    }
    if (priority < top->priority) {
        if (key < top->key) {
            insert(top->left, key, priority);
        } else {
            insert(top->right, key, priority);
        }
    } else {
        CNode* node = new CNode(key, priority);
        split(key, top, node->left, node->right);
        top = node;
    }
}

void Treap::split(int key, CNode *top, CNode *&left, CNode *&right) {
    if (top == nullptr) {
        left = nullptr;
        right = nullptr;
    } else if (key < top->key) {
        split(key, top->left, left, top->left);
        right = top;
    } else {
        split(key, top->right, top->right, right);
        left = top;
    }
}

void Treap::deleteTreap(CNode *node) {
    if (node) {
        deleteTreap(node->left);
        deleteTreap(node->right);
    }
    delete node;
}

int Treap::depthCount(CNode *top) {
    if (top == nullptr) {
        return 0;
    }
    return 1 + std::max(depthCount(top->left), depthCount(top->right));
}

int main() {
    int n;
    std::cin >> n;
    BinaryTree binary_tree;
    Treap treap;
    for (int i = 0; i < n; ++i) {
        int key = 0, priority = 0;
        std::cin >> key >> priority;
        binary_tree.Insert(key);
        treap.Insert(key, priority);
    }
    std::cout << abs(binary_tree.DepthCount() - treap.DepthCount());
    return 0;
}