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

    if (size < 2) {
        cout << "Este programa precisa de mais de 2 processos" << endl;
        MPI_Finalize();
        return 1;
    }

    int msg = rank;

    if (rank == 0){
        //Envia a msg para o processo 1
        MPI_Send(&msg, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        cout << "Processo 0 enviou " << msg << " para o processo 1" << endl;

        //Recebe a msg do último processo
        MPI_Recv(&msg, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo 0 recebeu " << msg << " do processo " << size - 1 << endl;
    } else {
        //Recebe a msg do processo anterior
        MPI_Recv(&msg, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "Processo " << rank << " recebeu " << msg << " do processo " << rank - 1 << endl;

        msg ++;

        //último processo envia para o processo 0
        if (rank == size - 1) { 
            MPI_Send(&msg, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            cout << "Processo " << rank << " enviou " << msg << " para o processo 0" << endl;
        } else {
            MPI_Send(&msg, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            cout << "Processo " << rank << " enviou " << msg << " para o processo " << rank + 1 << endl;
        }
    }

    // Finaliza o ambiente MPI
    MPI_Finalize();
    return 0;
}