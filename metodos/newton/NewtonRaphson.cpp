#include "NewtonRaphson.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <vector>

NewtonRaphson::NewtonRaphson(double a_param, double chute_inicial, double tolerancia, int maxIter)
    : MetodoNumerico(a_param, chute_inicial, 0.0, tolerancia, maxIter) {}

ResultadoMetodo NewtonRaphson::calcular() {
    double d = inicio;
    int iter = 0;

    std::vector<LinhaNewton> tabela;   // armazena as linhas da tabela

    while (iter < maxIter) {
        double f_d = funcao(d, a_param);
        double d_derivada = derivada(d, tolerancia, a_param);

        // Evita divisão por zero
        if (fabs(d_derivada) < 1e-12) {
            return {d, iter, false};
        }

        double d_novo = d - (f_d / d_derivada);
        double erro = fabs(d_novo - d);

        //Salvar linha da tabela
        tabela.push_back({
            iter,      // iteração
            d,         // x atual
            f_d,       // f(x)
            d_derivada,// f'(x)
            d_novo,    // próximo x
            erro       // erro |x_new - x_old|
        });

        iter++;

        // Critério de parada
        if (erro < tolerancia) {
            imprimirTabela(tabela);
            return {d_novo, iter, true};
        }

        d = d_novo;
    }

    imprimirTabela(tabela);
    return {d, iter, false};
}


void NewtonRaphson::imprimirTabela(const std::vector<LinhaNewton>& tabela) const {
    using std::cout;
    using std::setw;
    using std::endl;

    cout << std::scientific << std::setprecision(5);

    cout << "==============================================================" << endl;
    cout << "==================Método de Newton-Raphson====================" << endl;
    cout << "==============================================================" << endl;

    cout << "Iteracao "
         << setw(5) << "x"
         << setw(5) << "f(x)"
         << setw(5) << "f'(x)"
         << setw(5) << "x_novo"
         << setw(5) << "erro"
         << endl;

    for (const auto& linha : tabela) {
        cout << linha.iter << " "
             << linha.x      << " "
             << linha.fx     << " "
             << linha.dfx    << " "
             << linha.xnovo  << " "
             << linha.erro
             << endl;
    }
}
