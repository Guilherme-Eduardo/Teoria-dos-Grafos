/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
}
char* vertice_rotulo(vertice v) {
  return v->rotulo;
}
int vertice_particao(vertice v) {
  return v->particao;
}
int custo(vertice v) {
  return v->custo;
}
int estado(vertice v) {
  return v->estado;
}
vertice pai(vertice v) {
  return v->pai;
}
lista fronteira_entrada(vertice v) {
  return v->fronteira_entrada;
}
lista fronteira_saida(vertice v) {
  return v->fronteira_saida;
}
int aresta_id(aresta e) {
  return e->id;
}
vertice vertice_u(aresta e) {
  return e->u;
}
vertice vertice_v(aresta e) {
  return e->v;
}
int grafo_id(grafo G) {
  return G->id;
}
lista vertices(grafo G) {
  return G->vertices;
}
lista arestas(grafo G) {
  return G->arestas;
}

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo(int id) {
  if (id <= 0 ) {
    fprintf (stderr, "Valor inválido.\n");
    return NULL;
  }

  grafo G = (grafo) malloc (sizeof(t_grafo));
  if (!G) {
    fprintf (stderr, "Erro ao alocar memória para o grafo G.\n");
    return NULL;
  }

  G->id = id;
  G->arestas = cria_lista();
  G->vertices = cria_lista();
  
  return G;

}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  if (!G) {
    fprintf (stderr, "Erro ao acessar grafo G.\n");
    return;
  }

  /*Remove todos os vértices*/
  while (!vazio(vertices(G))) {
    remove_vertice(vertice_id(topo(vertices(G))), G);      
  }

  /*Remove todas as arestas*/
  // while (!vazio(arestas(G))) {    
  //   remove_aresta(aresta_id(topo(arestas(G))), G);
  // }

  free (vertices(G));
  free (arestas (G));
  free (G);
}

// cria novo vertice com id <id>, rotulo <rotulo>, particao <particao>
// e adiciona ao grafo G
void adiciona_vertice(int id, char *rotulo, int particao, grafo G) {
  
  if (!G || !rotulo) {
    fprintf (stderr, "Erro ao acessar o grafo G.\n");
    return;
  }

  vertice novo_vertice = (vertice) malloc (sizeof (t_vertice));
  if (!novo_vertice) {
    fprintf (stderr, "Erro ao alocar vértice.\n");
    return;
  }
  novo_vertice->id = id;
  novo_vertice->custo = 0;
  novo_vertice->particao = particao;
  novo_vertice->estado = ABERTO; //Professor criou os defines para aberto, processado e fechado.
  novo_vertice->fronteira_entrada = cria_lista();
  novo_vertice->fronteira_saida = cria_lista();
  novo_vertice->pai = NULL;
  strcpy (novo_vertice->rotulo, rotulo);
  empilha(novo_vertice, vertices(G));

  return;  
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  if (!G) {
    fprintf (stderr, "Erro ao acessar o grafo G.\n");
    return;
  }

  /*Remove o vertice do grafo G*/
  vertice v = remove_chave_int(id, vertices (G), (int_f_obj) vertice_id);

  /*Verifica Remove as arestas associadas ao vertice que está sendo removido (entrada/saida) */
  while (!vazio (fronteira_entrada(v))) {
    aresta a = desempilha (fronteira_entrada(v));
    remove_aresta (aresta_id (a), G);
  }

  while (!vazio (fronteira_saida(v))) {
    aresta a = desempilha (fronteira_saida(v));
    remove_aresta (aresta_id(a), G);
  }

  free (fronteira_entrada(v));
  free (fronteira_saida(v));
  free (v);
  return;  
}

// cria aresta com id <id> incidente a vertices com ids
// <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
  if (!G) {
    fprintf (stderr, "Erro ao acessar o grafo G.\n");
    return;
  }

  aresta nova_aresta = (aresta) malloc (sizeof (t_aresta));
  if (!nova_aresta) {
    fprintf (stderr, "Erro ao alocar aresta.\n");
    return;
  }

  /*Conecta os vertices na aresta criada */
  nova_aresta->id = id;
  nova_aresta->u = busca_chave_int(u_id, vertices(G), (int_f_obj) vertice_id);
  nova_aresta->v = busca_chave_int(v_id, vertices(G), (int_f_obj) vertice_id);

  if (!vertice_u(nova_aresta) || !vertice_v(nova_aresta)) {
    fprintf (stderr, "Erro ao adicionar nova aresta.\n");
    return;
  }

  /*Define a direção da aresta == u ----> v*/
  empilha (nova_aresta, fronteira_saida(vertice_u(nova_aresta)));
  empilha (nova_aresta, fronteira_entrada(vertice_v(nova_aresta)));
  empilha(nova_aresta, arestas(G));

  return;

}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  if (!G) {
    fprintf (stderr, "Erro ao acessar grafo G.\n");
    return;
  }

  /*Remove a aresta do grafo G*/
  aresta a = remove_chave_int (id, arestas(G), (int_f_obj) aresta_id);

  /*Remove a aresta dos vertices associados a ela (tanto na entrada quanto na saida)*/
  remove_chave_int (aresta_id(a), fronteira_saida (vertice_u(a)), (int_f_obj) aresta_id);
  remove_chave_int (aresta_id(a), fronteira_entrada (vertice_v(a)), (int_f_obj) aresta_id);

  free (a);
  return;
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve os graus do vertice v
int grau_entrada(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_entrada(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}
int grau_saida(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_saida(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  // imprimindo apenas a estrutura do grafo
  printf("%d\n", grafo_id(G));
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
  printf("\nEstrutura:\n");
  
  //imprime_lista(arestas(G), (void_f_obj) imprime_estrutura_aresta);
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("(id:%d, rotulo:%s, grau_entrada:%d, fronteira_entrada:{ ", vertice_id(v), vertice_rotulo(v), grau_entrada(v));
  imprime_lista(fronteira_entrada(v), (void_f_obj) imprime_aresta);
  printf("}, grau_saida:%d, fronteira_saida:{ ", grau_saida(v));
  imprime_lista(fronteira_saida(v), (void_f_obj) imprime_aresta);
  printf("})\n");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("(id:%d {%d,%d})", aresta_id(e), u_id, v_id);
}

// imprime aresta e no formato de entrada para
// https://graphonline.ru/en/create_graph_by_edge_list
void imprime_estrutura_aresta(aresta e) {
  char *u_rot = vertice_rotulo(vertice_u(e));
  char *v_rot = vertice_rotulo(vertice_v(e));
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:%s > %d:%s\n", u_id, u_rot, v_id, v_rot);
}
