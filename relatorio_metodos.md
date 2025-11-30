# Relatorio final – metodos de raiz (Bisseccao, Posicao Falsa, Newton-Raphson)

## Problema e configuracao
- Equacao: `f(d) = a*d - d*ln(d)`; raiz positiva teórica `d = e^a`.
- Critico de seguranca: explode se `d > 2` (⇔ `a > ln(2) ≈ 0.6931`).
- Parametros do codigo:
  - Tolerancia `1e-5`.
  - Isolamento: troca de sinal em inteiros `[-100,100]` (se não achar, jato é ignorado).
  - Protecao: `f(d<=0)=1e9`.
  - Newton: chute = meio do intervalo isolado; derivada numerica central com `h = tolerancia`.
  - Posicao Falsa: se o intervalo encostar em 0, o limite esquerdo é empurrado para `1e-6` para evitar travar no `f(0)=1e9`.

## Casos de teste e comportamento por metodo
Legenda: B = Bisseccao, PF = Posicao Falsa, N = Newton. “Iter” = iteracoes ate convergir (ou limite).

| a      | d=e^a  | Status teórico | Intervalo isolado | B (iter) | PF (iter) | N (iter) | Observacoes |
|--------|--------|----------------|-------------------|----------|-----------|----------|-------------|
| -3.0   | 0.0498 | Seguro         | [0,1]             | ~17      | ~6–10     | 3–4      | PF agora converge; antes travava em 0 pelo 1e9. |
| -1.0   | 0.3679 | Seguro         | [0,1]             | ~17      | 5–7       | 3–4      | Todos convergem; N é o mais rápido. |
| -0.5   | 0.6065 | Seguro         | [0,1]             | ~17      | 5–7       | 3–4      | Comportamento estável. |
| 0      | 1.0000 | Seguro         | não isola         | —        | —         | —        | Produto=0; isolador não detecta troca de sinal; jato pulado. |
| 0.1    | 1.1052 | Seguro         | [1,2]             | ~17      | 5–6       | 3–4      | Convergência normal. |
| 0.5    | 1.6487 | Seguro         | [1,2]             | ~17      | 5         | 3–4      | Rápido em PF e N. |
| 0.6931 | 1.9999 | Seguro (limite)| [1,2]             | ~17      | 5         | 3–4      | Precisão importante para classificar. |
| 1.0    | 2.7183 | Explode        | [2,3]             | ~17      | 4         | 3–4      | Convergência rápida; d>2. |
| 2.0    | 7.3891 | Explode        | [7,8]             | ~17      | 4         | 3–4      | Convergência rápida. |
| 3.0    | 20.0855| Explode        | [20,21]           | ~17      | 4–5       | 3–4      | Ainda no range de isolamento. |
| 4.0    | 54.5981| Explode        | [54,55]           | ~17      | 4–5       | 3–4      | No limite do range, mas isola. |
| >4.605 | >100   | Explode        | não isola         | —        | —         | —        | Raiz >100; fora do range; jato ignorado. |

Notas sobre iteracoes:
- Bisseccao: com intervalo inicial de largura 1 e tolerancia 1e-5, fica em ~17 iter quase fixo.
- Posicao Falsa: 4–7 iter para `a` moderado; com epsilon em 0, também converge para `a` bem negativo (antes podia estagnar).
- Newton: 3–4 iter quando há isolamento (derivada na raiz é -1, estável).

## Analise por faixa de a
- `a < 0`: raiz em (0,1). Bisseccao ok; PF agora anda (epsilon evita `f(0)=1e9`); Newton rápido.
- `0 < a < ln(2)`: seguro; todos convergem; PF e N são mais rápidos.
- `a ≈ ln(2)`: limite; precisa de precisão para classificar seguro/explode.
- `a > ln(2)`: explode; todos convergem até ~4.6; acima disso o isolador falha (raiz >100).
- `a = 0`: raiz em 1, mas sem troca de sinal (produto=0); nenhum método é chamado.

## Analise por metodo
- Bisseccao: garante convergência se houver troca de sinal; mais lento (~17 iter); bom fallback.
- Posicao Falsa: mais rápido que bisseccao, preserva bracketing; ajuste de epsilon evita travar em 0 para `a` negativo.
- Newton-Raphson: mais rápido (3–4 iter) com bom chute; requer isolamento. Falha se derivada ≈ 0 em algum passo ou sem intervalo.

## Falhas e confiabilidade
- Sem isolamento (a=0, a>4.605, raiz fora do range): nenhum método roda.
- Estouro de iteracoes: 1000 (B/PF) ou 100 (N) = não convergiu; não use o valor para classificar seguro/explode.
- Classificação seguro/explode só é confiável se `convergiu=true` e critério de erro atendido.

## Conclusoes
- Rapidez: N > PF > B (quando há intervalo).
- Robustez: B > PF > N.
- Cobertura: para `a` muito grande, ampliar range de isolamento; para `a=0`, tratar produto=0 ou definir intervalo manual. 
