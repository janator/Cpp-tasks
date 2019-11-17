// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв.
// Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
// Начальный размер таблицы должен быть равным 8-ми.
// Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
// 1_2. Для разрешения коллизий используйте двойное хеширование.
#include <iostream>
#include <vector>

class HashContainer {
 private:
  struct Record {
   private:
    std::string key;
   public:
    bool deleted;
    std::string getKey(){
      return key;
    }
    void NewKey(const std::string &new_key) {
      key = new_key;
    }
    Record(const std::string &key) : key(key), deleted(false) {}
  };
  std::vector<Record *> buffer;
  int buffer_size;
  int real_size;
  void rehash();
 public:
  HashContainer() : buffer(8, nullptr), buffer_size(8), real_size(0) {}
  ~HashContainer();
  bool Add(const std::string &data);
  bool Remove(const std::string &data);
  bool Has(const std::string &data);
  int FirstHash(const std::string &data);
  int SecondHash (const std::string &data);
};

int HashContainer::FirstHash(const std::string &data) {
  int hash = 0;
  for (int i = data.size(); i >= 0; --i) {
    hash += (data[i] + 11 * hash) % buffer_size;
  }
  return hash % buffer_size;
}

int HashContainer::SecondHash(const std::string &data) {
  int hash = 0;
  for (int i = data.size(); i >= 0; --i) {
    hash += (data[i] + 17 * hash) % buffer_size;
  }
  return (2 * hash + 1) % buffer_size;
}

HashContainer::~HashContainer() {
  for (int i = 0; i < buffer_size; ++i)
    delete buffer[i];
}

bool HashContainer::Add (const std::string &data) {
  if (static_cast<double> (real_size) / buffer_size >= 0.75)
    rehash();
  int hash_1 = FirstHash(data);
  int hash_2 = SecondHash(data);
  int deleted_element = -1;
  if (Has(data))
    return false;
  while (buffer[hash_1] != nullptr && deleted_element == -1) {
    if (buffer[hash_1]->deleted)
      deleted_element = hash_1;
    hash_1 += hash_2;
    hash_1 %= buffer_size;
  }
  if (deleted_element != -1) {
    buffer[deleted_element]->NewKey(data);
    buffer[deleted_element]->deleted = false;
  } else {
    buffer[hash_1] = new Record(data);
  }
  ++real_size;
  return true;
}

bool HashContainer::Has(const std::string &data) {
  int hash_1 = FirstHash(data);
  int hash_2 = SecondHash(data);
  for (int i = 0; i < buffer_size && buffer[hash_1] != nullptr; ++i) {
    if (buffer[hash_1]->getKey() == data && !buffer[hash_1]->deleted)
      return true;
    hash_1 += hash_2;
    hash_1 %= buffer_size;
  }
  return false;
}

bool HashContainer::Remove(const std::string &data) {
  int hash_1 = FirstHash(data);
  int hash_2 = SecondHash(data);
  for (int i = 0; i < buffer_size && buffer[hash_1] != nullptr; ++i) {
    if (buffer[hash_1]->getKey() == data && !buffer[hash_1]->deleted) {
      buffer[hash_1]->deleted = true;
      --real_size;
      return true;
    }
    hash_1 += hash_2;
    hash_1 %= buffer_size;
  }
  return false;
}

void HashContainer::rehash() {
  buffer_size *= 2;
  std::vector<Record *> new_buffer(buffer_size, nullptr);
  for (int i = 0; i < buffer_size / 2; ++i) {
    if (buffer[i] != nullptr && !buffer[i]->deleted) {
      int hash_1 = FirstHash(buffer[i]->getKey());
      int hash_2 = SecondHash(buffer[i]->getKey());
      while (new_buffer[hash_1] != nullptr) {
        hash_1 += hash_2;
        hash_1 %= buffer_size;
      }
      new_buffer[hash_1] = buffer[i];
    } else {
      delete buffer[i];
    }
    buffer[i] = nullptr;
  }
  buffer = new_buffer;
}

int main() {
  HashContainer hash_table;
  std::string key;
  char action;
  bool is_successful;
  while (std::cin >> action >> key) {
    switch (action) {
      case '+' : is_successful = hash_table.Add(key);
        break;
      case '-' : is_successful = hash_table.Remove(key);
        break;
      case '?' : is_successful = hash_table.Has(key);
        break;
    }
    if (is_successful){
      std::cout << "OK" << std::endl;
    } else {
      std::cout << "FAIL" << std::endl;
    }
  }
  return 0;
}