#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "RelatorioJato.hpp"
using namespace std;
class Relatorio {
public:

    void cabecalhoSimples() {
        cout << "| Jato | Parametro 'a' | Raiz Encontrada (d) | Iteracoes | Status |" << endl;
        cout << "|------|---------------|---------------------|-----------|--------|" << endl;
    }

    void linhaSimples(int id, double a, ResultadoMetodo r) {
        string status = (r.raiz > 2.0) ? "PERIGO!" : "Seguro";
        cout << "| " << setw(4) << id << " | "
                  << setw(13) << a << " | "
                  << setw(19) << fixed << setprecision(6) << r.raiz << " | "
                  << setw(9) << r.iteracoes << " | "
                  << setw(6) << status << " |" << endl;
    }

    void imprimirSimples(const vector<RelatorioJato>& lista, int opcao) {
        cabecalhoSimples();

        for (auto& r : lista) {
            if (opcao == 1) linhaSimples(r.id, r.parametro_a, r.res_bisseccao);
            if (opcao == 2) linhaSimples(r.id, r.parametro_a, r.res_pos_falsa);
            if (opcao == 3) linhaSimples(r.id, r.parametro_a, r.res_newton);
        }
    }

    void quadroSeguranca(const vector<RelatorioJato>& lista) {
        cout << "QUADRO RESPOSTA (Ref: Newton)" << endl;
        cout << "| Jato | Parametro | Deslocamento | Status |" << endl;

        for (auto& r : lista) {
            string status = r.res_newton.raiz > 2.0 ? "EXPLODE" : "SEGURO";
            cout << "| " << r.id << " | "
                      << r.parametro_a << " | "
                      << setprecision(5) << r.res_newton.raiz << " | "
                      << status << " |" << endl;
        }
    }

    void quadroComparativo(const vector<RelatorioJato>& rel) {
        cout << "\nQUADRO COMPARATIVO" << endl;
        cout << "| Jato | Metodo | Raiz | Iteracoes |" << endl;

        for (auto& r : rel) {
            cout << "| " << r.id << " | Bisseccao      | " << r.res_bisseccao.raiz << " | " << r.res_bisseccao.iteracoes << " |\n";
            cout << "| " << r.id << " | Posicao Falsa  | " << r.res_pos_falsa.raiz << " | " << r.res_pos_falsa.iteracoes << " |\n";
            cout << "| " << r.id << " | Newton-Raphson | " << r.res_newton.raiz << " | " << r.res_newton.iteracoes << " |\n";
        }
    }
};

#endif
