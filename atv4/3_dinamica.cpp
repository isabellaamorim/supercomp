#include <iostream>   // Inclui a biblioteca padrão de entrada e saída, usada para operações como std::cout.
#include <chrono>     // Inclui a biblioteca para medição de tempo, usada para medir a performance do código.

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    int N = 1000;  // Define o tamanho da matriz como N x N, onde N é 1000.

    // Alocação dinâmica de memória para uma matriz N x N.
    // Primeiro, aloca um array de ponteiros, onde cada ponteiro irá apontar para uma linha da matriz.
    int** matriz = new int*[N];

    // Para cada linha da matriz, aloca um array de inteiros de tamanho N.
    for (int i = 0; i < N; ++i) {
        matriz[i] = new int[N];
    }

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

    // Liberação da memória alocada dinamicamente.
    // Primeiro, libera a memória alocada para cada linha (os arrays de inteiros).
    for (int i = 0; i < N; ++i) {
        delete[] matriz[i];
    }

    // Finalmente, libera a memória alocada para o array de ponteiros.
    delete[] matriz;
    
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execução: " << duration.count() << " segundos" << std::endl;
    std::cout << "Soma: " << soma << std::endl;

    return 0;  // Retorna 0, indicando que o programa terminou com sucesso.
}