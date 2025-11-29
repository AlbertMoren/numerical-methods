#ifndef SISTEMA_JATOS_HPP
#define SISTEMA_JATOS_HPP

#include <iostream>
#include <vector>
#include "ProcessadorMetodos.hpp"
#include "Relatorio.hpp"

class SistemaJatos {
private:
    ProcessadorMetodos processador;
    Relatorio relatorio;

public:
    SistemaJatos() : processador(2.0, 3.0, 1e-5) {}

    void executar() {
        int opcao;

        do {
            menu();
            std::cin >> opcao;

            if (opcao == 0) {
                std::cout << "Encerrando...\n";
                break;
            }

            if (opcao < 0 || opcao > 4) {
                std::cout << "Opcao invalida!\n";
                continue;
            }

            int n;
            std::cout << "Digite o numero de jatos a serem analisados nesta rodada: ";
            std::cin >> n;

            std::vector<RelatorioJato> lista;

            for (int i = 0; i < n; i++) {
                RelatorioJato j;
                j.id = i + 1;

                std::cout << "Digite o parametro 'a' para o Jato " << j.id << ": ";
                std::cin >> j.parametro_a;

                processador.executarMetodos(j, opcao);
                lista.push_back(j);
            }

            if (opcao != 4) {
                relatorio.imprimirSimples(lista, opcao);
            } else {
                relatorio.quadroSeguranca(lista);
                relatorio.quadroComparativo(lista);
            }

            std::cout << "\nEnter para continuar...";
            std::cin.ignore();
            std::cin.get();

        } while (true);
    }

    void menu() {
        std::cout << "\n======= SISTEMA DE JATOS =======\n";
        std::cout << "1. Bisseccao\n";
        std::cout << "2. Posicao Falsa\n";
        std::cout << "3. Newton-Raphson\n";
        std::cout << "4. Todos os Metodos\n";
        std::cout << "0. Sair\n";
        std::cout << "Opcao: ";
    }
};

#endif
