// Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Выведите элементы в порядке post-order (снизу вверх).
#include <iostream>
#include <stack>

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
    void insert(Node *&root, int key);
    void postOrder(Node *&node);
public:
    ~BinaryTree() {
        deleteTree(root);
    }
    void Insert(int key) {
        insert(root, key);
    }
    void PostOrder() {
        postOrder(root);
    }
};

void BinaryTree::deleteTree(Node *node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
    }
    delete node;
}

void BinaryTree::postOrder(Node *&node) {
    if (node == nullptr)
        return;
    std::stack<Node *> post_order;
    post_order.push(root);
    Node *previous = nullptr;
    while (!post_order.empty()) {
        node = post_order.top();
        if (previous == nullptr || previous->right == node || previous->left == node) {
            if (node->left != nullptr)
                post_order.push(node->left);
            else if (node->right != nullptr)
                post_order.push(node->right);
        } else if (node->left == previous) {
            if (node->right != nullptr)
                post_order.push(node->right);
        } else {
            std::cout << node->key << " ";
            post_order.pop();
        }
        previous = node;
    }
}

void BinaryTree::insert(Node *&root, int key) {
    if (root == nullptr) {
        root = new Node(key);
        return;
    }
    Node *current_top = root;
    Node *father_of_current_top = root;
    while (current_top != nullptr) {
        if (key < current_top->key) {
            father_of_current_top = current_top;
            current_top = current_top->left;
        } else {
            father_of_current_top = current_top;
            current_top = current_top->right;
        }
    }
    if (key < father_of_current_top->key) {
        father_of_current_top->left = new Node(key);
    } else {
        father_of_current_top->right = new Node(key);
    }
}

int main() {
    int n;
    std::cin >> n;
    BinaryTree tree;
    for (int i = 0; i < n; ++i) {
        int key;
        std::cin >> key;
        tree.Insert(key);
    }
    tree.PostOrder();
    return 0;
}
