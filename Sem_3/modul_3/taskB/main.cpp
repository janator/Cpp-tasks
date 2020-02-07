#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

const double pi = 3.14159265;

class Vector {
public:
    Vector(double x, double y) : _x(x), _y(y) {}

    Vector(double x1, double y1, double z1, double x2, double y2, double z2) :
            _x(x2 - x1), _y(y2 - y1) {}

    ~Vector() = default;

    Vector operator+(const Vector &other) const {
        return {this->_x + other._x, this->_y + other._y};
    }

    double _x;
    double _y;
};

// If the point1 below point2
bool operator<(const Vector &vector1, const Vector &vector2) {
    if (vector1._y < vector2._y) {
        return true;
    }
    if (vector1._y == vector2._y)
        return vector1._x < vector2._x;
    return false;
}

double Angle(const Vector &vector1, const Vector &vector2) {
    double angle = atan2(vector2._y - vector1._y, vector2._x - vector1._x);
    if (angle < 0)
        angle += 2 * pi;
    return angle;
}

void Reverse(std::vector<Vector> &polygon) {
    std::reverse(polygon.begin(), polygon.end());
    int min_el = 0;
    for (int i = 1; i < polygon.size(); ++i) {
        if (polygon[i] < polygon[min_el])
            min_el = i;
    }
    rotate(polygon.begin(), polygon.begin() + min_el, polygon.end());
}

void MinkowskiAmount(std::vector<Vector> &polygon1, std::vector<Vector> &polygon2, std::vector<Vector> &answer) {
    answer.clear();
    polygon1.push_back(polygon1[0]);
    polygon1.push_back(polygon1[1]);
    polygon2.push_back(polygon2[0]);
    polygon2.push_back(polygon2[1]);
    int index1 = 0;
    int index2 = 0;
    while (index1 < polygon1.size() - 2 && index2 < polygon2.size() - 2) {
        answer.push_back(polygon1[index1] + polygon2[index2]);
        // compare angles current points
        double angle = Angle(polygon1[index1], polygon1[index1 + 1]) - Angle(polygon2[index2], polygon2[index2 + 1]);
        if (angle < 0) {
            ++index1;
        } else if (angle > 0) {
            ++index2;
        } else {
            ++index1;
            ++index2;
        }
    }
    answer.push_back(polygon1[index1] + polygon2[index2]);
    answer.push_back(answer[0]);
}

// if there is a common point in two polygons, then (0, 0) will be in the sum
bool ZeroInSum(const std::vector<Vector> &sum) {
    Vector zero(0.0, 0.0);
    for (int i = 0; i < sum.size() - 1; ++i) {
        if ((sum[i + 1]._x - sum[i]._x) * (zero._y - sum[i + 1]._y) - (zero._x - sum[i + 1]._x) * (sum[i + 1]._y - sum[i]._y) < 0) {
            return false;
        }
    }
    return true;
}
int main() {
    int n, m;
    std::vector<Vector> polygon1;
    std::vector<Vector> polygon2;
    std::cin >> n;
    double x, y;
    for (int i = 0; i < n; ++i) {
        std::cin >> x >> y;
        polygon1.emplace_back(x, y);
    }
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        std::cin >> x >> y;
        polygon2.emplace_back(-x, -y);
    }
    if (n == 0 || m == 0)
        std::cout << "NO";
    Reverse(polygon1);
    Reverse(polygon2);
    std::vector<Vector> sum;
    MinkowskiAmount(polygon1, polygon2, sum);
    if (ZeroInSum(sum)) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}