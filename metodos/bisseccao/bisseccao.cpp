#include <iostream> // Para std::cout, std::cin, std::endl
#include <cmath>    // Para log() (ln) e fabs() (valor absoluto)
#include <iomanip>  // Para std::setprecision (configurar precisão da saída)

// Variável global para o parâmetro de ajuste
// Precisamos dela global para que a função g(d) possa acessá-la
double parametro_a;

/**
 * @brief A função g(d) = f(d) que queremos resolver.
 * @param d O deslocamento.
 * @return O valor de g(d).
 */
double g(double d) {
    if (d <= 0) {
        return 1.0e9; 
    }
    // Usa a variável global 'parametro_a'
    return parametro_a * d - d * log(d);
}

/**
 * @brief Implementa o método da Bisseção.
 * (Esta função não muda em nada)
 */
double bissecao(double a, double b, double tolerancia, int& iteracoes) {
    if (g(a) * g(b) >= 0) {
        std::cout << "  Erro: A função não muda de sinal no intervalo [" 
                  << a << ", " << b << "]." << std::endl;
        std::cout << "  g(a) = " << g(a) << ", g(b) = " << g(b) << std::endl;
        return -1; 
    }

    double c = a; 
    iteracoes = 0;

    while (fabs(b - a) >= tolerancia) {
        iteracoes++;
        c = (a + b) / 2.0;

        if (g(c) == 0.0) {
            break;
        }
        else if (g(c) * g(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return (a + b) / 2.0; 
}

// ==========================================================
// A MÁGICA ACONTECE AQUI: FUNÇÃO MAIN MODIFICADA
// ==========================================================
int main() {
    // Configura a saída para mostrar 8 casas decimais
    std::cout << std::fixed << std::setprecision(8);

    // --- 1. Pergunta o número de jatos (n) ---
    int n_jatos;
    std::cout << "Digite o número de jatos (n) a analisar: ";
    std::cin >> n_jatos;
    std::cout << "-------------------------------------" << std::endl;


    // --- 2. Inicia o loop para rodar 'n' vezes ---
    for (int i = 0; i < n_jatos; ++i) {
        
        std::cout << "\n--- Analisando o Jato " << (i + 1) << " ---" << std::endl;

        // --- 3. Pede os dados de CADA jato ---
        double intervalo_inicio, intervalo_fim, tolerancia;

        // Pergunta o 'a' e armazena na variável global
        std::cout << "  Digite o parâmetro 'a' para este jato: ";
        std::cin >> parametro_a; 

        std::cout << "  Digite o início do intervalo (ex: 2.0): ";
        std::cin >> intervalo_inicio;

        std::cout << "  Digite o fim do intervalo (ex: 3.0): ";
        std::cin >> intervalo_fim;

        std::cout << "  Digite a precisão/tolerância (ex: 1e-5): ";
        std::cin >> tolerancia;
        
        // Variável para contar as iterações deste jato
        int num_iteracoes = 0;
        std::cout << "\n  Calculando..." << std::endl;

        // --- 4. Chama a bisseção (exatamente como antes) ---
        double raiz = bissecao(intervalo_inicio, intervalo_fim, tolerancia, num_iteracoes);

        // --- 5. Mostra o resultado deste jato ---
        if (raiz != -1) {
            std::cout << "\n  --- Resultado do Jato " << (i + 1) << " ---" << std::endl;
            std::cout << "  Raiz (deslocamento d) encontrada: " << raiz << " cm" << std::endl;
            std::cout << "  Valor de g(d) na raiz: " << g(raiz) << std::endl;
            std::cout << "  Número de iterações: " << num_iteracoes << std::endl;

            if (raiz > 2.0) {
                std::cout << "\n  AVISO: O deslocamento (" << raiz << " cm) é maior que 2 cm. O jato explodiria!" << std::endl;
            } else {
                std::cout << "\n  INFO: O deslocamento (" << raiz << " cm) é seguro." << std::endl;
            }
        }
        std::cout << "-------------------------------------" << std::endl;
    } // --- Fim do loop for ---

    std::cout << "\nAnálise de " << n_jatos << " jatos concluída." << std::endl;

    return 0; // Termina o programa com sucesso
}