#include <iostream>
#include <mpi.h>
#include <cstring>

using namespace std;

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Número total de processos

    char msg[100];

    if (rank == 0) {
        for (int i = 1; i < size; i++) {
            // Processo 0 envia uma mensagem para o processo i
            strcpy(msg, "Olá");
            MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            cout << "Processo 0 enviou: " << msg << " para o processo " << i << endl;

            // Processo 0 aguarda uma resposta do processo i
            MPI_Recv(msg, 100, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cout << "Processo 0 recebeu: " << msg << " do processo " << i << endl;
        }
    } else {
        // Cada processo i (onde i != 0) recebe uma mensagem do processo 0
        MPI_Recv(msg, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo " << rank << " recebeu: " << msg << " do processo 0" << endl;

        // Cada processo i responde de volta para o processo 0
        strcpy(msg, "Olá");
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        cout << "Processo " << rank << " enviou: " << msg << " para o processo 0" << endl;
    }

    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;
}