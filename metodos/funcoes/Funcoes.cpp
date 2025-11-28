#include <cmath>
#include "Funcoes.hpp"

// f(d) = a*d - d*ln(d)
double funcao(double d, double a) {
    if (d <= 0) return 1e9; // Proteção contra log de número negativo
    return (a * d) - (d * log(d));
}

// Derivada Numerica
double derivada(double d, double h, double a) {
    double f_mais = funcao(d + h, a);
    double f_menos = funcao(d - h, a);
    return (f_mais - f_menos) / (2 * h);
}