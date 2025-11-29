#ifndef BISSECCAO_HPP
#define BISSECCAO_HPP

#include "metodo/MetodoNumerico.hpp"
#include <vector>

struct LinhaBisseccao {
    int iter;
    double a, fa;
    double b, fb;
    double x, fx;
    double intervalo;
};

class Bisseccao : public MetodoNumerico {
public:
    using MetodoNumerico::MetodoNumerico;

    ResultadoMetodo calcular() override;

    // 👉 Novo método para imprimir tabela
    void imprimirTabela(const std::vector<LinhaBisseccao>& tabela) const;
};

#endif
