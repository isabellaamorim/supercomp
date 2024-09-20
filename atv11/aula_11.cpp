%%writefile aula11.cu
#include <iostream>                 // Biblioteca padrão para entrada e saída de dados
#include <thrust/device_vector.h>   // Inclui a biblioteca Thrust para vetores na GPU
#include <thrust/host_vector.h>     // Inclui a biblioteca Thrust para vetores na CPU
#include <thrust/extrema.h>         // Inclui a biblioteca Thrust para funções de redução
#include <thrust/transform.h>       // Inclui a biblioteca Thrust para funções de transformação
#include <thrust/reduce.h>          // Inclui a biblioteca Thrust para redução
#include <thrust/functional.h>      // Inclui funções de placeholders e operações
#include <thrust/count.h>

using namespace std;

//Difference Functor 
struct difference_functor {
    __host__ __device__
    float operator()(const float& x1, const float& x2) const {
        return x1 - x2;
    }
};

//Variance Functor
struct variance_functor {
    const float mean;
    variance_functor(float _mean) : mean(_mean) {}
    __host__ __device__
    float operator()(const float& x) const {
        return (x - mean) * (x - mean);
    }
};

int main() {
    int n = 2518;                   // Define o tamanho do vetor (2518 elementos)
    double value = 0.0;             // Variável auxiliar para armazenar o valor lido da entrada

    // Cria um vetor na CPU (host_vector) com n elementos, todos inicializados com 0
    thrust::host_vector<double> host(n, 0);

    // Loop para ler n valores da entrada padrão e armazená-los no vetor host
    for (int i = 0; i < n; i++) {
        cin >> value;              // Lê um valor da entrada padrão
        host[i] = value;           // Armazena o valor lido no vetor host
    }

    // Cria um vetor na GPU (device_vector) copiando os dados do vetor host da CPU
    thrust::device_vector<double> dev(host);

    //Calcula a média
    float sum= thrust::reduce(dev.begin(), dev.end(), 0, thrust::plus<int>());
    float media = sum / dev.size();

    //Calcula a variância
    float variance = thrust::transform_reduce(
        dev.begin(), dev.end(), 
        variance_functor(media), //Calcula (x - media)^2
        0.0f,                    //Valor incial da soma
        thrust::plus<float>()    //Operação de soma
    ) / dev.size();

    //Print
    cout << "Variância: " << variance << endl;

    //Cria vetor de diferenças
    thrust::device_vector<double> ganho_diario(n-1);

    //Calcula diferenças
    thrust::transform(dev.begin(), dev.end() - 1, dev.begin() + 1, ganho_diario.begin(), difference_functor());

    //Print 15 itens
    for (int i = 0; i < 15; i++) {
        cout << "Ganho diário: " << ganho_diario[i] << endl;
    }

    //Conta quantos dias tiveram ganho
    int dias_ganho = thrust::count_if(ganho_diario.begin(), ganho_diario.end(), [] __host__ __device__ (double x) {
        return x > 0;
    });

    //Print
    cout << "Dias com ganho: " << dias_ganho << endl;

    //Substitui valores negativos por 0
    thrust::replace_if(ganho_diario.begin(), ganho_diario.end(), [] __host__ __device__ (double x) { return x < 0; }, 0);

    //Soma vetor ganho_diario positivos 
    float ganho_total = thrust::reduce(ganho_diario.begin(), ganho_diario.end(), 0, thrust::plus<float>());
    float aumento_medio = ganho_total / dias_ganho;

    //Print
    cout << "Aumento médio: " << aumento_medio << endl;

    return 0;
}