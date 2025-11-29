#ifndef SISTEMA_JATOS_HPP
#define SISTEMA_JATOS_HPP

#include <iostream>
#include <vector>
#include <climits>
#include <limits>
#include "../funcoes/Funcoes.hpp"
#include "ProcessadorMetodos.hpp"
#include "Relatorio.hpp"

using namespace std;

class SistemaJatos {

private:
    Relatorio relatorio;

public:

    SistemaJatos() {}

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
            cout << "Digite o numero de jatos a serem analisados: ";
            cin >> n;

            vector<RelatorioJato> lista;

            for (int i = 0; i < n; i++) {
                RelatorioJato j;
                j.id = i + 1;

                cout << "Digite o parametro 'a' para o Jato " << j.id << ": ";
                cin >> j.parametro_a;

                // Isolar raiz dinamicamente
                auto intervalo = IsolarRaizInt(j.parametro_a, -100, 100);

                if (intervalo.first == INT_MIN) {
                    cout << "Nao foi possivel isolar um intervalo para o jato " 
                         << j.id << ". Pulando...\n";
                    continue;
                }

                // Criar o processador com intervalo certo
                ProcessadorMetodos processador(intervalo.first, intervalo.second, 1e-5);

                // Executar métodos para este jato
                processador.executarMetodos(j, opcao);

                lista.push_back(j);
            }

            // Exibir relatorios
            if (opcao != 4) {
                relatorio.imprimirSimples(lista, opcao);
            } else {
                relatorio.quadroSeguranca(lista);
                relatorio.quadroComparativo(lista);
            }

            cout << "\nPressione ENTER para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } while (true);
    }

    void menu() {
        cout << "\n==================================================================\n";
        cout << "             SISTEMA DE ANALISE DE JATOS SUPERSONICOS             \n";
        cout << "==================================================================\n";
        cout << "1. Bisseccao\n";
        cout << "2. Posicao Falsa\n";
        cout << "3. Newton-Raphson\n";
        cout << "4. Todos os Metodos\n";
        cout << "0. Sair\n";
        cout << "Opcao: ";
    }
};

#endif
