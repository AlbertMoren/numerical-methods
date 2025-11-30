#include "UtilsMenu.hpp"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

const int W = 15;  // largura fixa das colunas

void titulo(std::string texto) {
    using std::cout;
    using std::endl;

    cout << "\n=================================================================================================================================\n";
    cout << "                                                     " << texto << "                                                         \n";
    cout << "=================================================================================================================================\n";
}


std::string centralizar(const std::string& texto, int largura) {
    int espacos = largura - texto.size();
    if (espacos <= 0) return texto;

    int esquerda = espacos / 2;
    int direita  = espacos - esquerda;

    return std::string(esquerda, ' ') + texto + std::string(direita, ' ');
}

void linhaSep() {
        cout << "-";
        for (int i = 0; i < 8; i++) cout << std::string(W, '-') << "-";
        cout << endl;
    };