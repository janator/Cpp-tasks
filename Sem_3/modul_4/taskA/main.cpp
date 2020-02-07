#include <iostream>
#include <string>
#include <vector>
#include "biginteger.h"


int main() {
    for (int i = 0; i < 10; ++i) {
        BigInteger A, B, C, D;
        /*std::cin >> A >> B;
        std::cout << A << " " << ++A << " " << A++ << " " << A << " " << -A << " ";
        A += B;
        C = A / B;
        D = A % B;
        std::cout << C << " " << D << " " << ++D << std::endl;*/
        std::cin >> A >> B;
        std::cout << (A == B);
    }
     return 0;
}