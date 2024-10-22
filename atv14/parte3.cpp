//Para compilar: g++ -fopenmp parte3.cpp -o parte3

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <chrono>                   // Biblioteca para medir o tempo de execução do código
#include <omp.h>        // Inclui a biblioteca OpenMP, usada para paralelismo em C++.
#include <random>

int main() {
    // Início da contagem do tempo de execução
    auto start = std::chrono::high_resolution_clock::now();

    int N = 100000; // Número de pontos aleatórios
    int points_inside_circle = 0;

    #pragma omp parallel reduction(+:points_inside_circle)
    {
        // Criando um gerador de números aleatórios para cada thread
        std::random_device rd; // Para obter um seed único
        std::mt19937 gen(rd() ^ omp_get_thread_num()); // Gerador de números aleatórios com seed único para cada thread
        std::uniform_real_distribution<> dis(0.0, 1.0); // Distribuição uniforme entre 0 e 1

        // Cada thread executa uma parte do loop
        #pragma omp for
        for (int i = 0; i < N; ++i) {
            double x = dis(gen);
            double y = dis(gen);

            // Verificando se o ponto está dentro do círculo
            if (x * x + y * y <= 1.0) {
                points_inside_circle++;
            }
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