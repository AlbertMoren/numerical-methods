#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "RelatorioJato.hpp"

class Relatorio {
public:

    void cabecalhoSimples() {
        std::cout << "| Jato | Parametro 'a' | Raiz Encontrada (d) | Iteracoes | Status |" << std::endl;
        std::cout << "|------|---------------|---------------------|-----------|--------|" << std::endl;
    }

    void linhaSimples(int id, double a, ResultadoMetodo r) {
        std::string status = (r.raiz > 2.0) ? "PERIGO!" : "Seguro";
        std::cout << "| " << std::setw(4) << id << " | "
                  << std::setw(13) << a << " | "
                  << std::setw(19) << std::fixed << std::setprecision(6) << r.raiz << " | "
                  << std::setw(9) << r.iteracoes << " | "
                  << std::setw(6) << status << " |" << std::endl;
    }

    void imprimirSimples(const std::vector<RelatorioJato>& lista, int opcao) {
        cabecalhoSimples();

        for (auto& r : lista) {
            if (opcao == 1) linhaSimples(r.id, r.parametro_a, r.res_bisseccao);
            if (opcao == 2) linhaSimples(r.id, r.parametro_a, r.res_pos_falsa);
            if (opcao == 3) linhaSimples(r.id, r.parametro_a, r.res_newton);
        }
    }

    void quadroSeguranca(const std::vector<RelatorioJato>& lista) {
        std::cout << "QUADRO RESPOSTA (Ref: Newton)" << std::endl;
        std::cout << "| Jato | Parametro | Deslocamento | Status |" << std::endl;

        for (auto& r : lista) {
            std::string status = r.res_newton.raiz > 2.0 ? "EXPLODE" : "SEGURO";
            std::cout << "| " << r.id << " | "
                      << r.parametro_a << " | "
                      << std::setprecision(5) << r.res_newton.raiz << " | "
                      << status << " |" << std::endl;
        }
    }

    void quadroComparativo(const std::vector<RelatorioJato>& rel) {
        std::cout << "\nQUADRO COMPARATIVO" << std::endl;
        std::cout << "| Jato | Metodo | Raiz | Iteracoes |" << std::endl;

        for (auto& r : rel) {
            std::cout << "| " << r.id << " | Bisseccao      | " << r.res_bisseccao.raiz << " | " << r.res_bisseccao.iteracoes << " |\n";
            std::cout << "| " << r.id << " | Posicao Falsa  | " << r.res_pos_falsa.raiz << " | " << r.res_pos_falsa.iteracoes << " |\n";
            std::cout << "| " << r.id << " | Newton-Raphson | " << r.res_newton.raiz << " | " << r.res_newton.iteracoes << " |\n";
        }
    }
};

#endif
