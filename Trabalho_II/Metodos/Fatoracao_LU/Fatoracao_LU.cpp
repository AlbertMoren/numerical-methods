#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

void Fatoracao_LU(int n, vector<vector<double>> A, vector<double> f) {
    vector<vector<double>> L(n, vector<double>(n, 0));
    vector<vector<double>> U(n, vector<double>(n, 0));

    // Decomposição LU ---
    for (int i = 0; i < n; i++) {
        // Triangular Superior U
        for (int k = i; k < n; k++) {
            double soma = 0;
            for (int j = 0; j < i; j++)
                soma += (L[i][j] * U[j][k]);
            U[i][k] = A[i][k] - soma;
        }

        // Triangular Inferior L
        for (int k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1; 
            else {
                double soma = 0;
                for (int j = 0; j < i; j++)
                    soma += (L[k][j] * U[j][i]);
                L[k][i] = (A[k][i] - soma) / U[i][i];
            }
        }
    }

    // Substituição para frente (Ly = f)
    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        double soma = 0;
        for (int j = 0; j < i; j++)
            soma += L[i][j] * y[j];
        y[i] = f[i] - soma;
    }

    // Substituição para trás (Ud = y) 
    vector<double> d(n);
    for (int i = n - 1; i >= 0; i--) {
        double soma = 0;
        for (int j = i + 1; j < n; j++)
            soma += U[i][j] * d[j];
        d[i] = (y[i] - soma) / U[i][i];
    }

    // Verificação de Segurança (Módulo dos Deslocamentos) ---
    bool explodiu = false;
    cout << fixed << setprecision(5);
    cout << "\n--- RELATORIO DE DESLOCAMENTOS DO JATO ---" << endl;
    
    for (int i = 0; i < n; i++) {
        double modulo = abs(d[i]);
        cout << "Deslocamento d" << i + 1 << ": " << setw(8) << d[i] << " cm";
        
        if (modulo > 2.0) {
            cout << " [CRITICO: > 2cm]";
            explodiu = true;
        }
        cout << endl;
    }

    cout << "------------------------------------------" << endl;
    if (explodiu) {
        cout << "RESULTADO: O JATO EXPLODIU! (Limite de seguranca violado)" << endl;
    } else {
        cout << "RESULTADO: VOO BEM SUCEDIDO. Deslocamentos dentro da margem." << endl;
    }
}

int main() {
    // Exemplo de entrada do pdf do trabalho (Matriz A e Vetor f)
    int n = 3;
    vector<vector<double>> A = {
        {3, -2, 1},
        {1, -3, 4},
        {9, 4, -5}
    };
    vector<double> f = {8, 6, 11};

    Fatoracao_LU(n, A, f);

    return 0;
}