#include <iostream>
#include <mpi.h>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    // Pega o rank do processo
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Pega o número de processos
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char msg[100];

    if (rank == 0) {
        strcpy(msg, "Olá");
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

    } else {
        // Recebe a mensagem do processo anterior
        MPI_Recv(msg, 100, MPI_CHAR, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Se não for o último processo, envia para o próximo
        if (rank < size - 1) {
            MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, rank + 1, 0, MPI_COMM_WORLD);
            
        } else { // Se for o último processo, imprime a mensagem
            cout << "Processo " << rank << " recebeu: " << msg << " do processo " << rank - 1 << endl;
        }
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}