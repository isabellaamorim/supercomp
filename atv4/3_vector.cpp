#include <iostream>   // Inclui a biblioteca padrão de entrada e saída, usada para operações como std::cout.
#include <chrono>     // Inclui a biblioteca para medição de tempo, usada para medir a performance do código.
#include <vector>

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    int N = 1000;  // Define o tamanho da matriz como N x N, onde N é 1000.

    //Aloca Matriz utilizando vector
    std::vector<std::vector<int>> matriz(N, std::vector<int>(N));

    // Aqui você pode inicializar e somar os elementos da matriz.
    // Por exemplo, você pode preencher a matriz com valores e calcular a soma total.
    
    int soma = 0;
    for (size_t i = 0; i < N; ++i) {
        // Itera sobre as linhas da matriz
        for (size_t j = 0; j < N; ++j) {
            // Preenche a matriz com valores como a soma dos índices i e j.
            matriz[i][j] = i + j;
            //Adiciona à soma o valor de matriz[i][j]
            soma += matriz[i][j];
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;
    std::cout << "Soma: " << soma << std::endl;
    
    return 0;  // Retorna 0, indicando que o programa terminou com sucesso.
}