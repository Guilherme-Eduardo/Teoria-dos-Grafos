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
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

void destroi_grafo(grafo G) {
  if (!G) {
    fprintf(stderr, "Erro ao destruir o Grafo G: grafo nulo\n");
    return;
  }
  
  // Remove todas as arestas
  while (!vazio(arestas(G))) {
    remove_aresta(aresta_id(topo(arestas(G))), G);
  }
  // Remove todos os vértices
  while (!vazio(vertices(G))) {
    remove_vertice(vertice_id(topo(vertices(G))), G);
  }
  free(G->vertices);
  free(G->arestas);
  free(G);
  return;
}


// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {

  if (!G) G = cria_grafo();

  vertice novo_vertice = (vertice) malloc (sizeof(t_vertice));
  if (!novo_vertice) {
    fprintf (stderr, "Erro ao alocar memoria para ADD de um novo vertice\n");
    return;
  }
  
  novo_vertice->id = id; 
  novo_vertice->fronteira = cria_lista();
  empilha (novo_vertice, vertices(G));
  return;
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  if (!G || vazio(vertices(G))) {
    fprintf(stderr, "Erro ao remover o vértice: grafo nulo\n");
    exit(_ERRO_MALLOC_);
  }

  /* Remove o vértice V da lista de vértices e retorna o objeto */
  vertice v = remove_chave(id, vertices(G), (int_f_obj) vertice_id);
  if (!v) {
    fprintf(stderr, "Erro ao remover vértice: vértice com ID: %d não encontrado\n", id);
    return;
  }

  /* Remove todas as arestas incidentes no vértice v */
  while (!vazio(fronteira (v))) {
    aresta a = desempilha(fronteira(v));
    remove_aresta(aresta_id(a), G);
  }

  free(v->fronteira);
  free(v);
}



// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {  
  if (!G || u_id < 1 || v_id < 1) {
    fprintf (stderr, "Erro ao adicionar arestas\n");
    exit(_ERRO_MALLOC_);
  }

  aresta nova_aresta = (aresta) malloc (sizeof (t_aresta));
  if (!nova_aresta) {
    fprintf (stderr, "Erro ao alocar memoria para nova aresta\n");
    return;
  }

  /* Atribui os vertices que estão ligadas na aresta*/
  nova_aresta->u = busca_chave(u_id, vertices(G), (int_f_obj) vertice_id);
  nova_aresta->v = busca_chave(v_id, vertices(G), (int_f_obj) vertice_id);
  nova_aresta->id = id;

  if (!nova_aresta->u || !nova_aresta->v) {
    fprintf(stderr, "Erro ao adicionar aresta: vértices não encontrados\n");
    free(nova_aresta);
    return;
  }

  empilha (nova_aresta, fronteira (vertice_u(nova_aresta)));
  empilha (nova_aresta, fronteira (vertice_v(nova_aresta)));
  empilha (nova_aresta, arestas(G));
  return;
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  if (!G || vazio (arestas(G))) {
    fprintf (stderr, "Erro ao remover aresta\n");
    exit(_ERRO_MALLOC_);
  }

  aresta a = remove_chave (id, arestas(G), (int_f_obj) aresta_id);

  if (!a) {
    fprintf (stderr, "Erro ao remover uma aresta: Aresta com ID: %d não existe\n", id);
    return;
  }

  if (vertice_v(a)) {
    remove_chave (aresta_id(a), fronteira(vertice_v(a)), (int_f_obj) aresta_id);    
  }
  if (vertice_u(a)) {
    remove_chave (aresta_id(a), fronteira(vertice_u(a)), (int_f_obj) aresta_id);    
  }

  free (a);
  return;
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id =  vertice_id(vertice_u(e));
  int v_id =  vertice_id(vertice_v(e));
  printf("%d:{%d,%d}", aresta_id(e), u_id, v_id);
}