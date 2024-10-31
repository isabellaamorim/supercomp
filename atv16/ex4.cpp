#include <iostream>
#include <mpi.h>
#include <vector>
#include <numeric>  // Para std::accumulate
#include <cstdlib>  // Para rand e srand
#include <ctime>    // Para time (seeding do rand)

using namespace std;

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Número total de processos

    const int array_size = 100;  // Tamanho do array total
    int chunk_size = array_size / size;  // Tamanho do chunk para cada processo

    vector<int> array(array_size);
    vector<int> local_array(chunk_size);

    if (rank == 0) {
        // Inicializa o array com valores aleatórios no processo raiz
        srand(time(0));
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 100;  // Valores aleatórios entre 0 e 99
        }
    }

    // Distribui o array para todos os processos
    MPI_Scatter(array.data(), chunk_size, MPI_INT, local_array.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcula a média local do chunk recebido
    double local_sum = accumulate(local_array.begin(), local_array.end(), 0);
    double local_mean = local_sum / chunk_size;

    // Calcula a variação local
    double local_variance_sum = 0.0;
    for (int i = 0; i < chunk_size; i++) {
        local_variance_sum += pow(local_array[i] - local_mean, 2);
    }
    double local_variance = local_variance_sum / chunk_size;

    // Coleta todas as médias locais e variâncias locais no processo raiz
    vector<double> local_means(size);
    vector<double> local_variances(size);
    MPI_Gather(&local_mean, 1, MPI_DOUBLE, local_means.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&local_variance, 1, MPI_DOUBLE, local_variances.data(), 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Calcula a média global
        double global_mean = accumulate(local_means.begin(), local_means.end(), 0.0) / size;

        // Calcula a variância global
        double global_variance = 0.0;
        for (int i = 0; i < size; i++) {
            global_variance += local_variances[i];
            global_variance += pow(local_means[i] - global_mean, 2) * chunk_size;
        }
        global_variance /= array_size;

        // Calcula o desvio padrão global
        double global_std_dev = sqrt(global_variance);
        cout << "Desvio padrão global: " << global_std_dev << endl;
    }

    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;
}