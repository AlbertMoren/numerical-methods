#include <cmath>
#include <iostream>
#include <utility>
#include <climits>
#include "Funcoes.hpp"

using namespace std;


// f(d) = a*d - d*ln(d)
double funcao(double d, double a) {

    // --- Proteção: valores <= 0 não fazem sentido matemático ---
    if (d <= 0) {
        // retorna um valor MUITO GRANDE, mas proporcional e não enganoso
        return 1e6 + fabs(d);  
    }

    double ad = a * d;
    double dlog = d * log(d);

    // --- Proteções contra overflow e NaN ---
    if (!isfinite(ad) || !isfinite(dlog)) {
        return 1e6;
    }

    return ad - dlog;
}

// Derivada Numerica
double derivada(double d, double h, double a) {

    double f_mais  = funcao(d + h, a);
    double f_menos = funcao(d - h, a);

    // proteção contra valores absurdos
    if (!isfinite(f_mais) || !isfinite(f_menos))
        return 1e6;

    return (f_mais - f_menos) / (2 * h);
}

// isola raiz em intervalos inteiros [x, x+1]
pair<int,int> IsolarRaizInt(double a, int ini_range, int fim_range)
{
    for (int x = ini_range; x < fim_range; x++) {

        double f1 = funcao(x, a);
        double f2 = funcao(x + 1, a);

        if (f1 * f2 < 0) {
            return {x, x+1};
        }
    }

    cout << "Nenhum intervalo inteiro com mudança de sinal encontrado.\n";
    return {INT_MIN, INT_MIN};
}