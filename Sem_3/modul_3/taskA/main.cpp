#include <iostream>
#include <cmath>
#include <iomanip>

const double eps = 0.00000001;

class Vector {
public:
    Vector(double x, double y, double z) : _x(x), _y(y), _z(z) {}

    Vector(double x1, double y1, double z1, double x2, double y2, double z2) :
            _x(x2 - x1), _y(y2 - y1), _z(z2 - z1) {}

    Vector operator+(const Vector &other) const {
        return {this->_x + other._x, this->_y + other._y, this->_z + other._z};
    }

    Vector operator*(double a) const {
        return {this->_x * a, this->_y * a, this->_z * a};
    }

    double Dot(const Vector &other) const {
        return (this->_x * other._x + this->_y * other._y + this->_z * other._z);
    }

    // Квадрат длины вектора
    double Norm() const {
        return this->Dot(*this);
    }

    // Квадрат модуля векторного произведения
    double Cross(const Vector &other) const {
        return (this->Norm() * other.Norm() - this->Dot(other) * this->Dot(other));
    }

private:
    double _x;
    double _y;
    double _z;
};

double DistanceBetweenLines(const Vector &vector_1, const Vector &vector_2, const Vector &vector_3) {
    double t_comp1, s_comp1; // tN, SN
    double t_comp2 = vector_1.Norm() * vector_2.Norm() - vector_2.Dot(vector_1) * vector_2.Dot(vector_1);
    double s_comp2 = vector_1.Norm() * vector_2.Norm() - vector_2.Dot(vector_1) * vector_2.Dot(vector_1); // tD, SD
    if (vector_1.Norm() * vector_2.Norm() - vector_2.Dot(vector_1) * vector_2.Dot(vector_1) <= eps) {
        s_comp1 = 0.0;
        s_comp2 = 1.0;
        t_comp1 = vector_2.Dot(vector_3);
        t_comp2 = vector_2.Norm();
    } else {
        s_comp1 = vector_1.Dot(vector_2) * vector_2.Dot(vector_3) - vector_2.Norm() * vector_1.Dot(vector_3);
        t_comp1 = vector_1.Norm() * vector_2.Dot(vector_3) - vector_1.Dot(vector_2) * vector_1.Dot(vector_3);
        if (s_comp1 <= 0.0) {
            s_comp1 = 0.0;
            t_comp1 = vector_2.Dot(vector_3);
            t_comp2 = vector_2.Norm();
        } else if (s_comp1 >= s_comp2) {
            s_comp1 = s_comp2;
            t_comp1 = vector_2.Dot(vector_3) + vector_1.Dot(vector_2);
            t_comp2 = vector_2.Norm();
        }
    }

    if (t_comp1 <= 0.0) {
        t_comp1 = 0.0;
        if (vector_1.Dot(vector_3) * (-1) <= 0.0) {
            s_comp1 = 0.0;
        } else if (vector_1.Dot(vector_3) * (-1) >= vector_1.Norm()) {
            s_comp1 = s_comp2;
        } else {
            s_comp1 = vector_1.Dot(vector_3) * (-1);
            s_comp2 = vector_1.Norm();
        }
    } else if (t_comp1 >= t_comp2) {
        t_comp1 = t_comp2;
        if (vector_1.Dot(vector_2) - vector_1.Dot(vector_3) <= 0.0) {
            s_comp1 = 0.0;
        } else if (vector_1.Dot(vector_2) - vector_1.Dot(vector_3) >= vector_1.Norm()) {
            s_comp1 = s_comp2;
        } else {
            s_comp1 = vector_1.Dot(vector_2) - vector_1.Dot(vector_3);
            s_comp2 = vector_1.Norm();
        }
    }
    double comp1 = std::fabs(s_comp1) <= eps ? 0.0 : s_comp1 / s_comp2;
    double comp2 = std::fabs(t_comp1) <= eps ? 0.0 : t_comp1 / t_comp2;
    Vector distance = vector_3 + vector_1 * comp1 + vector_2 * (-1) * comp2;
    return std::sqrt(distance.Norm());
}

int main() {
    double x1, x2, x3, x4;
    double y1, y2, y3, y4;
    double z1, z2, z3, z4;
    std::cin >> x1 >> y1 >> z1;
    std::cin >> x2 >> y2 >> z2;
    std::cin >> x3 >> y3 >> z3;
    std::cin >> x4 >> y4 >> z4;
    std::cout << std::fixed;
    std::cout << std::setprecision(999);
    Vector vector1(x1, y1, z1, x2, y2, z2);
    Vector vector2(x3, y3, z3, x4, y4, z4);
    Vector vector3(x3, y3, z3, x1, y1, z1);
    std::cout << DistanceBetweenLines(vector1, vector2, vector3);
    return 0;
}