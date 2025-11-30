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

    cout << std::scientific << std::setprecision(5);

    cout << "==============================================================" << endl;
    cout << "==================Método da Posição Falsa=====================" << endl;
    cout << "==============================================================" << endl;
    

    cout << "Iteracao "
         << setw(5) << "a"
         << setw(5) << "fa"
         << setw(5) << "b"
         << setw(5) << "fb"
         << setw(5) << "x"
         << setw(5) << "fx"
         << setw(5) << "intervX"
         << endl;

    for (const auto& linha : tabela) {
        cout << linha.iter << " "
             << linha.a  << " "
             << linha.fa << " "
             << linha.b  << " "
             << linha.fb << " "
             << linha.x  << " "
             << linha.fx << " "
             << linha.intervalo
             << endl;
    }
}
