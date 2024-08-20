#include <iostream>

using namespace std;

int main() {
    int vetor[5];
    int sum = 0;

    for (int i = 0; i < 5; i++) {
        std::cin >> vetor[i];
        sum += vetor[i];
    }

    std::cout << "A soma eh igual a " << sum << std::endl;
}