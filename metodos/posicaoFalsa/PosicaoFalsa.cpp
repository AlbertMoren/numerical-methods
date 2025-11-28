#include "PosicaoFalsa.hpp"
#include <cmath>
#include "funcoes/Funcoes.hpp"

ResultadoMetodo PosicaoFalsa::calcular() {
    double inicio = this->inicio;
    double fim = this->fim;
    double a_param = this->a_param;
    double tol = this->tolerancia;
    int maxIter = this->maxIter;

    int iter = 0;

    double fa = funcao(inicio, a_param);
    double fb = funcao(fim, a_param);

    if (fa * fb >= 0) {
        return {0.0, 0, false};
    }

    double xm = inicio;
    double fxm = fa;

    while (fabs(fxm) > tol && iter < maxIter) {

        xm = (inicio * fb - fim * fa) / (fb - fa);
        fxm = funcao(xm, a_param);

        if (std::isnan(fxm)) {
            return {0.0, iter, false};
        }

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
