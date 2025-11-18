#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

double funcao_f(double d, double a) {
    if (d <= 0) {
        cerr << "Erro: 'd' deve ser positivo para log()." << endl;
        return NAN;
    }
    return (a * d) - (d * log(d));
}

double posicao_falsa(double a_intervalo, double b_intervalo, double a_param, double epsilon) {
    
    double fa = funcao_f(a_intervalo, a_param);
    double fb = funcao_f(b_intervalo, a_param);
    
    if (fa * fb >= 0) {
        return NAN;
    }

    double xm = a_intervalo;
    double fxm = fa;
    int max_iter = 1000;
    int i = 0;

    while (fabs(fxm) > epsilon && i < max_iter) {
        
        xm = (a_intervalo * fb - b_intervalo * fa) / (fb - fa);
        fxm = funcao_f(xm, a_param);

        if (isnan(fxm)) {
            return NAN;
        }

        if (fa * fxm < 0) {
            b_intervalo = xm;
            fb = fxm;
        } else {
            a_intervalo = xm;
            fa = fxm;
        }
        i++;
    }

    if (i == max_iter) {
        cout << "Aviso: Limite de " << max_iter << " iterações atingido." << endl;
    }
    
    return xm;
}

int main() {
    const double epsilon = 1e-5;
    const double intervalo_a = 2.0; 
    const double intervalo_b = 3.0;

    int n;
    double a_param;
    double raiz;

    cout << "--- Cálculo de Raízes (Tema 1: Jato Supersônico) ---" << endl;
    cout << "Método: Posição Falsa" << endl << endl;
    
    cout << "Usando parâmetros Padrão:" << endl;
    cout << "Precisão (epsilon): " << epsilon << endl;
    cout << "Intervalo [a, b]:   [" << intervalo_a << ", " << intervalo_b << "]" << endl << endl;

    cout << "Digite o número de jatos (n) a serem testados: ";
    cin >> n;

    cout << left << endl; 
    cout << "--- Quadro Resposta: Método da Posição Falsa ---" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "| " << setw(13) << "Parâmetro 'a'" << " | " 
         << setw(23) << "Deslocamento 'd' (Raiz)" << " | "
         << setw(7) << "Risco?"  << " |" << endl;
    cout << "----------------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        cout << endl << "Digite o parâmetro 'a' para o Jato " << i + 1 << ": ";
        cin >> a_param;

        raiz = posicao_falsa(intervalo_a, intervalo_b, a_param, epsilon);

        if (isnan(raiz)) {
            cout << "| " << setw(13) << fixed << setprecision(4) << a_param
                 << " | " << setw(33) << "ERRO NO CÁLCulo (Verifique 'a' e intervalo)" << " |" << endl;
        } else {
            string risco = (raiz > 2.0) ? "PERIGO!" : "Seguro";
            
            cout << "| " << setw(13) << fixed << setprecision(4) << a_param
                 << " | " << setw(23) << fixed << setprecision(10) << raiz
                 << " | " << setw(7) << risco << " |" << endl;
        }
    }

    cout << "----------------------------------------------------------------" << endl;
    
    cout << right; 

    return 0;
}