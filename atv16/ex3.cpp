#include <iostream>
#include <mpi.h>
#include <vector>
#include <algorithm>  // Para std::max_element
#include <cstdlib>    // Para rand() e srand()
#include <ctime>      // Para time() (seeding do rand)

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

    int max_value;

    if (rank == 0) {
        srand(time(0));
        for (int i = 0; i < array_size; i++) {
            array[i] = rand() % 100 + 1;  // Valores aleatórios entre 1 e 100
        }

        max_value = *max_element(array.begin(), array.end());

        cout << "Valor máximo: " << max_value << endl;
    }

    //Envia valor máximo para todos os processos
    MPI_Bcast(&max_value, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Distribui o array para todos os processos
    MPI_Scatter(array.data(), chunk_size, MPI_INT, local_array.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo normaliza seu array
    vector<float> local_normalized(chunk_size);
    for (int i = 0; i < chunk_size; i++) {
        local_normalized[i] = static_cast<float>(local_array[i]) / max_value;
    }

    // Coleta todos os arrays normalizados no processo raiz
    vector<float> normalized_array;
    if (rank == 0) {
        normalized_array.resize(array_size);
    }

    MPI_Gather(local_normalized.data(), chunk_size, MPI_FLOAT, normalized_array.data(), chunk_size, MPI_FLOAT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        cout << "Array normalizado:" << endl;
        for (int i = 0; i < array_size; i++) {
            cout << normalized_array[i] << " ";
        }
        cout << endl;
    }

    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;
}