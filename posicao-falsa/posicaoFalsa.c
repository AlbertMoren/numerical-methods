#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
double funcao_f(double d, double a) {
    if (d <= 0) {
        printf("Erro: 'd' deve ser positivo para log().\n");
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
        printf("Aviso: Limite de %d iterações atingido.\n", max_iter);
    }
    
    return xm;
}

int main() {
    int n;
    double epsilon;
    double a_param;
    double intervalo_a, intervalo_b;
    double raiz;
    int i;

    printf("--- Cálculo de Raízes (Tema 1: Jato Supersônico) ---\n");
    printf("Método: Posição Falsa\n\n");

    printf("Digite o valor da precisão (ex: 0.00001): ");
    scanf("%lf", &epsilon);

    printf("Digite o início do intervalo de isolamento (ex: 2.0): ");
    scanf("%lf", &intervalo_a);
    printf("Digite o fim do intervalo de isolamento (ex: 3.0): ");
    scanf("%lf", &intervalo_b);

    printf("Digite o número de jatos (n) a serem testados: ");
    scanf("%d", &n);

    printf("\n--- Quadro Resposta: Método da Posição Falsa ---\n");
    printf("---------------------------------------------------\n");
    printf("| Parâmetro 'a' | Deslocamento 'd' (Raiz) | Risco? |\n");
    printf("---------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("\nDigite o parâmetro 'a' para o Jato %d: ", i + 1);
        scanf("%lf", &a_param);

        raiz = posicao_falsa(intervalo_a, intervalo_b, a_param, epsilon);

        if (isnan(raiz)) {
            printf("| %13.4f | ERRO NO CÁLCULO (Verifique 'a' e intervalo) |\n", a_param);
        } else {
            const char* risco = (raiz > 2.0) ? "PERIGO!" : "Seguro";
            
            printf("| %13.4f | %23.10f | %-6s |\n", a_param, raiz, risco);
        }
    }

    printf("---------------------------------------------------\n");

    return 0;
}