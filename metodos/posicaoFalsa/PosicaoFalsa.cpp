#include "PosicaoFalsa.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "funcoes/Funcoes.hpp"
#include "../menu/UtilsMenu.hpp"


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

    const int W = 15;  // largura fixa das colunas

    auto col = [&](const std::string& txt) {
        return centralizar(txt, W);
    };

    cout << std::scientific << std::setprecision(5);

    titulo("Metodo da Posicao Falsa");

    linhaSep();

    // Cabeçalho centralizado
    cout << "|"
         << col("Iteracao")  << "|"
         << col("a")         << "|"
         << col("fa")        << "|"
         << col("b")         << "|"
         << col("fb")        << "|"
         << col("x")         << "|"
         << col("fx")        << "|"
         << col("intervalo") << "|\n";

    linhaSep();

    for (const auto& linha : tabela) {
        cout << "|"
             << setw(W) << left << linha.iter
             << "|" << setw(W) << left << linha.a
             << "|" << setw(W) << left << linha.fa
             << "|" << setw(W) << left << linha.b
             << "|" << setw(W) << left << linha.fb
             << "|" << setw(W) << left << linha.x
             << "|" << setw(W) << left << linha.fx
             << "|" << setw(W) << left << linha.intervalo
             << "|\n";
    }

    linhaSep();
}
