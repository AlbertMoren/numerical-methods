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

    // Protecao: se o intervalo encostar em zero, tentar empurrar um epsilon acima.
    // Mas manter a troca de sinal; se perder bracketing, volta para 0 (sentinela).
    if (a <= 0.0) {
        const double epsilon = 1e-6;
        double fa_eps = funcao(epsilon, a_param);
        if (fa_eps * fb < 0) {
            a = epsilon;
            fa = fa_eps;
        } else {
            a = 0.0;
            fa = funcao(a, a_param);
        }
    }

    if (fa * fb >= 0) {
        return {0.0, 0, false};
    }

    std::vector<LinhaPosFalsa> tabela;   // armazena linhas da tabela
    int iter = 0;
    double x = a;
    double fx = 0.0;

    for (iter = 0; iter < maxIter; ++iter) {
        x = (a * fb - b * fa) / (fb - fa);
        fx = funcao(x, a_param);

        if (std::isnan(fx)) {
            return {0.0, iter, false};
        }

        double intervalo = fabs(b - a);

        tabela.push_back({
            iter,
            a, fa,
            b, fb,
            x, fx,
            intervalo
        });

        if (fabs(fx) <= tol) {
            imprimirTabela(tabela);
            return {x, iter + 1, true};
        }

        // Atualização dos limites
        if (fa * fx < 0) {
            b = x;
            fb = fx;
        } else {
            a = x;
            fa = fx;
        }
    }

    imprimirTabela(tabela);
    return {x, iter, false};
}


void PosicaoFalsa::imprimirTabela(const std::vector<LinhaPosFalsa>& tabela) const {
    using std::cout;
    using std::endl;
    using std::setw;
    using std::right;

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
         << col("b - a") << "|\n";

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