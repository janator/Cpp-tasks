// Восьминашки, найти решение за минимальное число ходов.
// Алгоритм A*. Эвристика - манхетанское растояние.
// Положение поля будем хэшировать.
// Проверяем, разрешима ли задача, считая кол-во инверсий, если их четное кол-во, то да.
// Алгоритм смотрит стартовое положение, смотрим все соседние положения, допустимые из него, помещает их в кучу с приоритетом,
// приоритетом является = кол-во ходов до данного положения + манхетанское растояние.
// Если при просмотре соседних положений находим более короткий путь до какого-то положения,
// то обновляем для него отца и кол-во ходов.
// Ячеек всего 9 < 2^4, каждые 4 бита в переменной long long будут хешировать одну ячейку.
#include <iostream>
#include <map>
#include <vector>

// Для хеширования положения ячеек, и для расшифровки обратно
struct Mask {
    std::vector<long long> mask = {0x00000000F, 0x0000000F0, 0x000000F00, 0x00000F000, 0x0000F0000,
                                   0x000F00000, 0x00F000000, 0x0F0000000, 0xF00000000};
    std::vector<long long> anti_mask = {0xFFFFFFFF0, 0xFFFFFFF0F, 0xFFFFFF0FF, 0xFFFFF0FFF, 0xFFFF0FFFF,
                                        0xFFF0FFFFF, 0xFF0FFFFFF, 0xF0FFFFFFF, 0x0FFFFFFFF};

    // Значение выйгрышного положения = 1000 0111 0110 0101 0100 0011 0010 0001
    long long goal = 2271560481;
};

// Хранит положение, отца, кол-во ходов, считает манхетанское растояние, возвращает положения, которые получаются при ходах.
class Pole {
private:
    long long _hash = 0;
    int _null_pos;
    int _heuristic = 0;
    char _move;
    long long _father;
    int _number_of_moves = 0;
public:
    Pole() = default;
    void Scanf(Mask &mask) {
        for (int i = 0; i < 9; ++i) {
            int value;
            std::cin >> value;
            MakeHash(i, value, mask);
            if (value == 0) {
                _null_pos = i;
            }
        }
    }
    void SetMove(char move) {
        _move = move;
    }
    long long GetFather() const {
        return _father;
    }
    void SetFather(long long father) {
        _father = father;
    }
    int GetNumderOfMoves() const {
        return _number_of_moves;
    }
    void SetNumberOfMoves(int number_of_moves) {
        _number_of_moves = number_of_moves;
    }
    void MakeHash(int place, int value, Mask &mask) {
        _hash = (_hash & mask.anti_mask[place]) | ((long long) value << (place << 2));
    }
    Pole &operator=(const Pole &pole) = default;

    int Decode(int place, Mask &mask) const {
        return ((_hash & mask.mask[place]) >> (place << 2));
    }
    Pole MoveUp(Mask &mask) const {
        Pole next_pole(*this);
        int up_value = Decode(_null_pos - 3, mask);
        next_pole.MakeHash(_null_pos - 3, 0, mask);
        next_pole.MakeHash(_null_pos, up_value, mask);
        next_pole._null_pos = _null_pos - 3;
        next_pole._move = 'U';
        next_pole._father = _hash;
        ++next_pole._number_of_moves;
        next_pole.Heuristic(mask);
        return next_pole;
    }
    Pole MoveDown(Mask &mask) const {
        Pole next_pole(*this);
        int down_value = Decode(_null_pos + 3, mask);
        next_pole.MakeHash(_null_pos + 3, 0, mask);
        next_pole.MakeHash(_null_pos, down_value, mask);
        next_pole._null_pos = _null_pos + 3;
        next_pole._move = 'D';
        next_pole._father = _hash;
        ++next_pole._number_of_moves;
        next_pole.Heuristic(mask);
        return next_pole;
    }
    Pole MoveLeft(Mask &mask) const {
        Pole next_pole(*this);
        int left_value = Decode(_null_pos - 1, mask);
        next_pole.MakeHash(_null_pos - 1, 0, mask);
        next_pole.MakeHash(_null_pos, left_value, mask);
        next_pole._null_pos = _null_pos - 1;
        next_pole._move = 'L';
        next_pole._father = _hash;
        ++next_pole._number_of_moves;
        next_pole.Heuristic(mask);
        return next_pole;
    }
    Pole MoveRight(Mask &mask) const {
        Pole next_pole(*this);
        int right_value = Decode(_null_pos + 1, mask);
        next_pole.MakeHash(_null_pos + 1, 0, mask);
        next_pole.MakeHash(_null_pos, right_value, mask);
        ++next_pole._null_pos;
        next_pole._move = 'R';
        next_pole._father = _hash;
        ++next_pole._number_of_moves;
        next_pole.Heuristic(mask);
        return next_pole;
    }
    bool IsSolvable(Mask &mask) {
        int inversions_number = 0;
        for (int i = 0; i < 9; ++i) {
            for (int j = i + 1; j < 9; ++j) {
                int i_value = Decode(i, mask);
                int j_value = Decode(j, mask);
                if (i_value != 0 && j_value != 0 && i_value > j_value) {
                    ++inversions_number;
                }
            }
        }
        return inversions_number % 2 == 0;
    }
    void Heuristic(Mask &mask) {
        _heuristic = 0;
        for (int i = 0; i < 9; ++i) {
            int value = this->Decode(i, mask);
            if (value == 0) {
                continue;
            }
            _heuristic += abs((value - 1) % 3 - i % 3) + abs((value - 1) / 3 - i / 3);
        }
    }
    int Priority() const {
        return _heuristic + _number_of_moves;
    }
    long long GetHash() const {
        return _hash;
    }
    int GetNullPos() const {
        return _null_pos;
    }
    char GetMove() const {
        return _move;
    }
};

std::string AZvezda(Pole &start, Mask &mask) {
    if (!start.IsSolvable(mask)) {
        return "-1";
    }
    std::string answer = "";
    std::multimap<int, long long> deque;
    std::map<long long, Pole> discovered_pos;
    start.Heuristic(mask);
    deque.emplace(start.Priority(), start.GetHash());
    discovered_pos[start.GetHash()] = start;
    long long current;
    while (!deque.empty()) {
        current = deque.begin()->second;
        Pole current_pole = discovered_pos[current];
        deque.erase(deque.begin());
        if (current_pole.GetHash() == mask.goal)
            break;
        if (current_pole.GetNullPos() >= 3) {
            Pole next_pole = current_pole.MoveUp(mask);
            // Если встречаем положение первый раз
            if (discovered_pos.find(next_pole.GetHash()) == discovered_pos.end()) {
                discovered_pos[next_pole.GetHash()] = next_pole;
                deque.emplace(next_pole.Priority(), next_pole.GetHash());
            } else if (discovered_pos[next_pole.GetHash()].GetNumderOfMoves() > current_pole.GetNumderOfMoves() + 1) {
                discovered_pos[next_pole.GetHash()].SetNumberOfMoves(current_pole.GetNumderOfMoves() + 1);
                discovered_pos[next_pole.GetHash()].SetFather(current);
                discovered_pos[next_pole.GetHash()].SetMove('U');
            }
        }
        if (current_pole.GetNullPos() <= 5) {
            Pole next_pole = current_pole.MoveDown(mask);
            // Если встречаем положение первый раз
            if (discovered_pos.find(next_pole.GetHash()) == discovered_pos.end()) {
                discovered_pos[next_pole.GetHash()] = next_pole;
                deque.emplace(next_pole.Priority(), next_pole.GetHash());
                // иначе обновляем отца и кол-во ходов
            } else if (discovered_pos[next_pole.GetHash()].GetNumderOfMoves() > current_pole.GetNumderOfMoves() + 1) {
                discovered_pos[next_pole.GetHash()].SetNumberOfMoves(current_pole.GetNumderOfMoves() + 1);
                discovered_pos[next_pole.GetHash()].SetFather(current);
                discovered_pos[next_pole.GetHash()].SetMove('D');
            }
        }
        if (current_pole.GetNullPos() % 3 != 0) {
            Pole next_pole = current_pole.MoveLeft(mask);
            // Если встречаем положение первый раз
            if (discovered_pos.find(next_pole.GetHash()) == discovered_pos.end()) {
                discovered_pos[next_pole.GetHash()] = next_pole;
                deque.emplace(next_pole.Priority(), next_pole.GetHash());
            } else if (discovered_pos[next_pole.GetHash()].GetNumderOfMoves() > current_pole.GetNumderOfMoves() + 1) {
                discovered_pos[next_pole.GetHash()].SetNumberOfMoves(current_pole.GetNumderOfMoves() + 1);
                discovered_pos[next_pole.GetHash()].SetFather(current);
                discovered_pos[next_pole.GetHash()].SetMove('L');
            }
        }
        if (current_pole.GetNullPos() % 3 != 2) {
            Pole next_pole = current_pole.MoveRight(mask);
            // Если встречаем положение первый раз
            if (discovered_pos.find(next_pole.GetHash()) == discovered_pos.end()) {
                discovered_pos[next_pole.GetHash()] = next_pole;
                deque.emplace(next_pole.Priority(), next_pole.GetHash());
            } else if (discovered_pos[next_pole.GetHash()].GetNumderOfMoves() > current_pole.GetNumderOfMoves() + 1) {
                discovered_pos[next_pole.GetHash()].SetNumberOfMoves(current_pole.GetNumderOfMoves() + 1);
                discovered_pos[next_pole.GetHash()].SetFather(current);
                discovered_pos[next_pole.GetHash()].SetMove('R');
            }
        }
    }

    // Востанавливаем путь через отцов
    while (current != start.GetHash()) {
        answer = discovered_pos[current].GetMove() + answer;
        current = discovered_pos[current].GetFather();
    }
    return answer;
}

int main() {
    Mask mask;
    Pole pole;
    pole.Scanf(mask);
    std::string answer;
    answer = AZvezda(pole, mask);
    if (answer != "-1") {
        std::cout << answer.size() << std::endl << answer;
    } else {
        std::cout << answer;
    }
    return 0;
}