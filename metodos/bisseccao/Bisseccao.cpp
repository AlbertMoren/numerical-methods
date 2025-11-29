#include "Bisseccao.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

ResultadoMetodo Bisseccao::calcular() {
    int iter = 0;
    double a = inicio;
    double b = fim;
    double c = a;

    double fa = funcao(a, a_param);
    double fb = funcao(b, a_param);

    if (fa * fb >= 0)
        return {0.0, 0, false};

    std::vector<LinhaBisseccao> tabela;   // 👉 armazena todas as linhas

    while (fabs(b - a) >= tolerancia && iter < maxIter) {

        c = (a + b) / 2.0;
        double fc = funcao(c, a_param);
        double intervalo = fabs(b - a);

        // 👉 guardar linha
        tabela.push_back({
            iter, a, fa, b, fb, c, fc, intervalo
        });

        if (fc == 0.0)
            break;

        if (fc * fa < 0)
            b = c;
        else
            a = c;

        fa = funcao(a, a_param);
        fb = funcao(b, a_param);

        iter++;
    }

    // 👉 Imprimir tabela (somente quando usuário escolher)
    imprimirTabela(tabela);

    return {(a + b) / 2.0, iter, true};
}


void Bisseccao::imprimirTabela(const std::vector<LinhaBisseccao>& tabela) const {
    using std::cout;
    using std::endl;
    using std::setw;

    cout << std::scientific << std::setprecision(6);

    cout << "Iteracao "
         << setw(12) << "a"
         << setw(12) << "fa"
         << setw(12) << "b"
         << setw(12) << "fb"
         << setw(12) << "x"
         << setw(12) << "fx"
         << setw(12) << "intervX" << endl;

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
