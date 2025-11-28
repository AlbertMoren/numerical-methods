#ifndef BISSECCAO_HPP
#define BISSECCAO_HPP

#include "metodo/MetodoNumerico.hpp"

class Bisseccao : public MetodoNumerico {
public:
    using MetodoNumerico::MetodoNumerico; 

    ResultadoMetodo calcular() override;
};


#endif 

