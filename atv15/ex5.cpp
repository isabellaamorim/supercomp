#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Número total de processos

    int valor_exclusivo = rank * 10;
    int soma = 0;

    if (rank == 0) {
        MPI_Send(&valor_exclusivo, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    } else {
        // Recebe a soma acumulada do processo anterior
        MPI_Recv(&soma, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // Adiciona seu valor exclusivo à soma acumulada
        soma += valor_exclusivo;
        
        // Se não for o último processo, envia a soma acumulada para o próximo
        if (rank < size - 1) {
            MPI_Send(&soma, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        } else {
            // Último processo exibe a soma total
            cout << "Processo " << rank << " recebeu a soma total: " << soma << endl;
        }
    }

    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;


}