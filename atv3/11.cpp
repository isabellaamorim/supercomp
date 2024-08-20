#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ifstream inputFile("texto.txt");
    ofstream outputFile("estatisticas.txt");

    if (!inputFile.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    string line, word;
    int totalLines = 0, totalWords = 0;
    map<string, int> wordCount;

    while (getline(inputFile, line)) {
        totalLines++;
        stringstream ss(line);
        while (ss >> word) {
            totalWords++; 
            wordCount[word]++;
        }
    }

    inputFile.close();

    string mostFrequentWord;
    int maxCount = 0;
    for (const auto& pair : wordCount) {
        if (pair.second > maxCount) {
            mostFrequentWord = pair.first;
            maxCount = pair.second;
        }
    }

    double averageWordsPerLine = (totalLines > 0) ? static_cast<double>(totalWords) / totalLines : 0;

    outputFile << "Número total de palavras: " << totalWords << endl;
    outputFile << "Número total de linhas: " << totalLines << endl;
    outputFile << "Número médio de palavras por linha: " << averageWordsPerLine << endl;
    outputFile << "Palavra mais frequente: " << mostFrequentWord << " (" << maxCount << " ocorrências)" << endl;

    outputFile.close();
    return 0;
}
