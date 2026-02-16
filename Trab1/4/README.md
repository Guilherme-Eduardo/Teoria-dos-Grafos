# Grafos

## Exercício 4
  
Alterar a estrutura de dados do programa anterior para que seja possível representar um grafo ponderado. Atribua a cada aresta, como peso, a soma dos graus dos seus vértices (isto é, das suas pontas).


## Observações:

Adicionei uma função no arquivo "grafos.c" (adiciona_peso_aresta) que recebe a lista de todas as arestas do grafo G e atribui a cada aresta a soma dos graus de seus vertices.
Inclui essa função adiciona_peso_aresta dentro da função subgrafo_unduzido, dessa forma, toda vez que eu gerar um grafo induzido, será atualizado o peso das arestas.