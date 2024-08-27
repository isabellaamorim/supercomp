#!/bin/bash
#SBATCH --job-name=convolucao_testes    # Nome do job
#SBATCH --output=convolucao_%j.txt   # Gera um novo arquivo de saída a cada execução
#SBATCH --ntasks=2                               # Número de tarefas (apenas 1 processos)
#SBATCH --cpus-per-task=4                        # Número de threads por tarefa (apenas 1 thread por processo)
#SBATCH --mem=1024                             # Memória total alocada por nó (1024 MB)
#SBATCH --time=00:10:00                          # Tempo máximo de execução (até 10 minutos)
#SBATCH --partition=espec                       # Fila do cluster a ser utilizada

# Exporta a variável de ambiente para configurar o número de threads OpenMP
export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Executa o programa usando MPI e OpenMP
./convolucao_O3
