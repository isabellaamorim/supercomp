#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>   

using namespace std;

int mochila_binaria(int capacidade, const vector<int>& pesos, const vector<int>& valores, int n) {
    if (n == 0 || capacidade == 0) {
        return 0;
    }

    if (pesos[n - 1] > capacidade) {
        return mochila_binaria(capacidade, pesos, valores, n - 1);
    } else {
        return max(valores[n-1] + mochila_binaria(capacidade - pesos[n-1], pesos, valores, n - 1), mochila_binaria(capacidade, pesos, valores, n - 1));
    }
} 

int main() {
    ifstream inputFile("Entrada_1.txt");

    if (!inputFile) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int n_objetos, capacidade, peso, valor; 
    inputFile >> n_objetos >> capacidade;

    vector<int> pesos(n_objetos);
    vector<int> valores(n_objetos);

    for (int i = 0; i < n_objetos; ++i) {
        inputFile >> pesos[i] >> valores[i];
    }
    
    auto start = std::chrono::high_resolution_clock::now();

    int valor_max = mochila_binaria(capacidade, pesos, valores, n_objetos);
    cout << "Valor max: " << valor_max << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;

    inputFile.close();
    return 0;
}
