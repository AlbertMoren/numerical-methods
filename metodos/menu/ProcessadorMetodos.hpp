#ifndef PROCESSADOR_METODOS_HPP
#define PROCESSADOR_METODOS_HPP

#include "RelatorioJato.hpp"
#include "bisseccao/Bisseccao.hpp"
#include "posicaoFalsa/PosicaoFalsa.hpp"
#include "newton/NewtonRaphson.hpp"

class ProcessadorMetodos {
private:
    double intervalo_ini;
    double intervalo_fim;
    double precisao;

public:
    ProcessadorMetodos(double ini, double fim, double p)
        : intervalo_ini(ini), intervalo_fim(fim), precisao(p) {}

    void executarMetodos(RelatorioJato& jato, int opcao) {

        ResultadoMetodo vazio = {0, 0, false};
        jato.res_bisseccao = vazio;
        jato.res_pos_falsa = vazio;
        jato.res_newton = vazio;

        if (opcao == 1 || opcao == 4) {
            Bisseccao b(jato.parametro_a, intervalo_ini, intervalo_fim, precisao);
            jato.res_bisseccao = b.calcular();
        }
        if (opcao == 2 || opcao == 4) {
            PosicaoFalsa pf(jato.parametro_a, intervalo_ini, intervalo_fim, precisao);
            jato.res_pos_falsa = pf.calcular();
        }
        if (opcao == 3 || opcao == 4) {
            double chute = (intervalo_ini + intervalo_fim) / 2.0;
            NewtonRaphson n(jato.parametro_a, chute, precisao);
            jato.res_newton = n.calcular();
        }
    }
};

#endif
