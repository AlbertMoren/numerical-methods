#include "Bisseccao.hpp"
#include <cmath>

ResultadoMetodo Bisseccao::calcular() {
    int iter = 0;
    double a = inicio;
    double b = fim;
    double c = a;

    if (funcao(a, a_param) * funcao(b, a_param) >= 0)
        return {0.0, 0, false};

    while (fabs(b - a) >= tolerancia && iter < maxIter) {
        iter++;
        c = (a + b) / 2.0;

        double fc = funcao(c, a_param);

        if (fc == 0.0)
            break;

        if (fc * funcao(a, a_param) < 0)
            b = c;
        else
            a = c;
    }

    return {(a + b) / 2.0, iter, true};
}