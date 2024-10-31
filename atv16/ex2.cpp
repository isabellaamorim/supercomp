#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
    // Inicializa o ambiente MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Rank do processo
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Número total de processos

    int num_iteracoes;

    if (rank == 0) {
        // Processo raiz define o número de iterações para o cálculo
        num_iteracoes = 100;
        cout << "Processo raiz definiu num_iteracoes = " << num_iteracoes << endl;
    }

    // Processo raiz envia o número de iterações para todos os outros processos
    MPI_Bcast(&num_iteracoes, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Cada processo executa um cálculo usando o número de iterações
    int resultado_local = 0;
    for (int i = 0; i < num_iteracoes; i++) {
        resultado_local += rank + i;  // Exemplo de cálculo: soma rank + i em cada iteração
    }

    // Cada processo imprime seu resultado local
    cout << "Processo " << rank << " terminou com resultado_local = " << resultado_local << endl;

    MPI_Finalize();  // Finaliza o ambiente MPI
    return 0;
}