#ifndef NEWTONRAPHSON_HPP
#define NEWTONRAPHSON_HPP

#include "metodo/MetodoNumerico.hpp"

class NewtonRaphson : public MetodoNumerico {
public:
    NewtonRaphson(double a_param, double chute_inicial, double tolerancia, int maxIter = 100);

    ResultadoMetodo calcular() override;
};


#endif 