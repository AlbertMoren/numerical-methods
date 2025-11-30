#include "PosicaoFalsa.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "funcoes/Funcoes.hpp"

ResultadoMetodo PosicaoFalsa::calcular() {
    double a = inicio;
    double b = fim;
    double a_param = this->a_param;
    double tol = this->tolerancia;
    int maxIter = this->maxIter;

    double fa = funcao(a, a_param);
    double fb = funcao(b, a_param);

    if (fa * fb >= 0) {
        return {0.0, 0, false};
    }

    int iter = 0;
    double x = a;
    double fx = fa;

    std::vector<LinhaPosFalsa> tabela;   // armazena linhas da tabela

    while (fabs(fx) > tol && iter < maxIter) {

        x = (a * fb - b * fa) / (fb - fa);
        fx = funcao(x, a_param);

        if (std::isnan(fx)) {
            return {0.0, iter, false};
        }

        double intervalo = fabs(b - a);

        // armazenar linha na tabela
        tabela.push_back({
            iter,
            a, fa,
            b, fb,
            x, fx,
            intervalo
        });

        // Atualização dos limites
        if (fa * fx < 0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }

        iter++;
    }

    imprimirTabela(tabela);
    return {x, iter, true};
}


void PosicaoFalsa::imprimirTabela(const std::vector<LinhaPosFalsa>& tabela) const {
    using std::cout;
    using std::endl;
    using std::setw;
    using std::right;

    // Largura para os campos numéricos em notação científica (12 caracteres)
    const int numWidth = 12;
    // Largura para a iteração (6 caracteres)
    const int iterWidth = 6;
    // Precisão científica
    const int precision = 5;

    cout << std::scientific << std::setprecision(precision);

    // --- Título ---
    cout << "==========================================================================================================" << endl;
    cout << "===================================Método da Posição Falsa================================================" << endl;
    cout << "==========================================================================================================" << endl;
    
    // --- Cabeçalho ---
    cout << right 
         << setw(iterWidth) << "Iter."
         << setw(numWidth) << "a"
         << setw(numWidth) << "f(a)"
         << setw(numWidth) << "b"
         << setw(numWidth) << "f(b)"
         << setw(numWidth) << "x_k"
         << setw(numWidth) << "f(x_k)"
         << setw(numWidth) << "I_Tam"
         << endl;

    // --- Linhas de Dados ---
    for (const auto& linha : tabela) {
        cout << setw(iterWidth) << linha.iter 
             << setw(numWidth) << linha.a  
             << setw(numWidth) << linha.fa 
             << setw(numWidth) << linha.b  
             << setw(numWidth) << linha.fb 
             << setw(numWidth) << linha.x  
             << setw(numWidth) << linha.fx 
             << setw(numWidth) << linha.intervalo
             << endl;
    }
}