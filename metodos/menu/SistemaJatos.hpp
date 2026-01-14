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

    void menuTrabalho1() {
        titulo("TRABALHO 1: ANALISE DE JATOS (RAIZES)");
        cout << "1. Bisseccao\n";
        cout << "2. Posicao Falsa\n";
        cout << "3. Newton-Raphson\n";
        cout << "4. Todos os Metodos\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Opcao: ";
    }

    void executarTrabalho1() {
        int opcao;

        do {
            menuTrabalho1();
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

            cout << "\nPressione ENTER para continuar no Trabalho 1...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } while (true);
    }

    void menuTrabalho2() {
        titulo("TRABALHO 2: SISTEMAS LINEARES (FATORACAO)");
        cout << "1. Metodo Fatoracao LU\n";
        cout << "2. Metodo Fatoracao LDP\n";
        cout << "3. Analise Completa (Comparativo LU vs LDP)\n";
        cout << "0. Voltar ao Menu Principal\n";
        cout << "Opcao: ";
    }

    void executarTrabalho2() {
        int opcao;
        
        do {
            menuTrabalho2();
            cin >> opcao;

            if (cin.fail()) {
                cout << "Entrada invalida.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (opcao == 0) return;
            if (opcao < 1 || opcao > 3) {
                cout << "Opcao invalida!\n";
                continue;
            }

            int qtdCenarios;
            while (true) {
                cout << "\nQuantos sistemas (jatos) deseja analisar? ";
                cin >> qtdCenarios;
                if (!cin.fail() && qtdCenarios > 0) break;
                cout << "Por favor, digite um numero inteiro positivo.\n";
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            for (int k = 0; k < qtdCenarios; k++) {
                cout << "\n------------------------------------------------\n";
                cout << "CONFIGURACAO DO JATO " << (k + 1) << "\n";
                cout << "------------------------------------------------\n";

                int ordem; 
                while (true) {
                    cout << "Digite a ordem da matriz (numero de deslocamentos n): ";
                    cin >> ordem;
                    if (!cin.fail() && ordem > 0) break;
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                vector<vector<double>> matrizA(ordem, vector<double>(ordem));
                vector<double> vetorF(ordem);

                char usarCalibracao;
                cout << "Deseja usar os dados padrao de calibracao? (s/n): ";
                cin >> usarCalibracao;

                if (usarCalibracao == 's' || usarCalibracao == 'S') {
                    cout << ">> Carregando dados de calibracao (Item C)...\n";
                    for(int i=0; i<ordem; i++) {
                        vetorF[i] = 1.0; 
                        for(int j=0; j<ordem; j++) {
                            if(i==j) matrizA[i][j] = 1.0; 
                            else matrizA[i][j] = 0.0;
                        }
                    }
                } 
                else {
                    cout << "\nDigite os coeficientes da Matriz A (" << ordem << "x" << ordem << "):\n";
                    for (int i = 0; i < ordem; i++) {
                        for (int j = 0; j < ordem; j++) {
                            cout << "A[" << i + 1 << "][" << j + 1 << "]: ";
                            cin >> matrizA[i][j];
                        }
                    }

                    cout << "\nDigite os termos independentes (Vetor f):\n";
                    for (int i = 0; i < ordem; i++) {
                        cout << "f[" << i + 1 << "]: ";
                        cin >> vetorF[i];
                    }
                }
                
                cout << "\n================================================\n";
                cout << "   RESUMO DOS DADOS - JATO " << (k+1) << "\n";
                cout << "================================================\n";
                
                cout << "Matriz A [" << ordem << "x" << ordem << "]:\n";
                for (int i = 0; i < ordem; i++) {
                    cout << "| ";
                    for (int j = 0; j < ordem; j++) {
                        cout << matrizA[i][j] << "\t"; 
                    }
                    cout << "|\n";
                }

                cout << "\nVetor f [" << ordem << "x1]:\n";
                for (int i = 0; i < ordem; i++) {
                    cout << "| " << vetorF[i] << " |\n";
                }
                cout << "================================================\n";

                cout << "\n>> Enviando dados para o metodo de opcao: " << opcao << "...\n";
                
                cout << ">> [TODO] Calcular deslocamentos 'd'\n";
                cout << ">> [TODO] Verificar se algum |d| > 2 (Explosao)\n";
            }

            cout << "\nPressione ENTER para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

        } while (true);
    }

public:
    SistemaJatos() {}

    void executar() {
        int escolhaTrabalho;

        do {
            titulo("SISTEMA DE ANALISE DE JATOS SUPERSONICOS");
            cout << "Selecione o modulo de trabalho:\n\n";
            cout << "1. Trabalho 1 (Raizes de Funcoes)\n";
            cout << "2. Trabalho 2 (Sistemas Lineares/Outros)\n";
            cout << "0. Encerrar Sistema\n";
            cout << "\nEscolha: ";
            
            cin >> escolhaTrabalho;

            if (cin.fail()) {
                cout << "Entrada invalida. Digite 1, 2 ou 0.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get(); 
                continue;
            }

            switch (escolhaTrabalho) {
                case 1:
                    executarTrabalho1();
                    break;
                case 2:
                    executarTrabalho2();
                    break;
                case 0:
                    cout << "Encerrando o sistema. Ate logo!\n";
                    return; 
                default:
                    cout << "Opcao invalida! Escolha 1 ou 2.\n";
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.get();
            }

        } while (true);
    }
};

#endif