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

            try {
                if (cin.fail()) {
                    throw std::invalid_argument("Entrada invalida para o parametro 'a'.");
                }
            } catch (const std::invalid_argument& e) {
                cout << "Entrada invalida! Digite um numero de 0 a 4.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;   // volta ao menu sem encerrar
            }

            switch (opcao) {

                case 0:
                    cout << "Encerrando...\n";
                    return;

                case 1:
                case 2:
                case 3:
                case 4:
                    // Opção válida – segue o fluxo normal
                    break;

                default:
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

                try {
                    if (cin.fail()) {
                        throw std::invalid_argument("Entrada invalida para o parametro 'a'.");
                    }
                } catch (const std::invalid_argument& e) {
                    cout << e.what() << " Preencha com um número valido, ex.: 1.0 .\n";
                    cin.clear(); // Limpa o estado de falha
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta a entrada inválida
                    i--;
                    continue;
                }

                // Isolar raiz
                auto intervalo = IsolarRaizInt(j.parametro_a, -100, 100);

                if (intervalo.first == INT_MIN) {
                    cout << "Nao foi possivel isolar um intervalo para o jato "
                        << j.id << ". Pulando...\n";
                    continue;
                }

                ProcessadorMetodos processador(intervalo.first, intervalo.second, 1e-5);

                processador.executarMetodos(j, opcao);

                lista.push_back(j);
            }

            // Relatórios
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

        titulo("SISTEMA DE ANALISE DE JATOS SUPERSONICOS");
        cout << "1. Bisseccao\n";
        cout << "2. Posicao Falsa\n";
        cout << "3. Newton-Raphson\n";
        cout << "4. Todos os Metodos\n";
        cout << "0. Sair\n";
        cout << "Opcao: ";
    }
};

#endif
