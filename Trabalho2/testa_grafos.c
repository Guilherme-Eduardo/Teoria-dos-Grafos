/*******************************************
 * Leitura e impressao de grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  
  // cria grafo vazio
  grafo G = cria_grafo(1);
  
  // le n e adiciona vertices 1..n
  int n;
  printf ("Quantos vertíces tem o grafo? ");
  scanf("%d", &n); // qtd vertices
  while (n <= 0) {
    printf ("Número inválido. Digite novamente.\n");
    scanf ("%d", &n);
  }
  
  for (int i = 1; i <= n; i++)
    adiciona_vertice(i, "Teste", 1, G);

  // le pares u v e adiciona arestas {u,v}
  // termina quando digitar 0 0
  int id = 1;
  int u, v;
  printf ("Quais são as arestas deste grafo? Digite 0 0 no final\n");
  scanf("%d %d", &u, &v);
  while (u && v) {
    
    if (u < 0 || u > n || v < 0 || v > n) 
      printf ("Relação inválida. Digite novamente.\n");

    else {
      adiciona_aresta(id, u, v, G);
      ++id;
    }
    
    scanf("%d %d", &u, &v);
  }
  
  // imprime e destroi grafo
  imprime_grafo(G);
  destroi_grafo(G);
  
  return 0;
}
