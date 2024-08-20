#include <iostream>

using namespace std;

//Soma diagonal principal
int main() {
    int matriz[3][3];
    int soma = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << "Digite o valor da posicao [" << i << "][" << j << "]: "<< endl;
            std::cin >> matriz[i][j];
            if (i == j) {
                soma += matriz[i][j];
            }
        }
    }

    std::cout << "A soma da diagonal principal eh " << soma << std::endl;
}