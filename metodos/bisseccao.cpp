#include <cmath>
#include "funcoes.h"

ResultadoMetodo calcularBisseccao(double a_param, double inicio, double fim, double tol) {
    int iter = 0;
    double c = inicio;
    
    if (funcao(inicio, a_param) * funcao(fim, a_param) >= 0) {
        return {0.0, 0, false}; 
    }

    while (fabs(fim - inicio) >= tol && iter < 1000) {
        iter++;
        c = (inicio + fim) / 2.0;

        if (funcao(c, a_param) == 0.0) break;
        
        if (funcao(c, a_param) * funcao(inicio, a_param) < 0)
            fim = c;
        else
            inicio = c;
    }
    return {(inicio + fim) / 2.0, iter, true};
}