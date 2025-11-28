#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include "metodos/funcoes/Funcoes.hpp" 
#include "metodos/bisseccao/Bisseccao.hpp"
#include "metodos/posicaoFalsa/PosicaoFalsa.hpp"
#include "metodos/newton/NewtonRaphson.hpp"


using namespace std;

// Estrutura para guardar todos os dados
struct RelatorioJato {
    int id;
    double parametro_a;
    ResultadoMetodo res_bisseccao;
    ResultadoMetodo res_pos_falsa;
    ResultadoMetodo res_newton;
};

void imprimirCabecalhoSimples() {
    cout << "| Jato | Parametro 'a' | Raiz Encontrada (d) | Iteracoes |    Status     |" << endl;
    cout << "|------|---------------|---------------------|-----------|---------------|" << endl;
}

void imprimirLinhaSimples(int id, double a, ResultadoMetodo res) {
    string status = (res.raiz > 2.0) ? "PERIGO!" : "Seguro";
    cout << "| " << setw(4) << id << " | " 
         << setw(13) << a << " | " 
         << setw(19) << fixed << setprecision(6) << res.raiz << " | " 
         << setw(9) << res.iteracoes << " | " 
         << setw(13) << status << " |" << endl;
}

int main() {
    // Configurações Iniciais Padrão
    double intervalo_ini = 2.0;
    double intervalo_fim = 3.0;
    double precisao = 1e-5;
    
    int opcao;

    do {
        // ================= MENU PRINCIPAL =================
        cout << endl;
        cout << "==================================================================" << endl;
        cout << "             SISTEMA DE ANÁLISE DE JATOS SUPERSÔNICOS             " << endl;
        cout << "==================================================================" << endl;
        cout << "Escolha o metodo de analise:" << endl;
        cout << "1. Metodo da Bisseccao" << endl;
        cout << "2. Metodo da Posicao Falsa" << endl;
        cout << "3. Metodo de Newton-Raphson" << endl;
        cout << "4. Executar TODOS (Gera Comparativo Completo)" << endl;
        cout << "0. Sair" << endl;
        cout << "------------------------------------------------------------------" << endl;
        cout << "Opcao: ";
        cin >> opcao;

        if (opcao == 0) {
            cout << "Encerrando o sistema..." << endl;
            break;
        }

        if (opcao < 1 || opcao > 4) {
            cout << "Opcao invalida! Tente novamente." << endl;
            continue;
        }

        // ================= COLETA DE DADOS =================
        int n_jatos;
        cout << "\nDigite o numero de jatos a serem analisados nesta rodada: ";
        cin >> n_jatos;

        vector<RelatorioJato> relatorios;

        for (int i = 0; i < n_jatos; i++) {
            RelatorioJato jato;
            jato.id = i + 1;
            cout << ">> Digite o parametro 'a' para o Jato " << jato.id << ": ";
            cin >> jato.parametro_a;

            // Inicializa resultados zerados
            ResultadoMetodo nulo = {0.0, 0, false};
            jato.res_bisseccao = nulo;
            jato.res_pos_falsa = nulo;
            jato.res_newton = nulo;

            // Executa apenas o(s) método(s) escolhido(s)
            if (opcao == 1 || opcao == 4) {
                Bisseccao metodo(jato.parametro_a, intervalo_ini, intervalo_fim, precisao);
                jato.res_bisseccao = metodo.calcular();
            }
            if (opcao == 2 || opcao == 4) {
                PosicaoFalsa metodo(jato.parametro_a, intervalo_ini, intervalo_fim, precisao);
                jato.res_pos_falsa = metodo.calcular();
            }
            if (opcao == 3 || opcao == 4) {
                double chute_inicial = (intervalo_ini + intervalo_fim) / 2.0;
                NewtonRaphson metodo(jato.parametro_a, chute_inicial, precisao);
                jato.res_newton = metodo.calcular();
            }
            
            relatorios.push_back(jato);
        }

        // ================= EXIBIÇÃO DOS RESULTADOS =================
        
        cout << endl << "------------------------------------------------------------------" << endl;
        
        // CASO 1, 2 ou 3: TABELA SIMPLES
        if (opcao != 4) {
            string nomeMetodo = (opcao == 1) ? "BISSECCAO" : (opcao == 2 ? "POSICAO FALSA" : "NEWTON-RAPHSON");
            cout << "RESULTADO: METODO DE " << nomeMetodo << endl;
            imprimirCabecalhoSimples();
            
            for (const auto& r : relatorios) {
                if (opcao == 1) imprimirLinhaSimples(r.id, r.parametro_a, r.res_bisseccao);
                else if (opcao == 2) imprimirLinhaSimples(r.id, r.parametro_a, r.res_pos_falsa);
                else if (opcao == 3) imprimirLinhaSimples(r.id, r.parametro_a, r.res_newton);
            }
            cout << "----------------------------------------------------------------" << endl;
        }
        // CASO 4: RELATÓRIO COMPLETO (IGUAL AO ANTERIOR)
        else {
            // Quadro de Segurança (Usando Newton como referência)
            cout << "QUADRO RESPOSTA: ANÁLISE DE SEGURANÇA (Ref: Newton)" << endl;
            cout << "| Jato | Parametro (a) | Deslocamento d (cm) |     STATUS        |" << endl;
            cout << "|------|---------------|---------------------|-------------------|" << endl;
            for (const auto& r : relatorios) {
                double raiz = r.res_newton.raiz;
                string status = (raiz > 2.0) ? "EXPLODE" : "SEGURO";
                cout << "| " << setw(4) << r.id << " | " 
                     << setw(13) << r.parametro_a << " | " 
                     << setw(19) << fixed << setprecision(5) << raiz << " | " 
                     << setw(15) << status << "   |" << endl;
            }

            // Quadro Comparativo
            cout << endl << "QUADRO COMPARATIVO DE MÉTODOS" << endl;
            cout << "| Jato (a)       | Método          | Raiz Encontrada | Iterações |" << endl;
            cout << "|----------------|-----------------|-----------------|-----------|" << endl;
            for (const auto& r : relatorios) {
                cout << "| Jato " << r.id << " (a=" << setprecision(1) << r.parametro_a << ") | "
                     << setw(15) << left << "Bisseccao" << " | " 
                     << setw(15) << right << setprecision(6) << r.res_bisseccao.raiz << " | " 
                     << setw(9) << r.res_bisseccao.iteracoes << " |" << endl;

                cout << "|                | "
                     << setw(15) << left << "Posicao Falsa" << " | " 
                     << setw(15) << right << setprecision(6) << r.res_pos_falsa.raiz << " | " 
                     << setw(9) << r.res_pos_falsa.iteracoes << " |" << endl;

                cout << "|                | "
                     << setw(15) << left << "Newton-Raphson" << " | " 
                     << setw(15) << right << setprecision(6) << r.res_newton.raiz << " | " 
                     << setw(9) << r.res_newton.iteracoes << " |" << endl;
                cout << "|----------------|-----------------|-----------------|-----------|" << endl;
            }
        }

        cout << "\nPressione Enter para continuar...";
        cin.ignore(); cin.get(); 

    } while (opcao != 0);

    return 0;
}