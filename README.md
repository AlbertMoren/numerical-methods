# numerical-methods

## Equipe

| Integrante       | Matricula |
| ---------------  | --------- |
|Albert Moren      | 515212    |
|Gustavo Cavalcante| 555217    |
|Werbster Marques  | 537205    |
|Bruno Augusto     | 554806    |
|Pedro Henrique    | 537759    |
|Caio Vidal        | 555025    |

## Tema

Um jato supersônico, ao vencer a barreira do som, tem o deslocamento de sua extremidade dada pela equação
**f(d) = a*d – d*ln(d)**, onde $d$ é o deslocamento medido em cm e $a$ é um parâmetro de ajuste para que se projete
um jato com a máxima segurança e eficiência possível. Caso esse deslocamento passe dos $2 cm$ esse jato irá
explodir, causando sérios danos e um prejuízo gigantesco. Vários testes e simulações são feitos de modo a
garantir que esse jato seja desenvolvido com toda segurança possível. 

## Objetivo

Desenvolva um sistema para calcular esse deslocamento d da extremidade de um jato supersônico desse tipo considerado com requisitos abaixo:

1. Implementar algoritmo para calcular d pelo método da Bissecção.
1. Implementar algoritmo para calcular d pelo método da Posição Falsa.
1. Implementar algoritmo para calcular d pelo método de Newton-Raphson.
1. Testar os seus resultados usando como padrão $a = 1$, isolamento = $(2, 3)$ e $e = 10-5$.
1. Fornecer um quadro resposta, variando os valores de a para vários jatos.
1. Fornecer um quadro comparativo, com isolamento, raízes e dados para cada método.
1. Analisar o efeito da variação do valor de a de cada jato, para cada método dado.
   
**Dados de entrada:** $n (número de jatos)$, $a (de cada jato)$ e $e (precisão)$.

**Dados de saída:** quadros resposta (com $d$ e erro para cada jato e método) e comparativo.

## Como execultar

```bash
mkdir build
cd build
cmake ..
make
./file.out
```
