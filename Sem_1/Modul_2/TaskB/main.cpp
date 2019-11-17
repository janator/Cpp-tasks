// Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
// Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.
// Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников.
// В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
// Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
// T(n) = O(nlogn); M(n) = n;
#include <iostream>

struct event {
    int year;
    int month;
    int day;
    int type;
    event(): year(0), month(0), day(0), type(0) {}
};

template <class T>
class PriorityQueue {
private:
    int size_;
    void SiftUp(int index);
    void SiftDown(int index);
    T *buffer_;
public:
    PriorityQueue(int start_capacity) {
        buffer_ = new T[start_capacity];
        size_ = 0;
    }
    void HeapSort(PriorityQueue<T> &contemporaries);
    ~PriorityQueue() {
        delete[] buffer_;
    }
    int SweepLine(PriorityQueue<event> &contemporaries);
    int GetSize() {
        return size_;
    }
    void Add(T value);
};

bool operator>(const event &date_1, const event &date_2) {
    if (date_1.year != date_2.year) {
        return date_1.year > date_2.year;
    }
    if (date_1.month != date_2.month) {
        return date_1.month > date_2.month;
    }
    if (date_1.day != date_2.day) {
        return date_1.day > date_2.day;
    }
    if (date_1.type != date_2.type) {
        return date_1.type > date_2.type;
    }
    return false;
}

template <class T>
void PriorityQueue<T>::SiftUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (buffer_[parent] > buffer_[index]) {
            return;
        }
        std::swap(buffer_[parent], buffer_[index]);
        index = parent;
    }
}

template <class T>
void PriorityQueue<T>::SiftDown(int index){
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;
    if (left < size_ && buffer_[left] > buffer_[index]) {
        largest = left;
    }
    if (right < size_ && buffer_[right] > buffer_[largest]) {
        largest = right;
    }
    if (index != largest) {
        std::swap(buffer_[index], buffer_[largest]);
        SiftDown(largest);
    }
}

template <class T>
void PriorityQueue<T>::Add(T value) {
    buffer_[size_++] = value;
    SiftUp(size_ - 1);
}
template <class T>
void PriorityQueue<T>::HeapSort(PriorityQueue<T> &contemporaries){
    int heap_size = size_;
    while (size_ > 1) {
        std::swap(buffer_[0], buffer_[--size_]);
        SiftDown(0);
    }
    size_ = heap_size;
}

template <class T>
T Min(const T &a, const T &b){
    return a > b ? b : a;
}

void MakeAdult(event &date_of_birth, event &date_of_death, PriorityQueue<event> &contemporaries) {
    date_of_birth.year += 18;
    if (date_of_death > date_of_birth){
        date_of_birth.type = 1;
        date_of_death.type = -1;
        contemporaries.Add(date_of_birth);
        date_of_birth.year += 62;
        date_of_birth.type = -1;
        contemporaries.Add(Min(date_of_birth, date_of_death));
    }
}
template <class T>
int PriorityQueue<T>::SweepLine(PriorityQueue<event> &contemporaries) {
    int max_number_of_people = 0;
    int current_number_of_people = 0;
    for (int i = 0; i < contemporaries.GetSize(); ++i) {
        max_number_of_people = std::max(max_number_of_people, current_number_of_people);
        current_number_of_people += contemporaries.buffer_[i].type;
    }
    return max_number_of_people;
}

int main() {
    int n;
    std::cin >> n;
    PriorityQueue <event> contemporaries(2 * n);
    for (int i = 0; i < n; ++i){
        event date_of_birth;
        event date_of_death;
        std::cin >> date_of_birth.day >> date_of_birth.month >> date_of_birth.year >> date_of_death.day >> date_of_death.month >> date_of_death.year;
        MakeAdult(date_of_birth, date_of_death, contemporaries);
    }
    if (contemporaries.GetSize() == 0) {
        std::cout << 0;
        return 0;
    } else {
        contemporaries.HeapSort(contemporaries);
    }

    std::cout << contemporaries.SweepLine(contemporaries);
    return 0;
}