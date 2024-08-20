#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 

using namespace std;

int main() {
    vector<string> estoque;

    bool status = true;
    string action;
    string add_element;
    string del_element;

    while (status) {

        cout << "Acao: (add, delete or view)"<< endl;
        std::cin >> action;

        if (action == "add") {
            cout << "Elemento a adicionar: "<< endl;
            std::cin >> add_element;

            estoque.push_back(add_element);
        }

        else if (action == "delete") {
            cout << "Elemento a remover: "<< endl;
            std::cin >> del_element;

            auto it = std::find(estoque.begin(), estoque.end(), 
                        del_element); 

            if (it != estoque.end()) { 
                estoque.erase(it); 
            } else {
                cout << "Elemento nao esta no estoque."<< endl;
            }
        }
        else if (action == "view") {
            for (string i : estoque) {
                cout << i << "  ";
            }
            cout << endl;
        }

        else{
            cout << "Selecione uma acao valida."<< endl;
        }
    }
}