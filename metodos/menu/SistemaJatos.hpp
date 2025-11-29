#ifndef SISTEMA_JATOS_HPP
#define SISTEMA_JATOS_HPP

#include <iostream>
#include <vector>
#include "ProcessadorMetodos.hpp"
#include "Relatorio.hpp"

using namespace std;

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
            cin >> opcao;

            if (opcao == 0) {
                cout << "Encerrando...\n";
                break;
            }

            if (opcao < 0 || opcao > 4) {
                cout << "Opcao invalida!\n";
                continue;
            }

            int n;
            cout << "Digite o numero de jatos a serem analisados nesta rodada: ";
            cin >> n;

            vector<RelatorioJato> lista;

            for (int i = 0; i < n; i++) {
                RelatorioJato j;
                j.id = i + 1;

                cout << "Digite o parametro 'a' para o Jato " << j.id << ": ";
                cin >> j.parametro_a;

                processador.executarMetodos(j, opcao);
                lista.push_back(j);
            }

            if (opcao != 4) {
                relatorio.imprimirSimples(lista, opcao);
            } else {
                relatorio.quadroSeguranca(lista);
                relatorio.quadroComparativo(lista);
            }

            cout << "\nEnter para continuar...";
            cin.ignore();
            cin.get();

        } while (true);
    }

    void menu() {
        cout << endl;
        cout << "==================================================================" << endl;
        cout << "             SISTEMA DE ANÁLISE DE JATOS SUPERSÔNICOS             " << endl;
        cout << "==================================================================" << endl;
        cout << "1. Bisseccao\n";
        cout << "2. Posicao Falsa\n";
        cout << "3. Newton-Raphson\n";
        cout << "4. Todos os Metodos\n";
        cout << "0. Sair\n";
        cout << "Opcao: ";
    }
};

#endif
