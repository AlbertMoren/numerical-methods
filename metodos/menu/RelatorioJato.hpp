#ifndef RELATORIO_JATO_HPP
#define RELATORIO_JATO_HPP

#include "funcoes/Funcoes.hpp"

struct RelatorioJato {
    int id;
    double parametro_a;

    ResultadoMetodo res_bisseccao;
    ResultadoMetodo res_pos_falsa;
    ResultadoMetodo res_newton;
};

#endif