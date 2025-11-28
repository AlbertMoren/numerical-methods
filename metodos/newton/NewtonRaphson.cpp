#include "NewtonRaphson.hpp"
#include <cmath>

NewtonRaphson::NewtonRaphson(double a_param, double chute_inicial, double tolerancia, int maxIter)
    : MetodoNumerico(a_param, chute_inicial, 0.0, tolerancia, maxIter){}

ResultadoMetodo NewtonRaphson::calcular() {
    double d = inicio;  
    int iter = 0;

    while (iter < maxIter) {
        double f_d = funcao(d, a_param);
        double d_derivada = derivada(d, tolerancia, a_param);

        // Evita divisão por zero
        if (fabs(d_derivada) < 1e-12) {
            return {d, iter, false};
        }

        double d_novo = d - (f_d / d_derivada);
        iter++;

        // Critério de parada
        if (fabs(d - d_novo) < tolerancia) {
            return {d_novo, iter, true};
        }

        d = d_novo;
    }

    return {d, iter, false};
}
