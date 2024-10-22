%%writefile saxpy.cu
#include <thrust/device_vector.h>   // Inclui a biblioteca Thrust para vetores na GPU
#include <thrust/host_vector.h>     // Inclui a biblioteca Thrust para vetores na CPU
#include <thrust/extrema.h>         // Inclui a biblioteca Thrust para funções de redução
#include <iostream>                 // Biblioteca padrão para entrada e saída de dados
#include <chrono>                   // Biblioteca para medir o tempo de execução do código
#include <sstream>
using namespace std;

struct saxpy
{
    int a;    
    saxpy(int a_) : a(a_) {};  // Construtor que inicializa a constante 'a'

    __host__ __device__
    double operator()(const int& x, const int& y) const {
        return a * x + y;  // Operação que será aplicada a cada elemento de x e y
    }
};

int main() {
    int n = 2518;                   // Define o tamanho do vetor (2518 elementos)
    double value = 0.0;             // Variável auxiliar para armazenar o valor lido da entrada
    string input;                  // Variável auxiliar para armazenar o valor lido da entrada

    // Cria um vetor na GPU (device_vector) com n elementos, todos inicializados com 0
    thrust::device_vector<double> dev_apple(n, 0);
    thrust::device_vector<double> dev_msft(n, 0);

    // Loop para ler n valores da entrada padrão e armazená-los no vetor host
    for (int i = 0; i < n; i++) {
        getline(cin, input);             // Lê um valor da entrada padrão

        // Cria um stream para manipular a string
        stringstream ss(input);

        // Lê o valor da primeira coluna (APPLE)
        ss >> value;
        dev_apple[i] = value;           // Armazena o valor lido no vetor host

        // Lê o valor da segunda coluna (MSFT)
        ss >> value;
        dev_msft[i] = value;           // Armazena o valor lido no vetor host
    }

    // Cria um vetor na GPU (device_vector) copiando os dados do vetor host da CPU
    //thrust::device_vector<double> dev_apple(host_apple);
    //thrust::device_vector<double> dev_msft(host_msft);

    // Define a constante 'a' para a operação SAXPY
    int a = 100;

    //Vetor que armazenará o resultado da operação SAXPY
    thrust::device_vector<double> dev_result(n, 0);

    // Marca o início da operação
    auto start = std::chrono::high_resolution_clock::now();

    // Aplica a operação SAXPY nos vetores dev_apple e dev_msft
    thrust::transform(dev_apple.begin(), dev_apple.end(), dev_msft.begin(), dev_result.begin(), saxpy(a));

    //Copia o resultado de volta para a CPU
    thrust::host_vector<double> host_result(dev_result);

    // Marca o fim da operação
    auto end = std::chrono::high_resolution_clock::now();

    // Calcula o tempo de execução da operação
    std::chrono::duration<double> duration = end - start;

    // Print
    cout << "Tempo de execução: " << duration.count() << "s" << endl;
}