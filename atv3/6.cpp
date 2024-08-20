#include <iostream>

using namespace std;

int main() {
    int vetor[10];
    int maior;

    for (int i = 0; i < 10; i++) {
        std::cin >> vetor[i];
        if (i == 0 || vetor[i] > maior) {
            maior = vetor[i];
        }
    }

    std::cout << "O maior numero eh " << maior << std::endl;
}