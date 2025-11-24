#include <cmath>
#include "funcoes.h"

ResultadoMetodo calcularNewton(double a_param, double chute_inicial, double tol) {
    double d = chute_inicial;
    int iter = 0;
    
    while (iter < 100) {
        double f_d = funcao(d, a_param);
        double d_derivada = derivada(d, tol, a_param); 
        
        if (fabs(d_derivada) < 1e-12) break;

        double d_novo = d - (f_d / d_derivada);
        iter++;
        
        if (fabs(d - d_novo) < tol) {
            return {d_novo, iter, true};
        }
        d = d_novo;
    }
    return {d, iter, false};
}