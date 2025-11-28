#ifndef METODONUMERICO_HPP
#define METODONUMERICO_HPP

#include "funcoes/Funcoes.hpp"

class MetodoNumerico {
protected:
    double a_param;
    double inicio;
    double fim;
    double tolerancia;
    int maxIter;

public:
    MetodoNumerico(double a_param, double inicio, double fim, double tolerancia, int maxIter = 1000)
        : a_param(a_param), inicio(inicio), fim(fim), tolerancia(tolerancia), maxIter(maxIter) {}

    virtual ResultadoMetodo calcular() = 0;

    virtual ~MetodoNumerico() {}
};

#endif
