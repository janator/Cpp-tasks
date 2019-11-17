// Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел,
// а также запрос на получение k-ой порядковой статистики.
// Команда добавления числа A задается положительным числом A,
// команда удаления числа A задается отрицательным числом “-A”.
// Запрос на получение k-ой порядковой статистики задается числом k.
// Требуемая скорость выполнения запроса - O(log n).
#include <iostream>

class AvlTree {
private:
    struct Node {
        int key;
        unsigned char height;
        int count;
        Node *left;
        Node *right;
        Node(int key) : key(key), left(nullptr), right(nullptr), height(1), count(1) {}
    };
    Node *root;
    Node *insert(Node *top, int key);
    Node *remove(Node *top, int key);
    Node *findMin(Node *top);
    Node *removeMin(Node *top);
    Node *balance(Node *top);
    Node *rotateLeft(Node *q);
    Node *rotateRight(Node *p);
    Node *find(Node *top, int key);

    unsigned char height(Node *top);
    int count(Node *top);
    int bFactor(Node *top);
    void updateHeightAndCount(Node *top);
    int findKthStatistic(Node *top, int k);
    void deleteTree(Node *top);
public:
    AvlTree() : root(nullptr) {}
    ~AvlTree() {
        deleteTree(root);
    }
    void Insert(int key);
    void Remove(int key);
    int FindKthStatistic(int k);
};

// Удаление
void AvlTree::deleteTree(Node *top) {
    if (top != nullptr) {
        deleteTree(top->left);
        deleteTree(top->right);
        delete top;
    }
}

// Вставка
void AvlTree::Insert(int key) {
    if (find(root, key)) {
        return;
    }
    root = insert(root, key);
}

AvlTree::Node *AvlTree::insert(Node *top, int key) {
    if (top == nullptr) {
        return new Node(key);
    }
    if (key < top->key) {
        top->left = insert(top->left, key);
    } else {
        top->right = insert(top->right, key);
    }
    return balance(top);
}

// Удаление
void AvlTree::Remove(int key) {
    if (find(root, key) == nullptr) {
        return;
    }
    root = remove(root, key);
}

AvlTree::Node *AvlTree::findMin(Node *top) {
    return top->left ? findMin(top->left) : top;
}

AvlTree::Node *AvlTree::removeMin(Node *top) {
    if (top->left == nullptr) {
        return top->right;
    }
    top->left = removeMin(top->left);
    return balance(top);
}

AvlTree::Node *AvlTree::remove(Node *top, int key) {
    if (top == nullptr) {
        return nullptr;
    }
    if (key < top->key) {
        top->left = remove(top->left, key);
    } else if (key > top->key) {
        top->right = remove(top->right, key);
    } else {
        Node *q = top->left;
        Node *r = top->right;
        delete top;
        if (r == nullptr)
            return q;
        Node *min = findMin(r);
        min->right = removeMin(r);
        min->left = q;
        return balance(min);
    }
    return balance(top);
}

// Балансировка
AvlTree::Node *AvlTree::balance(Node *top) {
    updateHeightAndCount(top);
    if (bFactor(top) == 2) {
        if (bFactor(top->right) < 0) {
            top->right = rotateRight(top->right);
        }
        return rotateLeft(top);
    }
    if (bFactor(top) == -2) {
        if (bFactor(top->left) > 0) {
            top->left = rotateLeft(top->left);
        }
        return rotateRight(top);
    }
    return top;
}

// Вращение
AvlTree::Node *AvlTree::rotateRight(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    updateHeightAndCount(p);
    updateHeightAndCount(q);
    return q;
}

AvlTree::Node *AvlTree::rotateLeft(Node *q) {
    Node *p = q->right;
    q->right = p->left;
    p->left = q;
    updateHeightAndCount(q);
    updateHeightAndCount(p);
    return p;
}

// Высота
unsigned char AvlTree::height(Node *top) {
    return top ? top->height : 0;
}

int AvlTree::count(Node *top) {
    return top ? top->count : 0;
}

// Балланс
int AvlTree::bFactor(Node *top) {
    return height(top->right) - height(top->left);
}

// Обновление высоты
void AvlTree::updateHeightAndCount(Node *top) {
    top->height = std::max(height(top->left), height(top->right)) + 1;
    top->count = count(top->left) + count(top->right) + 1;
}

// поиск элемента
AvlTree::Node *AvlTree::find(Node *top, int key) {
    if (top == nullptr) {
        return nullptr;
    }
    if (top->key == key) {
        return top;
    }
    if (key < top->key) {
        return find(top->left, key);
    }
    return find(top->right, key);
}

// Поиск k статистики
int AvlTree::FindKthStatistic(int k) {
    if (root == nullptr) {
        return -1;
    }
    if (k < 0 || k > root->count - 1) {
        return -1;
    }

    return findKthStatistic(root, k);
}

int AvlTree::findKthStatistic(Node *top, int k) {
    int left_count = count(top->left);
    if (k == left_count) {
        return top->key;
    }

    if (k < left_count) {
        return findKthStatistic(top->left, k);
    }
    return findKthStatistic(top->right, k - left_count - 1);
}

int main() {
    AvlTree tree;
    int n = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int key = 0, k = 0;
        std::cin >> key >> k;
        key > 0 ? tree.Insert(key) : tree.Remove(-1 * key);
        std::cout << tree.FindKthStatistic(k) << std::endl;
    }
    return 0;
}