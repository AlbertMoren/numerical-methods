#ifndef FUNCOES_HPP
#define FUNCOES_HPP

#include <utility> 

using namespace std;

// Estrutura de retorno comum
struct ResultadoMetodo {
    double raiz;
    int iteracoes;
    bool convergiu;
};

// Funções matemáticas utilizadas pelos métodos numéricos
double funcao(double d, double a);
double derivada(double d, double h, double a);
pair<int,int> IsolarRaizInt(double a, int ini_range, int fim_range);

#endif
