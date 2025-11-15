// ******************CONTEXTO**************************** 

/*
Um jato supersônico, ao vencer a barreira do som, tem o deslocamento de sua extremidade dada pela equação
f(d) = a*d – d*ln(d), onde d é o deslocamento medido em cm e a é um parâmetro de ajuste para que se projete
um jato com a máxima segurança e eficiência possível. Caso esse deslocamento passe dos 2 cm esse jato irá
explodir, causando sérios danos e um prejuízo gigantesco. Vários testes e simulações são feitos de modo a
garantir que esse jato seja desenvolvido com toda segurança possível. Desenvolva um sistema para calcular
esse deslocamento d da extremidade de um jato supersônico desse tipo considerado com requisitos abaixo:
*/

// função a ser analisada: f(d) = a*d – d*ln(d)
//testar os resultados usando como padrão a=1, isolamento = (2,3) e e=10⁻⁵.
//metodo: Newton-Raphson
//Feito por: Gustavo C. Martins - 555217

#include <iostream>
#include <cmath>
#include <utility>
using namespace std;

double f(float d, float a){
    return a*d-(d*log(d));
}

double derivada(double (*func)(float, float), double d, double h){
    return (func(d + h, 1) - func(d - h, 1)) / (2*h); // f'(d) = -ln(d)
}

pair<double, int> Newton_Raphson(float d, float a, float e){
    int passos=0;
    while(true){
        double f_d = f(d,a);
        double d_dd = derivada(f,d,e);
        double d_i = d - (f_d/d_dd);
        passos++;
        double erro = fabs(d-d_i);
        if (erro < e) return make_pair(d_i, passos);
        d = d_i;
    }
}

int main()
{
    float d_0 = 2.5; // "chute inicial"
    float a = 1.0; 
    float e = 0.00001; // erro
    pair<double, int> res= Newton_Raphson(d_0,a,e);
    cout << "Resultado: " << res.first << endl;
    cout << "Quantidade de passos necessários: " <<res.second << endl;
    return 0;
}
