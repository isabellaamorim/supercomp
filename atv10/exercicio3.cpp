%%writefile exercicio3.cu
#include <thrust/device_vector.h>   // Inclui a biblioteca Thrust para vetores na GPU
#include <thrust/host_vector.h>     // Inclui a biblioteca Thrust para vetores na CPU
#include <thrust/extrema.h>         // Inclui a biblioteca Thrust para funções de redução
#include <iostream>                 // Biblioteca padrão para entrada e saída de dados
#include <chrono>                   // Biblioteca para medir o tempo de execução do código
#include <sstream>
using namespace std;

int main() {
    int n = 2518;                   // Define o tamanho do vetor (2518 elementos)
    double value = 0.0;             // Variável auxiliar para armazenar o valor lido da entrada
    string input;                  // Variável auxiliar para armazenar o valor lido da entrada

    // Cria um vetor na CPU (host_vector) com n elementos, todos inicializados com 0
    thrust::host_vector<double> host_apple(n, 0);
    thrust::host_vector<double> host_msft(n, 0);

    // Loop para ler n valores da entrada padrão e armazená-los no vetor host
    for (int i = 0; i < n; i++) {
        getline(cin, input);             // Lê um valor da entrada padrão

        // Cria um stream para manipular a string
        stringstream ss(input);

        // Lê o valor da primeira coluna (APPLE)
        ss >> value;
        host_apple[i] = value;           // Armazena o valor lido no vetor host

        // Lê o valor da segunda coluna (MSFT)
        ss >> value;
        host_msft[i] = value;           // Armazena o valor lido no vetor host
    }

    // Cria um vetor na GPU (device_vector) copiando os dados do vetor host da CPU
    thrust::device_vector<double> dev_apple(host_apple);
    thrust::device_vector<double> dev_msft(host_msft);

    //Diferença entre os vetores (APLPLE - MSFT)
    thrust::device_vector<double> diff_apple_msft(n, 0);
    thrust::transform(dev_apple.begin(), dev_apple.end(), dev_msft.begin(), diff_apple_msft.begin(), thrust::minus<double>());

    //Diferença entre os vetores (MSFT - APLPLE)~
    thrust::device_vector<double> diff_msft_apple(n, 0);
    thrust::transform(dev_msft.begin(), dev_msft.end(), dev_apple.begin(), diff_msft_apple.begin(), thrust::minus<double>());

    //Média da diferença entre os vetores (APLPLE - MSFT)
    float med_apple_msft = thrust::reduce(diff_apple_msft.begin(), diff_apple_msft.end(), 0, thrust::plus<int>()) / n;

    //Média da diferença entre os vetores (MSFT - APLPLE)
    float med_msft_apple = thrust::reduce(diff_msft_apple.begin(), diff_msft_apple.end(), 0, thrust::plus<int>()) / n;

    //Print
    cout << "Média da diferença entre os vetores (APLPLE - MSFT): " << med_apple_msft << endl;
    cout << "Média da diferença entre os vetores (MSFT - APLPLE): " << med_msft_apple << endl;
}