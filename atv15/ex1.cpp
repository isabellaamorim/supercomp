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

    if (rank == 0){
        // Processo 0 envia Olá para o processo 1
        const char* msg = "Olá";
        MPI_Send(msg, strlen(msg) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
        cout << "Processo 0 enviou: " << msg << endl;

        // Processo 0 recebe a mensagem do processo 1
        char resposta[10];
        MPI_Recv(resposta, 10, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo 0 recebeu: " << resposta << endl;
    } else if (rank == 1) {
        // Processo 1 recebe a mensagem do processo 0
        char msg[10];
        MPI_Recv(msg, 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo 1 recebeu: " << msg << endl;

        // Processo 1 envia Oi para o processo 0
        const char* resposta = "Oi";
        MPI_Send(resposta, strlen(resposta) + 1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        cout << "Processo 1 enviou: " << resposta << endl;
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}