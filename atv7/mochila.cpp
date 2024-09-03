#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>   

using namespace std;

struct Item {
    int peso;
    int valor;
};

struct Resultado {
    int peso_total = 0;
    int valor_total = 0;
};


Resultado mochila_binaria(int capacidade, const vector<Item>& itens, int n) {
    if (n == 0 || capacidade == 0) {
        return {0, 0}; 
    }

    if (itens[n - 1].peso > capacidade) {
        return mochila_binaria(capacidade, itens, n - 1);
    } else {
        Resultado incluir = mochila_binaria(capacidade - itens[n - 1].peso, itens, n - 1);
        incluir.peso_total += itens[n - 1].peso;
        incluir.valor_total += itens[n - 1].valor;

        Resultado excluir = mochila_binaria(capacidade, itens, n - 1);

        if (incluir.valor_total > excluir.valor_total) {
            return incluir;
        } else {
            return excluir;
        }
    }
}

int main() {
    ifstream inputFile("Entrada_4.txt");

    if (!inputFile) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int n_objetos, capacidade, peso, valor; 
    inputFile >> n_objetos >> capacidade;

    vector<Item> itens(n_objetos);

    for (int i = 0; i < n_objetos; ++i) {
        inputFile >> itens[i].peso >> itens[i].valor;
    }
    
    auto start = std::chrono::high_resolution_clock::now();

    Resultado result = mochila_binaria(capacidade, itens, n_objetos);
    cout << "Peso ocupado: " << result.peso_total << "; Valor total: " << result.valor_total << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;

    inputFile.close();
    return 0;
}
