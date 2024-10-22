#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <chrono>                   // Biblioteca para medir o tempo de execução do código
#include <omp.h>        // Inclui a biblioteca OpenMP, usada para paralelismo em C++.

int main() {
    // Início da contagem do tempo de execução
    auto start = std::chrono::high_resolution_clock::now();

    int N = 100000; // Número de pontos aleatórios
    int points_inside_circle = 0;
    double x, y;
    
    // Semente para o gerador de números aleatórios
    std::srand(std::time(0));

    // Parallell loop using OpenMP
    #pragma omp parallel for reduction(+:points_inside_circle) private(x, y)
    for (int i = 0; i < N; ++i) {
        // Gerando coordenadas x e y aleatórias entre 0 e 1
        x = static_cast<double>(std::rand()) / RAND_MAX;
        y = static_cast<double>(std::rand()) / RAND_MAX;

        // Verificando se o ponto está dentro do círculo
        if (x * x + y * y <= 1.0) {
            points_inside_circle++;
        }
    }

    // Estimando o valor de Pi
    double pi_estimate = 4.0 * points_inside_circle / N;

    std::cout << "Estimativa de Pi: " << pi_estimate << std::endl;

    // Fim da contagem do tempo de execução
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Tempo de execucao: " << elapsed.count() << "s" << std::endl;

    return 0;
}
