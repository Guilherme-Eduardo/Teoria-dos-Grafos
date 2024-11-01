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
#include <string.h>

//---------------------------------------------------------
// funcoes adicionais:

int busca (int *v, int tam, int chave) {

    for (int i = 0; i < tam; i++) 
      if (v[i] == chave) 
        return 1; 
        
    return 0; 
}


void atualiza_peso (aresta e) { 
  
  e->peso = grau (vertice_u(e)) + grau (vertice_v(e)); 
}

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
char *elemento(vertice v){
  return v->atomo;
}


//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {

  grafo G = (grafo) malloc (sizeof(t_grafo));
  
  if (!G) {
    fprintf (stderr, "Erro na alocação de memória.");
    exit(_ERRO_MALLOC_);
  }

  G->vertices = cria_lista();
  G->arestas = cria_lista();
  
  return G;
}


// destroi grafo G (desaloca toda a memoria)    **verificar como sera feito a lista
void destroi_grafo(grafo G) {

  vertice aux;
  
  if (G->arestas) {
   
    while (!vazio(G->arestas)) 
      free (desempilha (G->arestas));
   
    free (G->arestas);
  }
  
  if (G->vertices) {
   
    while (!vazio (G->vertices)) {
      
      aux = desempilha (G->vertices);

      while (!vazio (aux->fronteira))
        desempilha (aux->fronteira);
      
      free (aux->fronteira);
      free (aux);
    }

    free (G->vertices);
  }
  
  free (G);  
}


// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G, char* atomo) {
  
  vertice new;

  if (!G) {
    fprintf (stderr, "Erro! Grafo não alocado.");
    return;
  }
    
  // Alocação
  new = (vertice) malloc (sizeof (t_vertice));
  if (!new) {
    fprintf (stderr, "Erro na alocação de memória");
    exit(_ERRO_MALLOC_);
  }
  
  // Inicialização
  new->id = id;
  printf ("Gravando elemento: %s\n", atomo);
  strcpy (new->atomo, atomo);
  new->fronteira = cria_lista ();

  // Adição no grafo
  empilha (new, G->vertices);

  return;
}


// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  
vertice rem, otherV;
  aresta a;

  if (!G) {
    fprintf (stderr, "Erro! Grafo não alocado.");
    return;
  }

  // Lista já vazia
  if (vazio (G->vertices))
    return;

  rem = remove_chave (id, G->vertices, (int_f_obj) vertice_id);

  while (!vazio (rem->fronteira)) {
    a = desempilha (rem->fronteira);

    // Encontra vertice de A diferente de REM
    if (a->u == rem) 
      otherV = a->v;
    else 
      otherV = a->u;

    // remove a aresta A da lista de fronteira do vertice OTHERV
    remove_chave (a->id, otherV->fronteira, (int_f_obj) aresta_id);

    // remove aresta do grafo
    remove_chave (a->id, G->arestas, (int_f_obj) aresta_id);

    // Deleta a estrutura da aresta. Os vertices mantem pois ou serão removidos posteriormente na função ou ainda serão utilizados.
    free (a);
  }

  free (rem->fronteira);
  free (rem);

  percorre_lista (G->arestas, (void_f_obj) atualiza_peso);
}


// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
  
  aresta new;
  
  if (!G) {
    fprintf (stderr, "Erro! Grafo não alocado.");
    return;
  }

  // Alocação
  new = (aresta) malloc (sizeof (t_aresta));
  if (!new) {
    fprintf (stderr, "Erro na alocação de memória");
    exit(_ERRO_MALLOC_);
  }
  
  // Inicialização
  new->id = id;
  new->u = busca_chave (u_id, G->vertices, (int_f_obj) vertice_id);
  new->v = busca_chave (v_id, G->vertices, (int_f_obj) vertice_id);

  // Adiciona a aresta nas fronteiras
  empilha (new, new->u->fronteira);
  empilha (new, new->v->fronteira);

  // Adição no grafo
  empilha (new, G->arestas);

  percorre_lista (G->arestas, (void_f_obj) atualiza_peso);

}


// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
  
  aresta rem;

  rem = busca_chave (id, G->arestas, (int_f_obj) aresta_id);

  remove_chave (id, rem->u->fronteira, (int_f_obj) aresta_id);
  remove_chave (id, rem->v->fronteira, (int_f_obj) aresta_id);

  free (rem);

  percorre_lista (G->arestas, (void_f_obj) atualiza_peso);

}

void subgrafo (int *cjt, int tam, int vertices, grafo G) {

  for (int i = 1; i <= vertices; i++) {
    if (!busca (cjt, tam, i))
      remove_vertice (i, G);
  }
  
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
  printf("\nVertices: <id> - <Átomo> - [grau]( <fronteira> )");
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id> - [<peso>]:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - <%s> - [%d]( ", vertice_id(v), elemento(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")");
}

// imprime a aresta e
void imprime_aresta(aresta e) {

  int u_id, v_id;

  u_id = vertice_id(vertice_u(e));
  v_id = vertice_id(vertice_v(e));

  printf("%d - [%d]:{%d,%d}", aresta_id(e), e->peso, u_id, v_id);

}