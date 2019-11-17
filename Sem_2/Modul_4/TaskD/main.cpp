// Реализуйте структуру данных “массив строк” на основе декартового дерева по неявному ключу со следующими методами:
//  Добавление строки в позицию position.
//  Все последующие строки сдвигаются на одну позицию вперед.
// void InsertAt( int position, const std::string& value );
//  Удаление строки из позиции position.
//  Все последующие строки сдвигаются на одну позицию назад.
// void DeleteAt( int position );
//  Получение строки из позиции position.
// std::string GetAt( int position );
// Все методы должны работать за O(log n) в среднем, где n – текущее количество строк в массиве.
// Дерево по неявному ключу - декартого дерево, которое является бинарным деревом по позиции элемента, и кучей по рандомному приоритету.
// Для каждого элемента храним количество элементов в его поддереве, таким образом можно обращаться к нашему массиву по индексу.
#include <iostream>
#include <iomanip>

// Дерево по неявному ключу
class ImplicitKeyTreap{
 private:
  struct CNode{
    CNode(const std::string& data) : _data(data), priority(rand()), _left(nullptr), _right(nullptr), _size(1) {}
    // Пересчитывает размер дерева
    void Update()
    {
      _size = 1;
      if (_left != nullptr)
        _size += _left->_size;
      if (_right != nullptr)
        _size += _right->_size;
    }
    size_t _size;
    int priority;
    std::string _data;
    CNode* _left;
    CNode* _right;
  };
  // Разрезает дерево на два, возвращает пару указателей на новые корни
  std::pair<CNode*, CNode*> Split(CNode* node, int position)
  {
    if (node == nullptr)
      //return {nulptr, nulptr};
      return std::pair<CNode*, CNode*>(nullptr, nullptr);
    int left = (node->_left != nullptr) ? (node->_left->_size) : 0;
    // Если количество элементов в левом поддереве больше, то рекурсивно идем разрезать в нем
    if (left >= position) {
      std::pair<CNode*, CNode*> answer = Split(node->_left, position);
      node->_left = answer.second;
      node->Update();
      return std::make_pair(answer.first, node);
    }
    // Иначе в правое, причем тогда уменьшаем значение позиции на left + 1 т к это то, сколько мы уже отрезали(то что в левом поддереве и сам node)
    else
    {
      std::pair<CNode*, CNode*> ans = Split(node->_right, position - left - 1);
      node->_right = ans.first;
      node->Update();
      return std::make_pair(node, ans.second);
    }
  }

  // Сливает дерево в одно
  CNode* Merge(CNode* node_1, CNode* node_2)
  {
    if (node_2 == nullptr)
      return node_1;
    if (node_1 == nullptr)
      return node_2;
    // Если приоритет первого больше приоритета второго, то второе подвешиваем справа к первому рекурсивно
    if (node_1->priority > node_2->priority) {
      node_1->_right = Merge(node_1->_right, node_2);
      node_1->Update();
      return node_1;
    } else {
      node_2->_left = Merge(node_1, node_2->_left);
      node_2->Update();
      return node_2;
    }
  }

  // Удаляем дерево рекурсивно снизу
  void clear(CNode* node)
  {
    if (node == nullptr)
      return;
    clear(node->_left);
    clear(node->_right);
    delete node;
  }
  CNode* _root;

public:
    ImplicitKeyTreap() : _root(nullptr) {}
    ~ImplicitKeyTreap()
    {
      // Удаляем рекурсивно поддеревья
      clear(_root);
      _root = nullptr;
    }
    void operator=(const ImplicitKeyTreap&) = delete;
    ImplicitKeyTreap (const ImplicitKeyTreap&) = delete;
    // Вставка
    // Разрезаем массив [0, N) по индексу pos, на массивы L[0, pos) и R[pos, N)
    // Делаем новый CNode, приписываем его справа к левому результату, и к ним обоим правый результат.
    void InsertAt(int position, const std::string& data)
    {
      CNode* new_node = new CNode(data);
      // Разрезаем дерево по заданной позиции, сливаем первое с новым элементом, потом всё сливаем со вторым
      std::pair<CNode*, CNode*> splitted = Split(_root, position);
      CNode* right = Merge(new_node, splitted.second);
      _root = Merge(splitted.first, right);
    }

    // Удаление со start до finish позиции
    // Разрезаем массив [0, N) по индексу start на два массива: [0, start) [start, N)
    // Далее второй разрезаем еще раз по индексу start - finish + 1 и получаем [start, finish + 1) и [finish + 1, N)
    void DeleteAt(int start_pos, int finish_pos)
    {
      // Разрезаем по элементу и сливаем без него
      std::pair<CNode*, CNode*> tree_1 = Split(_root, start_pos);
      std::pair<CNode*, CNode*> tree_2 = Split(tree_1.second, finish_pos - start_pos + 1);
      clear(tree_2.first);
      _root = Merge(tree_1.first, tree_2.second);
    }

    // Возвращаем значение по позиции.
    std::string GetAt(int position) const
    {
      CNode* node = _root;
      int left = (node->_left != nullptr) ? (node->_left->_size) : 0;
      while (left != position) {
        // Если позиция меньше элементов слева от текущего элементо, то идем искать в левое поддерево, иначе в правое
        if (position < left) {
          node = node->_left;
        } else {
          position -= left + 1;
          node = node->_right;
        }
        left = (node->_left != nullptr) ? (node->_left->_size) : 0;
      }
      return node->_data;
    }
};


int main() {
    int n;
    std::cin >> n;
    ImplicitKeyTreap implicit_key_treap;
    for (int i = 0; i < n; ++i) {
        char command;
        std::cin >> command;
        switch(command){
            case '+': {
                int position;
                std::string data;
                std::cin >> position >> data;
                implicit_key_treap.InsertAt(position, data);
                break;
            }
            case '-': {
                int start_pos, finish_pos;
                std::cin >> start_pos >> finish_pos;
                implicit_key_treap.DeleteAt(start_pos, finish_pos);
                break;
            }
          case '?': {
            int position;
            std::cin >> position;
            std::cout << implicit_key_treap.GetAt(position) << std::endl;
            break;
          }
        }
    }
    return 0;
}