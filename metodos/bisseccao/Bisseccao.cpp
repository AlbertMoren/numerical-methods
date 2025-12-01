#include "Bisseccao.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include "../menu/UtilsMenu.hpp"

ResultadoMetodo Bisseccao::calcular() {
    int iter = 0;
    double a = inicio;
    double b = fim;
    double c = a;

    double fa = funcao(a, a_param);
    double fb = funcao(b, a_param);

    if (fa * fb >= 0)
        return {0.0, 0, false};

    std::vector<LinhaBisseccao> tabela;   // armazena todas as linhas

    while (fabs(b - a) >= tolerancia && iter < maxIter) {

        c = (a + b) / 2.0;
        double fc = funcao(c, a_param);
        double intervalo = fabs(b - a);

        // guardar linha
        tabela.push_back({
            iter, a, fa, b, fb, c, fc, intervalo
        });

        if (fc == 0.0)
            break;

        if (fc * fa < 0)
            b = c;
        else
            a = c;

        if (fabs(a) < 1e-12) a = (a < 0 ? -1e-12 : 1e-12);
        if (fabs(b) < 1e-12) b = (b < 0 ? -1e-12 : 1e-12);

        fa = funcao(a, a_param);
        fb = funcao(b, a_param);

        iter++;
    }

    imprimirTabela(tabela);

    return {(a + b) / 2.0, iter, true};
}

void Bisseccao::imprimirTabela(const std::vector<LinhaBisseccao>& tabela) const {
    using std::cout;
    using std::endl;
    using std::setw;
    using std::left;
    using std::right;

    const int W = 15;  // largura fixa das colunas

    auto col = [&](const std::string& txt) {
        return centralizar(txt, W);
    };

    titulo("Metodo da Bisseccao");

    // Largura para os campos numéricos em notação científica (12 caracteres)
    const int numWidth = 12;
    // Largura para a iteração (6 caracteres)
    const int iterWidth = 6;
    // Precisão científica
    const int precision = 5;

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