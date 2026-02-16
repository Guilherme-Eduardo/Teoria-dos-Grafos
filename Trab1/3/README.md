# Grafos

## Exercício 3
  
Usando o código do item 2, faça um programa que lê um conjunto de vértices X e transforma o grafo G no grafo G[X].

## OBS: 

Basicamente eu criei uma lista X com os vértices que eu gostaria transformar o grafo G em G[X].
Sendo assim, adicionei uma função (subgrafo_induzido()) no arquivo "grafos.c" para que recebesse uma lista e um grafo como parâmetros.

Além disso, a função possui um laço que compara o ID dos vértices do grafo com o ID dos vértices que estão na lista X.
Caso a resposta seja "não" (retorno NULL), eu removo esse vértice do grafo G, pois ele não está na minha lista X.

Interpretei o enunciado e entendi que não era para criar um novo grafo e sim transformar o grafo G em G[X].

No arquivo testa_grafos.c, eu adicionei alguns printf's e um laço para preencher a lista X.


