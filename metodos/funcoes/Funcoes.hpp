#ifndef FUNCOES_HPP
#define FUNCOES_HPP

// Estrutura de retorno comum
struct ResultadoMetodo {
    double raiz;
    int iteracoes;
    bool convergiu;
};

// Funções matemáticas utilizadas pelos métodos numéricos
double funcao(double d, double a);
double derivada(double d, double h, double a);

#endif
