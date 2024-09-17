%%writefile exercicio2.cu
#include <thrust/device_vector.h>   // Inclui a biblioteca Thrust para vetores na GPU
#include <thrust/host_vector.h>     // Inclui a biblioteca Thrust para vetores na CPU
#include <thrust/extrema.h>         // Inclui a biblioteca Thrust para funções de redução
#include <iostream>                 // Biblioteca padrão para entrada e saída de dados
#include <chrono>                   // Biblioteca para medir o tempo de execução do código
using namespace std;

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

    //Calcula a média dos últimos 10 anos
    int sum_10_anos = thrust::reduce(dev.begin(), dev.end(), 0, thrust::plus<int>());
    int media_10_anos = sum_10_anos / dev.size();

    // Calcula a média dos últimos 365 dias
    int sum_365_dias = thrust::reduce(dev.end() - 365, dev.end(), 0, thrust::plus<int>());
    int media_365_dias = sum_365_dias / 365;

    //Maior preço do período total
    int max_preco = *thrust::max_element(dev.begin(), dev.end());

    //Menor preço do período total
    int min_preco = *thrust::min_element(dev.begin(), dev.end());

    //Maior preço do último ano
    int max_preco_ultimo_ano = *thrust::max_element(dev.end() - 365, dev.end());

    //Menor preço do último ano
    int min_preco_ultimo_ano = *thrust::min_element(dev.end() - 365, dev.end());

    //Print 
    cout << "Média dos últimos 10 anos: " << media_10_anos << endl;
    cout << "Média dos últimos 365 dias: " << media_365_dias << endl;
    cout << "Maior preço do período total: " << max_preco << endl;
    cout << "Menor preço do período total: " << min_preco << endl;
    cout << "Maior preço do último ano: " << max_preco_ultimo_ano << endl;
    cout << "Menor preço do último ano: " << min_preco_ultimo_ano << endl;

    return 0;
}