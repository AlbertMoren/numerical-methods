// #ifndef POSICAOFALSA_HPP
// #define POSICAOFALSA_HPP

// #include "metodo/MetodoNumerico.hpp"

// class PosicaoFalsa : public MetodoNumerico {
// public:
//     // Herdar construtor da classe base
//     using MetodoNumerico::MetodoNumerico;

//     ResultadoMetodo calcular() override;
// };

// #endif

#ifndef POSICAOFALSA_HPP
#define POSICAOFALSA_HPP

#include "metodo/MetodoNumerico.hpp"
#include <vector>

struct LinhaPosFalsa {
    int iter;
    double a, fa;
    double b, fb;
    double x, fx;
    double intervalo;
};

class PosicaoFalsa : public MetodoNumerico {
public:
    using MetodoNumerico::MetodoNumerico;

    ResultadoMetodo calcular() override;

    // 👉 Novo método de impressão da tabela
    void imprimirTabela(const std::vector<LinhaPosFalsa>& tabela) const;
};

#endif

