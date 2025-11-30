#ifndef NEWTONRAPHSON_HPP
#define NEWTONRAPHSON_HPP

#include "metodo/MetodoNumerico.hpp"
#include <vector>

struct LinhaNewton {
    int iter;
    double x;
    double fx;
    double dfx;
    double xnovo;
    double erro;
};

class NewtonRaphson : public MetodoNumerico {
public:
    NewtonRaphson(double a_param, double chute_inicial, double tolerancia, int maxIter = 100);

    ResultadoMetodo calcular() override;

    // Novo método para imprimir tabela
    void imprimirTabela(const std::vector<LinhaNewton>& tabela) const;
};

#endif
