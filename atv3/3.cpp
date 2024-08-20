#include <iostream>

int main() {
    int n;
    std::cin >> n;

    if (n % 2 == 0) {
        std::cout << "Par" << std::endl;
    } else {
        std::cout << "Impar" << std::endl;
    }
}