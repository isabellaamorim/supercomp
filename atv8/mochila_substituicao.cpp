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
    vector<Item> usados;  // Para armazenar itens adicionados
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
                result.usados.push_back(*it); // Adiciona o item na lista de itens usados
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

Resultado mochila_cheia(int capacidade, const vector<Item>& itens, Resultado result){
    for (const auto& item : itens) {
        if (result.peso_total + item.peso <= capacidade) {
            result.peso_total += item.peso;
            result.valor_total += item.valor;
            result.usados.push_back(item); // Adiciona o item na lista de itens usados
        } 
    }
    return result; 
} 

Resultado substituicao(int capacidade, vector<Item>& itens, Resultado result) {
    bool houve_substituicao = true;

    while (houve_substituicao) {
        houve_substituicao = false;

        for (size_t i = 0; i < result.usados.size(); ++i) {
            for (auto it = itens.begin(); it != itens.end(); ++it) {
                // Verifica se a troca é válida e aumenta o valor total
                if (result.peso_total - result.usados[i].peso + it->peso <= capacidade) {
                    int novo_valor_total = result.valor_total - result.usados[i].valor + it->valor;
                    if (novo_valor_total > result.valor_total) {
                        // Faz a substituição
                        result.peso_total = result.peso_total - result.usados[i].peso + it->peso;
                        result.valor_total = novo_valor_total;

                        // Substitui o item usado pelo novo item
                        result.usados[i] = *it;
                        itens.erase(it);  // Remove o item dos itens disponíveis
                        houve_substituicao = true;

                        break;  // Volta ao passo 2 (recomeça as verificações)
                    }
                }
            }
            if (houve_substituicao) {
                break;  // Se houve uma substituição, começa novamente
            }
        }
    }

    return result;
}

int main() {
    ifstream inputFile("Entrada_2.txt");

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
    Resultado result_cheia = mochila_cheia(capacidade, itens, result);
    Resultado result_final = substituicao(capacidade, itens, result_cheia);

    cout << "Peso ocupado: " << result_final.peso_total << "; Valor total: " << result_final.valor_total << endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tempo de execucao: " << duration.count() << " segundos" << std::endl;

    inputFile.close();
    return 0;
}
