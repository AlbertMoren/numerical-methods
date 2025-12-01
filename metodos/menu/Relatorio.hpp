#ifndef RELATORIO_HPP
#define RELATORIO_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include "RelatorioJato.hpp"
#include "../menu/UtilsMenu.hpp"

using namespace std;

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

class Relatorio {
public:

    void cabecalhoSimples() {
        titulo("RESULTADOS");

        auto col = [&](const std::string& txt) {
            return centralizar(txt, 15);
        };

        // Cabeçalho centralizado
        cout << "|"
            << col("Jato")  << "|"
            << col("Parametro 'a'")         << "|"
            << col(" Raiz Encontrada (d) ")        << "|"
            << col("Iteracoes")         << "|"
            << col("Status") << "|\n";
        linhaSep();
    }


    void linhaSimples(int id, double a, ResultadoMetodo r) {
        string status = (r.raiz > 2.0) ? "PERIGO!" : "Seguro";
        cout << "| " << setw(13) << id << " | "
                  << setw(13) << a << " | "
                  << setw(19) << fixed << setprecision(5) << r.raiz << " | "
                  << setw(13) << r.iteracoes << " | "
                  << setw(13) << status << " |" << endl;
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
        titulo("QUADRO RESPOSTA (Ref: Newton)");

        auto col = [&](const std::string& txt) {
            return centralizar(txt, 15);
        };

        // Cabeçalho centralizado
        cout << "|"
            << col("Jato")  << "|"
            << col("Parametro 'a'")         << "|"
            << col(" Deslocamento ")        << "|"
            << col("Status") << "|\n";
        linhaSep();

        for (auto& r : lista) {
            string status = (r.res_newton.raiz > 2.0) ? "PERIGO!" : "Seguro";
            cout << "| " << setw(13) << r.id << " | "
                    << setw(13) << r.parametro_a << " | "
                    << setw(13) << fixed << setprecision(6) << r.res_newton.raiz << " | "
                    << setw(13) << status << " |" << endl;
        }
    }

    void quadroComparativo(const vector<RelatorioJato>& rel) {
        titulo("QUADRO COMPARATIVO");

         auto col = [&](const std::string& txt) {
            return centralizar(txt, 15);
        };

        // Cabeçalho centralizado
        cout << "|"
            << col("Jato")  << "|"
            << col("Método")  <<   "  |"
            << col(" Deslocamento")         << "|"
            << col(" Iterações") << " |\n";
        linhaSep();

        for (auto& r : rel) {
            cout << "| " << setw(13) << r.id << " | Bisseccao      | " 
            << setw(13) << fixed << setprecision(6) << r.res_bisseccao.raiz << " | " 
            << setw(12) << r.res_bisseccao.iteracoes << " |\n";
            cout << "| " << setw(13) << r.id << " | Posicao Falsa  | " 
            << setw(13) << fixed << setprecision(6) << r.res_pos_falsa.raiz << " | " 
            << setw(12) << r.res_pos_falsa.iteracoes << " |\n";
            cout << "| " << setw(13)<< r.id << " | Newton-Raphson | " 
            << setw(13) << fixed << setprecision(6) << r.res_newton.raiz << " | " 
            << setw(12) << r.res_newton.iteracoes << " |\n";
        }
    }
};

#endif
