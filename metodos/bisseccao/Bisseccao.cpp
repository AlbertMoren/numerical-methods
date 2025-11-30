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

        fa = funcao(a, a_param);
        fb = funcao(b, a_param);

        iter++;
    }

    // Imprimir tabela (somente quando usuário escolher)
    imprimirTabela(tabela);

    return {(a + b) / 2.0, iter, true};
}


void Bisseccao::imprimirTabela(const std::vector<LinhaBisseccao>& tabela) const {
    using std::cout;
    using std::endl;
    using std::setw;

    cout << std::scientific << std::setprecision(5);

    cout << "==============================================================" << endl;
    cout << "======================Método da Bissecção=====================" << endl;
    cout << "==============================================================" << endl;

    cout << "Iteracao "
         << setw(5) << "a"
         << setw(5) << "fa"
         << setw(5) << "b"
         << setw(5) << "fb"
         << setw(5) << "x"
         << setw(5) << "fx"
         << setw(5) << "intervX" << endl;

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
