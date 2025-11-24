#include <cmath>
#include "funcoes.h"

ResultadoMetodo calcularPosicaoFalsa(double a_param, double inicio, double fim, double tol) {
    int iter = 0;
    double xm = inicio;
    double fa = funcao(inicio, a_param);
    double fb = funcao(fim, a_param);

    if (fa * fb >= 0) return {0.0, 0, false};

    double fxm = fa;
    
    while (fabs(fxm) > tol && iter < 1000) {
        xm = (inicio * fb - fim * fa) / (fb - fa);
        fxm = funcao(xm, a_param);
        
        if (std::isnan(fxm)) return {0.0, iter, false};

        if (fa * fxm < 0) {
            fim = xm;
            fb = fxm;
        } else {
            inicio = xm;
            fa = fxm;
        }
        iter++;
    }
    return {xm, iter, true};
}