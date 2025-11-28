#ifndef POSICAOFALSA_HPP
#define POSICAOFALSA_HPP

#include "metodo/MetodoNumerico.hpp"

class PosicaoFalsa : public MetodoNumerico {
public:
    // Herdar construtor da classe base
    using MetodoNumerico::MetodoNumerico;

    ResultadoMetodo calcular() override;
};

#endif
