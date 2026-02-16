/*******************************************
 * Leitura e impressao de grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  
  // cria grafo vazio
  grafo G = cria_grafo();
  
  // le n e adiciona vertices 1..n
  fprintf (stdout, "Informe a quantidade de vertices para o grafo G: \n");
  int n;
  scanf("%d", &n); // qtd vertices
  
  if (n < 1) {
    fprintf (stderr, "Numero invalido\n");
    destroi_grafo(G);
    return 1;
  }
  
  for (int i = 1; i <= n; ++i)
    adiciona_vertice(i, G);
  
  
  // le pares u v e adiciona arestas {u,v}
  // termina quando digitar 0 0
  int id = 1;
  int u, v;
  fprintf (stdout, "Informe o par de vertices para incluir uma aresta"
          "(valor zero interrompe a inclusao): \n");
  scanf("%d %d", &u, &v);
  while (u && v) {
    adiciona_aresta(id, u, v, G);   
    ++id;
    scanf("%d %d", &u, &v);
  }
  
  // imprime informacoes do grafo e o destroi
  imprime_grafo(G);
  destroi_grafo(G);

  fprintf (stdout, "Grafo destruido com sucesso\n");
  return 0;
}
