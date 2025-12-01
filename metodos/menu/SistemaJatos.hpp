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
                    throw std::invalid_argument("Entrada invalida para o menu.");
                }
            } catch (const std::invalid_argument& e) {
                cout << "Entrada invalida! Digite um numero de 0 a 4.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            switch (opcao) {
                case 0:
                    cout << "Encerrando...\n";
                    return;

                case 1:
                case 2:
                case 3:
                case 4:
                    break;

                default:
                    cout << "Opcao invalida!\n";
                    continue;
            }

            int n;
            string entrada;

            while (true) {
                cout << "Digite o numero de jatos a serem analisados: ";
                cin >> entrada;

                try {
                    for (char c : entrada) {
                        if (!isdigit(c))
                            throw invalid_argument("Entrada inválida");
                    }

                    n = stoi(entrada);

                    if (n <= 0) {
                        cout << "O número deve ser um inteiro positivo!\n";
                        continue;
                    }

                    break;

                } catch (...) {
                    cout << "Entrada inválida! Digite um inteiro positivo.\n";
                }
            }


            vector<RelatorioJato> lista;

            for (int i = 0; i < n; i++) {
                RelatorioJato j;
                j.id = i + 1;

                while (true) {
                    cout << "Digite o parametro 'a' para o Jato " << j.id << ": ";
                    cin >> j.parametro_a;

                    if (!cin.fail())
                        break;

                    cout << "Entrada invalida! Preencha com um número valido, ex.: 1.0.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

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
