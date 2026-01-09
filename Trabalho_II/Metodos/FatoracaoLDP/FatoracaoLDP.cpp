#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<double> Vetor;
typedef vector<Vetor> Matriz;

// ===== FATORAÇÃO LDP =====
bool fatoracaoLDPsegura(const Matriz& A, Matriz& L, Matriz& D, Matriz& P) {
    int n = A.size();

    L.assign(n, Vetor(n, 0.0));
    D.assign(n, Vetor(n, 0.0));
    P.assign(n, Vetor(n, 0.0));

    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;
        P[i][i] = 1.0;
    }

    for (int i = 0; i < n; i++) {
        double soma = 0.0;
        for (int k = 0; k < i; k++)
            soma += L[i][k] * D[k][k] * P[k][i];

        D[i][i] = A[i][i] - soma;

        if (fabs(D[i][i]) < 1e-12) {
            return false; // falha na fatoração
        }

        for (int j = i + 1; j < n; j++) {
            soma = 0.0;
            for (int k = 0; k < i; k++)
                soma += L[i][k] * D[k][k] * P[k][j];

            P[i][j] = (A[i][j] - soma) / D[i][i];
        }

        for (int j = i + 1; j < n; j++) {
            soma = 0.0;
            for (int k = 0; k < i; k++)
                soma += L[j][k] * D[k][k] * P[k][i];

            L[j][i] = (A[j][i] - soma) / D[i][i];
        }
    }
    return true;
}

// ===== SUBSTITUIÇÕES =====
Vetor substituicaoDireta(const Matriz& L, const Vetor& f) {
    int n = f.size();
    Vetor y(n);

    for (int i = 0; i < n; i++) {
        y[i] = f[i];
        for (int j = 0; j < i; j++)
            y[i] -= L[i][j] * y[j];
    }
    return y;
}

Vetor sistemaDiagonal(const Matriz& D, const Vetor& y) {
    int n = y.size();
    Vetor z(n);

    for (int i = 0; i < n; i++)
        z[i] = y[i] / D[i][i];

    return z;
}

Vetor substituicaoRetroativa(const Matriz& P, const Vetor& z) {
    int n = z.size();
    Vetor d(n);

    for (int i = n - 1; i >= 0; i--) {
        d[i] = z[i];
        for (int j = i + 1; j < n; j++)
            d[i] -= P[i][j] * d[j];
    }
    return d;
}

Matriz lerMatrizInterativa(int n) {
    Matriz A(n, Vetor(n));
    cout << "Digite os elementos da matriz A (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }
    cout << "Matriz A construída com sucesso.\n";
    return A;
}

Vetor lerVetorInterativo(int n) {
    Vetor f(n);
    cout << "Digite os elementos do vetor f (" << n << " elementos):\n";
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    cout << "Vetor f construído com sucesso.\n";
    return f;
}
/*
Essa função tem como objetivo verificar se a matriz é simétrica. Em problemas de Engenharia reais, matrizes de deformação são simétricas devido às leis da Física. 
Portanto, ela só alerta o usuário que ele não está trabalhando com uma matriz que representa um problema de engenharia real. 

bool matrizSimetrica(const Matriz& A) {
    int n = A.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (A[i][j] != A[j][i]) {
                return false;
            }
        }
    }
    return true;
}

*/

int main() {
    int n;

    cout << "=== Sistema Linear via Fatoracao LDP ===\n";
    cout << "Digite a ordem da matriz (n): ";
    cin >> n;

    if (n <= 0) {
        cout << "Erro: ordem da matriz invalida.\n";
        return 0;
    }

    Matriz A = lerMatrizInterativa(n);
    Vetor f = lerVetorInterativo(n);
    
    /*
    cout << "\n=== VERIFICACAO DE SIMETRIA ===" << endl;
    if (!matrizSimetrica(A)) {
        cout << "⚠️  ATENCAO: Matriz A nao e simetrica!" << endl;
        cout << "Para o problema fisico do jato, A deve ser simetrica." << endl;
        cout << "Deseja continuar mesmo assim? (s/n): ";
        
        char resposta;
        cin >> resposta;
        if (resposta != 's' && resposta != 'S') {
            cout << "Execucao interrompida pelo usuario.\n";
            return 0;
        }
        cout << "Continuando com matriz nao-simetrica...\n";
    } else {
        cout << "✅ Matriz A e simetrica.\n";
    }
    */

    Matriz L, D, P;

    if (!fatoracaoLDPsegura(A, L, D, P)) {
        cout << "Erro: matriz invalida para fatoracao LDP (pivo nulo).\n";
        return 0;
    }

    Vetor y = substituicaoDireta(L, f);
    Vetor z = sistemaDiagonal(D, y);
    Vetor d = substituicaoRetroativa(P, z);

    cout << "\nVetor solucao {d}:\n";
    for (int i = 0; i < n; i++) {
        cout << "d[" << i + 1 << "] = " << d[i] << endl;
    }
    cout << "\n=== ANALISE DE SEGURANÇA DO JATO ===" << endl;
    bool perigo = false;
    for (int i = 0; i < n; i++) {
        if (fabs(d[i]) > 2.0) {
            cout << "ALERTA: Parte " << (i+1) << " tem deslocamento de " 
                 << d[i] << " cm (limite: 2 cm)" << endl;
            perigo = true;
        }
    }

    if (perigo) {
        cout << "\n❌ CONCLUSAO: JATO EM RISCO DE EXPLOSAO!" << endl;
        cout << "   Algum deslocamento excede 2 cm." << endl;
    } else {
        cout << "\n✅ CONCLUSAO: JATO SEGURO." << endl;
        cout << "   Todos os deslocamentos dentro do limite de 2 cm." << endl;
    }
    

    cout << "\nSistema resolvido com sucesso.\n";
    return 0;
}