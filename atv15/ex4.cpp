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

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            char msg[100];
            sprintf(msg, "Oi processo %d", i);
            MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }
    else {
        char msg[100];
        MPI_Recv(msg, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo " << rank << " recebeu: " << msg << endl;
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}