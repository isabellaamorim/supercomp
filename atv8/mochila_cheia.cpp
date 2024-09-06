#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::random_device e std::mt19937
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

Resultado mochila_probabilidade(int capacidade, vector<Item>& itens) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    Resultado result;
    auto it = itens.begin();

    while (it != itens.end()) {
        double random_value = dis(gen);

        if (random_value >= 0.5) {  // Solução aleatória: probabilidade
            if (result.peso_total + it->peso <= capacidade) {
                result.peso_total += it->peso;
                result.valor_total += it->valor;
                it = itens.erase(it);  // Remove o item da lista e atualiza o iterador
            } else {
                ++it;  // Avança o iterador apenas se o item não for adicionado
            }
        } else {
            ++it;  // Avança o iterador se o item não for escolhido aleatoriamente
        }
    }
    return result;
}

//Percorre os itens restantes e adiciona na mochila
Resultado mochila_cheia(int capacidade, const vector<Item>& itens, Resultado result){ 
    for (const auto& item : itens) {
        if (result.peso_total + item.peso <= capacidade) {
            result.peso_total += item.peso;
            result.valor_total += item.valor;
        } 
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
    
    auto start = std::chrono::high_resolution_clock::now();

    Resultado result = mochila_probabilidade(capacidade, itens);
    Resultado result_final = mochila_cheia(capacidade, itens, result);
    cout << "Peso ocupado: " << result_final.peso_total << "; Valor total: " << result_final.valor_total << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;

    inputFile.close();
    return 0;
}
