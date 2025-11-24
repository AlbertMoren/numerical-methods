#ifndef FUNCOES_H
#define FUNCOES_H

// Estrutura compartilhada por todos os arquivos
struct ResultadoMetodo {
    double raiz;
    int iteracoes;
    bool convergiu;
};

// Declaração das funções matematicas (física do jato)
double funcao(double d, double a);
double derivada(double d, double h, double a);

// Declaração dos Algoritmos Numéricos
ResultadoMetodo calcularBisseccao(double a_param, double inicio, double fim, double tol);
ResultadoMetodo calcularPosicaoFalsa(double a_param, double inicio, double fim, double tol);
ResultadoMetodo calcularNewton(double a_param, double chute_inicial, double tol);

#endif