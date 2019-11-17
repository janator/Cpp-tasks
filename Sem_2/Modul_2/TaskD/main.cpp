// Пятнашки. Сначала проверяем на разрешимость, кол-во инверсий + строка нуля должно быть нечетным числом.
// Будем хэшировать положение фишек для каждого положения в переменной unsigned long long, по 4 бита на каждую позицию.
// Так как мы ищем не минимальное решение, то алгоритм будет похож на жадный.
// Смотрим все допустимые положения из текущего, считаем для них эвристику(манхетанское растояние), кладем в очередь с приоритетом.
// Делаем так, пока не дойдем до решения.

#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
// Константы для хеширования

const unsigned long long Hash[] = {
        0xFFFFFFFFFFFFFFF0, 0xFFFFFFFFFFFFFF0F, 0xFFFFFFFFFFFFF0FF,
        0xFFFFFFFFFFFF0FFF, 0xFFFFFFFFFFF0FFFF, 0xFFFFFFFFFF0FFFFF,
        0xFFFFFFFFF0FFFFFF, 0xFFFFFFFF0FFFFFFF, 0xFFFFFFF0FFFFFFFF,
        0xFFFFFF0FFFFFFFFF, 0xFFFFF0FFFFFFFFFF, 0xFFFF0FFFFFFFFFFF,
        0xFFF0FFFFFFFFFFFF, 0xFF0FFFFFFFFFFFFF, 0xF0FFFFFFFFFFFFFF,
        0x0FFFFFFFFFFFFFFF
};

const unsigned long long Decode[] = {
        0x000000000000000F, 0x00000000000000F0, 0x0000000000000F00,
        0x000000000000F000, 0x00000000000F0000, 0x0000000000F00000,
        0x000000000F000000, 0x00000000F0000000, 0x0000000F00000000,
        0x000000F000000000, 0x00000F0000000000, 0x0000F00000000000,
        0x000F000000000000, 0x00F0000000000000, 0x0F00000000000000,
        0xF000000000000000
};
struct Field {

    unsigned long long hash = 0;
    int null_pos;
    long num_of_moves = 0;
    int heuristic = 0;

    inline Field() = default;
    inline Field(const Field &field) = default;
    inline Field &operator=(const Field &field) = default;
    friend bool operator<(const Field &L, const Field &R) { return true; }
    inline int GetValue(int place) const {
        return (int)((hash & Decode[place]) >> (place << 2));
    }

    inline void SetValue(int place, int value) {
        hash = (hash & Hash[place]) |
               ((unsigned long long)(value) << (place << 2));
    }

    int Heuristic() const {
        int heuristic = 0;
        for (int i = 0; i < 16; ++i) {
            int value = GetValue(i);
            if (value == 0)
                continue;
            heuristic += 10 * (abs(i % 4 - (value - 1) % 4) + abs(i / 4 - (value - 1) / 4));
        }
        return heuristic;
    }

    bool IsSolvable() const {
        int inversions_num = 0;
        for (int i = 0; i < 16; i++)
            for (int j = i + 1; j < 16; j++)
                if (GetValue(i) != 0 && GetValue(j) != 0 && GetValue(i) > GetValue(j))
                    inversions_num++;
        return (inversions_num + null_pos / 4) % 2 == 1;
    }

    inline Field up() const {
        Field next(*this);
        int trg = null_pos - 4;
        int value = GetValue(trg);
        // Update heuristic
        next.heuristic -= 10 * (abs((trg) % 4 - (value - 1) % 4)
                                + abs(trg / 4 - (value - 1) / 4));
        next.SetValue(trg, 0);
        next.SetValue(null_pos, value);
        // Update heuristic
        next.heuristic += 10 * (abs((null_pos) % 4 - (value - 1) % 4)
                                + abs(null_pos / 4 - (value - 1) / 4));
        next.null_pos = trg;
        next.num_of_moves++;
        return next;
    }

    inline Field down() const {
        Field next(*this);
        int trg = null_pos + 4;
        int value = GetValue(trg);
        // Update heuristic
        next.heuristic -= 10 * (abs((trg) % 4 - (value - 1) % 4)
                                + abs(trg / 4 - (value - 1) / 4));
        next.SetValue(trg, 0);
        next.SetValue(null_pos, value);
        // Update heuristic
        next.heuristic += 10 * (abs((null_pos) % 4 - (value - 1) % 4)
                                + abs(null_pos / 4 - (value - 1) / 4));
        next.null_pos = trg;
        next.num_of_moves++;
        return next;
    }

    inline Field left() const {
        Field next(*this);
        int trg = null_pos - 1;
        int value = GetValue(trg);
        // Update heuristic
        next.heuristic -= 10 * (abs((trg) % 4 - (value - 1) % 4)
                                + abs(trg / 4 - (value - 1) / 4));
        next.SetValue(trg, 0);
        next.SetValue(null_pos, value);
        // Update heuristic
        next.heuristic += 10 * (abs((null_pos) % 4 - (value - 1) % 4)
                                + abs(null_pos / 4 - (value - 1) / 4));
        next.null_pos = trg;
        next.num_of_moves++;
        return next;
    }

    inline Field right() const {
        Field next(*this);
        int trg = null_pos + 1;
        int value = GetValue(trg);
        // Update heuristic
        next.heuristic -= 10 * (abs((trg) % 4 - (value- 1) % 4)
                                + abs(trg / 4 - (value - 1) / 4));
        next.SetValue(trg, 0);
        next.SetValue(null_pos, value);
        // Update heuristic
        next.heuristic += 10 * (abs((null_pos) % 4 - (value - 1) % 4)
                                + abs(null_pos / 4 - (value - 1) / 4));
        next.null_pos = trg;
        next.num_of_moves++;
        return next;
    }
};

inline void AStar(const Field &start, std::list<char> &answer) {
    std::priority_queue<std::pair<int, Field>> queue;
    queue.emplace(std::make_pair(0, start));

    // Хранит хеш поля и пару(ход, родитель)
    std::unordered_map<unsigned long long, std::pair<char, unsigned long long>> parents;
    parents.emplace(start.hash, std::make_pair(0, 0));
    const long long goal = 1147797409030816545;
    Field cur;
    Field next;
    while (!queue.empty()) {
        // Достаем из очереди
        cur = queue.top().second;
        queue.pop();
        // Посещаем все возможные позиции
        if (cur.null_pos >= 4) {
            next = cur.up();
            // Проверяем посещали ли уже
            if (parents.find(next.hash) == parents.end()) {
                // Тогда добавляем
                parents.emplace(next.hash, std::make_pair('D', cur.hash));
                if (next.hash == goal) {
                    break;
                }
                // Добавляем в очередь
                queue.emplace(std::make_pair(-(next.num_of_moves + next.heuristic), next));
            }
        }

        if (cur.null_pos <= 11) {
            next = cur.down();
            // Проверяем посещали ли уже
            if (parents.find(next.hash) == parents.end()) {
                // Тогда добавляем
                parents.emplace(next.hash, std::make_pair('U', cur.hash));
                if (next.hash == goal) {
                    break;
                }
                // Добавляем в очередь
                queue.emplace(std::make_pair(-(next.num_of_moves + next.heuristic), next));
            }
        }

        if (cur.null_pos % 4 != 3) {
            next = cur.right();
            // Проверяем посещали ли уже
            if (parents.find(next.hash) == parents.end()) {
                // Тогда добавляем
                parents.emplace(next.hash, std::make_pair('L', cur.hash));
                if (next.hash == goal) {
                    break;
                }
                // Добавляем в очередь
                queue.emplace(std::make_pair(-(next.num_of_moves + next.heuristic), next));
            }
        }

        if (cur.null_pos % 4 != 0) {
            next = cur.left();
            // Проверяем посещали ли уже
            if (parents.find(next.hash) == parents.end()) {
                // Тогда добавляем
                parents.emplace(next.hash, std::make_pair('R', cur.hash));
                if (next.hash == goal) {
                    break;
                }
                // Добавляем в очередь
                queue.emplace(std::make_pair(-(next.num_of_moves + next.heuristic), next));
            }
        }
    }
    // Востанавливаем путь
    unsigned long long cur_hash = goal;
    std::pair<char, unsigned long long> cur_field;
    while (cur_hash != start.hash) {
        cur_field = parents[cur_hash];
        answer.push_front(cur_field.first);
        cur_hash = cur_field.second;
    }
}

int main() {
    Field start;
    std::list<char> answer;
    for (int i = 0; i < 16; ++i) {
        int value;
        scanf("%d", &value);
        if (value == 0)
            start.null_pos = i;
        start.SetValue(i, value);
    }
    start.heuristic = start.Heuristic();
    if (start.IsSolvable()) {
        AStar(start, answer);
        printf("%d\n", answer.size());
        for (char i : answer) {
            printf("%c", i);
        }
    } else {
        printf("%d", -1);
    }
    return 0;
}