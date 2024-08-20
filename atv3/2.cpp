#include <iostream>

using namespace std;

int main() {
    int n1, n2;
    char operation;

    std::cout << "Digite um inteiro:" << endl;
    std::cin >> n1;
    std::cout << "Digite outro inteiro:" << endl;
    std::cin >> n2;
    std::cout << "Digite uma operacao (+,-,/,*):" << endl;
    std::cin >> operation;

    if (operation == '+') {
        std::cout << n1 + n2 << std::endl;
    } else if (operation == '-') {
        std::cout << n1 - n2 << std::endl;
    } else if (operation == '*') {
        std::cout << n1 * n2 << std::endl;
    } else if (operation == '/') {
        std::cout << n1 / n2 << std::endl;
    } else {
        std::cout << "Invalid operation" << std::endl;
    }

}