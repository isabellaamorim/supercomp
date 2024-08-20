#include <iostream>
#include <string>

using namespace std;

int main() {
    string word;
    cout << "Palavra: " << endl;
    cin >> word;

    string temp = "";
    for (int i = word.size() - 1; i >= 0; i--) {
        temp = temp + word[i];
    }

    if (word == temp) {
        cout << "Eh palindromo" << endl;
    } else {
        cout << "Nao eh palindromo" << endl;
    }
}
