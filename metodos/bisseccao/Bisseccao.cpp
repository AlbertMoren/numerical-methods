#include "Bisseccao.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

ResultadoMetodo Bisseccao::calcular() {
    int iter = 0;
    double a = inicio;
    double b = fim;
    double c = a;

    double fa = funcao(a, a_param);
    double fb = funcao(b, a_param);

    if (fa * fb >= 0)
        return {0.0, 0, false};

    std::vector<LinhaBisseccao> tabela;   // armazena todas as linhas

    while (fabs(b - a) >= tolerancia && iter < maxIter) {

        c = (a + b) / 2.0;
        double fc = funcao(c, a_param);
        double intervalo = fabs(b - a);

        // guardar linha
        tabela.push_back({
            iter, a, fa, b, fb, c, fc, intervalo
        });

        if (fc == 0.0)
            break;

        if (fc * fa < 0)
            b = c;
        else
            a = c;

        fa = funcao(a, a_param);
        fb = funcao(b, a_param);

        iter++;
    }

    // Imprimir tabela
    imprimirTabela(tabela);

    return {(a + b) / 2.0, iter, true};
}

void Bisseccao::imprimirTabela(const std::vector<LinhaBisseccao>& tabela) const {
    using std::cout;
    using std::endl;
    using std::setw;
    using std::left;
    using std::right;

    // Largura para os campos numéricos em notação científica (12 caracteres)
    const int numWidth = 12;
    // Largura para a iteração (6 caracteres)
    const int iterWidth = 6;
    // Precisão científica
    const int precision = 5;

    cout << std::scientific << std::setprecision(precision);

    // --- Título ---
    cout << "==========================================================================================================" << endl;
    cout << "======================================Método da Bissecção=================================================" << endl;
    cout << "==========================================================================================================" << endl;

    // --- Cabeçalho ---
    cout << right // Alinha o texto do cabeçalho à direita para simular o alinhamento dos números
         << setw(iterWidth) << "Iter."
         << setw(numWidth) << "a"
         << setw(numWidth) << "f(a)"
         << setw(numWidth) << "b"
         << setw(numWidth) << "f(b)"
         << setw(numWidth) << "x_m"
         << setw(numWidth) << "f(x_m)"
         << setw(numWidth) << "I_Tam" << endl;
    
    // --- Linhas de Dados ---
    for (const auto& linha : tabela) {
        cout << setw(iterWidth) << linha.iter 
             << setw(numWidth) << linha.a  
             << setw(numWidth) << linha.fa 
             << setw(numWidth) << linha.b  
             << setw(numWidth) << linha.fb 
             << setw(numWidth) << linha.x  
             << setw(numWidth) << linha.fx 
             << setw(numWidth) << linha.intervalo
             << endl;
    }
}