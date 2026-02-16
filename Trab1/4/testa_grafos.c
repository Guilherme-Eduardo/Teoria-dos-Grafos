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
  lista X = cria_lista();
  
  // le n e adiciona vertices 1..n
  fprintf (stdout, "Informe a quantidade de vertices para o grafo G: \n");
  int n;
  scanf("%d", &n); // qtd vertices
  
  for (int i = 1; i <= n; ++i)
    adiciona_vertice(i, G);

  if (n < 1) {
    fprintf (stderr, "Numero invalido\n");
    destroi_grafo(G);
    return 1;
  }
    
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

  adiciona_peso_aresta (arestas(G));
  
  // imprime informacoes do grafo e o destroi
  fprintf (stdout, "Imprimindo Grafo: \n");
  imprime_grafo(G);

  /* Para o exercício 3*/

  fprintf (stdout, "Informe os indices do vertices a seguir para criar um grafo G[X]: \n");
  scanf ("%d", &n);
  while (n != 0) {
    obj vertice = busca_chave (n, G->vertices, (int_f_obj) vertice_id);
    if (vertice) empilha (vertice, X);
    scanf ("%d", &n);
  }

  fprintf (stdout, "Mostrando o grafo G[X]\n");
  G = subgrafo_induzido (X, G);
  imprime_grafo(G);

  destroi_grafo(G);
  while (!vazio (X)) desempilha(X);  
  free (X);

  fprintf (stdout, "Grafo destruido com sucesso\n");
  return 0;
}
