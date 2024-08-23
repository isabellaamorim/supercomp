#include <iostream>
#include <vector>

class Vector {
public:
    Vector(int tamanho);
    ~Vector();
    void inicializa(int valor);
    int get(int index) const;
    void set(int index, int valor);
    void inserir(int index, int valor);
    void remover(int index);
    void imprime() const;

private:
    int* dados;
    int tam;
    int capacidade;
    void redimensiona(int novaCapacidade);
};

// Implementação das funções...
Vector::Vector(int tamanho) {
    tam = tamanho;
    capacidade = tamanho;
    dados = new int[capacidade];
}

Vector::~Vector() {
    delete[] dados;
}

void Vector::inicializa(int valor) {
    for (int i = 0; i < tam; ++i) {
        dados[i] = valor;
    }
}

int Vector::get(int index) const {
    if (index >= 0 && index < tam) {
        return dados[index];
    }
    std::cerr << "Index fora do intervalo!" << std::endl;
    return -1;
}

void Vector::set(int index, int valor) {
    if (index >= 0 && index < tam) {
        dados[index] = valor;
    } else {
        std::cerr << "Index fora do intervalo!" << std::endl;
    }
}

void Vector::inserir(int index, int valor) {
    if (index < 0 || index > tam) {
        std::cerr << "Index fora do intervalo!" << std::endl;
        return;
    }

    if (tam == capacidade) {
        redimensiona(capacidade * 2);
    }

    for (int i = tam; i > index; --i) {
        dados[i] = dados[i - 1];
    }

    dados[index] = valor;
    ++tam;
}

void Vector::remover(int index) {
    if (index < 0 || index >= tam) {
        std::cerr << "Index fora do intervalo!" << std::endl;
        return;
    }

    for (int i = index; i < tam - 1; ++i) {
        dados[i] = dados[i + 1];
    }

    --tam;

    if (tam < capacidade / 2) {
        redimensiona(capacidade / 2);
    }
}

void Vector::imprime() const {
    for (int i = 0; i < tam; ++i) {
        std::cout << dados[i] << " ";
    }
    std::cout << std::endl;
}

void Vector::redimensiona(int novaCapacidade) {
    int* novoArray = new int[novaCapacidade];
    for (int i = 0; i < tam; ++i) {
        novoArray[i] = dados[i];
    }
    delete[] dados;
    dados = novoArray;
    capacidade = novaCapacidade;
}

int main() {
    Vector vec(5);
    vec.inicializa(0);
    vec.imprime();

    return 0;
}