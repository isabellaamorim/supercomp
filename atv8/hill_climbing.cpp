#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>  
#include <string>
#include <random> 

using namespace std;

struct Item {
    int peso;
    int valor;
};

struct Resultado {
    int peso_total = 0;
    int valor_total = 0;
};

string gerar_vizinho(const std::string &s, int i) {
    string vizinho = s;
    vizinho[i] = (s[i] == '0') ? '1' : '0';
    return vizinho;
}

Resultado hill_climbing(int n_objetos, int capacidade, vector<Item>& itens, string binario) {
    Resultado result;
    Resultado new_result;

    int i;
    for (int i = 0; i < n_objetos; ++i) {
        new_result.peso_total = 0;
        new_result.valor_total = 0;
        for (int j = 0; j < n_objetos; ++j) {
            if (binario[j] == '1') {
                if (new_result.peso_total + itens[j].peso <= capacidade) {
                    new_result.peso_total += itens[j].peso;
                    new_result.valor_total += itens[j].valor;
                } 
            }
        }

        if (new_result.valor_total > result.valor_total) {
            result = new_result;
        }

        binario = gerar_vizinho(binario, i);
    }

    return result;

}

int main() {
    ifstream inputFile("Entrada_3.txt");

    if (!inputFile) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    int n_objetos, capacidade;
    inputFile >> n_objetos >> capacidade;

    vector<Item> itens(n_objetos);

    for (int i = 0; i < n_objetos; ++i) {
        inputFile >> itens[i].peso >> itens[i].valor;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 100);

    string binario_inicial = "";
    for (int i = 0; i < n_objetos; ++i) {
        int random_number = dis(gen);
        binario_inicial += (random_number % 2 == 0) ? '0' : '1';
    }

    auto start = std::chrono::high_resolution_clock::now();

    Resultado result = hill_climbing(n_objetos, capacidade, itens, binario_inicial);
    cout << "Peso ocupado: " << result.peso_total << "; Valor total: " << result.valor_total << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;

    inputFile.close();
    return 0;
}