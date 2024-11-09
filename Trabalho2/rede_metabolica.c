/*******************************************
 * Biblioteca para manipulação de redes
 * metabólicas.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include "rede_metabolica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REA 1
#define MET 2
#define ENZ 3


/* Funcao responsavel por separar as palavras dependendo de um char separador*/
char *separa(char *linha, char separador) {
    if (!linha) {
      fprintf (stderr, "String vazia\n");
      return NULL; // Se a linha passada por parametro já for nula
    }

    char *posSeparador;
    posSeparador = strchr(linha, separador);

    if (!posSeparador) { // Se nao encontrar o separador, verifica se nao chegou na ultima parte a ser lida (antes do \n)
        if (strlen(linha))
          return linha;
        else {            
            return NULL;
        }
    }
    *posSeparador = '\0'; // Substitui o separador por um '\0' que indicara o final da string
    return linha;
}


int ehEnzima (vertice V) {

  if (vertice_particao (V) == ENZ)
    return 1;
  
  return 0;  
}


int qtd_enzima (vertice v) {

  if (vertice_particao(v) != REA)
    return 0;

  return percorreSoma (fronteira_entrada(v), ehEnzima);
}

/*************************************************************/

// Cria grafo G e lê a rede metabólica do arquivo apontado por <f_met>,
// adicionando em G as reações, enzimas e metabólitos, com as respectivas conexões.
// Devolve o grafo G.
grafo le_rede_metabolica(FILE *f_met) {
  
  grafo G = cria_grafo(1);
  
  char linha[1024];
  char* nomeMolecula;
  int idVertice = 1;
  int idAresta = 1;
  vertice reacaoAtual, verticeU;
 
  /*Ler até o fim do arquivo*/
  while (fgets(linha, sizeof(linha), f_met)) {
    /*Leio a linha até o char ' = ' */
    fscanf (f_met,"%[^=]", linha);    
    nomeMolecula = separa(linha, ' ');
    
    /*Encontrou o fim*/
    if (strncmp(nomeMolecula, "FIM", 3) == 0) {
        break;
    }

    /*Adiciona o vertice da reação no Grafo*/
    printf ("Criando vertice: %s\n", nomeMolecula);      
    adiciona_vertice (idVertice, nomeMolecula, REA, G);

    /* Obtenho ele para associar os outros vertices da reação*/
    reacaoAtual = busca_chave_int (idVertice, vertices(G), (int_f_obj) vertice_id);

    /*Vou lendo até encontrar outras moleculas*/
    while (nomeMolecula) {
      nomeMolecula = separa (nomeMolecula + strlen(nomeMolecula) + 1, ' '); 

      if(nomeMolecula[0] == 'M') {
        /* conecto os vertices MET ----> REA*/
        verticeU = busca_chave_str(nomeMolecula, vertices(G),(str_f_obj) vertice_rotulo);
        if (!verticeU) {
          printf ("Criando vertice: %s\n", nomeMolecula);
          adiciona_vertice(++idVertice, nomeMolecula, MET, G);
          adiciona_aresta(idAresta++,idVertice, vertice_id(reacaoAtual), G);
        }
        else {
          adiciona_aresta(idAresta++, idVertice, vertice_id (verticeU), G);
        }

      if (nomeMolecula[0] == '_') {        
        verticeU = busca_chave_str(nomeMolecula, vertices(G),(str_f_obj) vertice_rotulo);
        if (!verticeU) {
          printf ("Criando vertice: %s\n", nomeMolecula);
          adiciona_vertice(++idVertice, nomeMolecula, ENZ, G);
          adiciona_aresta(idAresta++,idVertice, vertice_id(reacaoAtual), G);
        }
        else {
          adiciona_aresta(idAresta++, idVertice, vertice_id (verticeU), G);
        }
      nomeMolecula = separa (nomeMolecula + strlen(nomeMolecula) + 1, ' '); 
    }

    /* Segunda parte: Os produtos da reação == REA ---> MET(Produtos) */
    fscanf (f_met,"%[^.]", linha);
    nomeMolecula = separa (linha, ' ');

    while (nomeMolecula) {
      if(nomeMolecula[0] == 'M') {
        /*Conecto os vertices REA ----> MET*/        
        vertice verticeU = busca_chave_str(nomeMolecula, vertices(G),(str_f_obj) vertice_rotulo);
        if (!verticeU) {
          printf ("Criando vertice: %s\n", nomeMolecula);
          adiciona_vertice(++idVertice, nomeMolecula, MET, G);
          adiciona_aresta(idAresta++, vertice_id(reacaoAtual), idVertice, G);
        }
        else {
          adiciona_aresta(idAresta++, vertice_id(reacaoAtual), vertice_id (verticeU), G);
        }
      }
      nomeMolecula = separa (nomeMolecula + strlen(nomeMolecula) + 1, ' '); 
    }
  }
  
  return G;
}

// Cria lista L e lê da entrada padrão os substratos iniciais, adicionando
// em L os vértices que representam os substratos.
// Devolve a lista de vértices L.
lista le_substratos(grafo G) {


  lista L = cria_lista();
  vertice v;
  char linha[1024], *substrato;

  scanf ("%s",linha);
  substrato = separa(linha, ' ');

  /*Eu estou criando e adicionando o vertice tanto para a lista
    quanto para o Grafo G. Creio que seja isso*/
  while (substrato && !strcmp(substrato, "FIM")) {
    v = busca_chave_str (substrato, vertices(G), (str_f_obj) vertice_rotulo);
    empilha (v, L);
    substrato = separa (substrato + strlen (substrato) + 1, ' '); 
  }
  
  return L;
}

// Função auxiliar que adiciona na rede metabólica uma reação falsa que gera
// todos os substratos iniciais (dado pela lista de vértices <substratos>).
// Deve adicionar um novo vértice com rótulo "SF" representando o substrato
// falso inicial e um novo vértice com rótulo "RF" representando a reação falsa.
// Deve também adicionar as arestas necessárias.
// ATENÇÃO: os rótulos "SF" e "RF" são usados no método imprime_reacoes_minimas().
void adiciona_reacao_falsa(lista substratos, grafo G) {
  
  int id = 0;

  adiciona_vertice (0, "RF", REA, G);
  
  while (!vazio(substratos)) {
    adiciona_aresta (id, 0, vertice_id(desempilha (substratos)), G);
    id--;
  }

  adiciona_vertice (-1, "SF", MET, G);
  adiciona_aresta (id, -1, 0, G);
}


// Função auxiliar que inicializa os custos e pais dos vértices do grafo G para
// iniciar busca em largura. O custo de uma reação é a quantidade de enzimas que
// a cataliza.
// Devolve uma lista de vértices para ser a Fila inicial do algoritmo de busca.
lista inicializa_custos(grafo G) {
  
  int id;
  lista F;
  vertice v;

  id = -1;
  F = cria_lista();

  v = busca_chave_int (id, vertices(G), (int_f_obj) vertice_id);
  while (v) {
    
    if (vertice_id(v) <= 0) 
      v->custo = 0;
    else 
      v->custo = INT_MAX;

    if (vertice_id(v) <= 0 && vertice_particao(v) == REA)
      empilha (v, F);
   
    id++;
    v = busca_chave_int (id, vertices(G), (int_f_obj) vertice_id);
  }
    
  return F;
}

// Algoritmo variante de Dijkstra que encontra o conjunto de reações de custo
// mínimo (número de enzimas) que produz todos os metabólitos da rede, considerando
// como substratos iniciais os metabólitos representados pelos vértices na lista
// substratos.
// Ao final do algoritmo, cada metabólito deve ter como pai (na estrutura vértice->pai)
// a reação "ótima" que o produz.
void processa(lista substratos, grafo G) {
  
  vertice v, aux;
  lista copy = cria_lista ();

  // adiciona uma reação falsa para iniciar a busca
  adiciona_reacao_falsa(substratos, G);
  
  // inicializa custos, pais e fila inicial da busca F
  lista F = inicializa_custos(G);
  
  // variante do Algoritmo de Dijkstra para resolver o problema
  while (!vazio(F)) {
    
    v = remove_min (F, custo(v));
    while (!vazio(fronteira_saida(v))) {
      aux = desempilha (fronteira_saida(v));
      empilha (aux, copy);

      if (aux->estado == PROCESSADO) 
        if (aux->custo > v->custo + qtd_enzima(aux)) {
          aux->pai = v;
          aux->custo = v->custo + qtd_enzima(aux);
        }

        if (aux->estado == ABERTO) {
          aux->pai = v;
          aux->custo = v->custo + qtd_enzima(aux);
          aux->estado = PROCESSADO;
          empilha (aux, F);
        }
      }

    v->estado = FECHADO;
    free (v->fronteira_saida);
    v->fronteira_saida = copy; 
  }
}

// Imprime resultados com base nos pais dos vértices (na estrutura vértice->pai),
// calculados pelo método processa().
void imprime_reacoes_minimas(grafo G) {
  
  // Para cada metabólito, imprime as reações "ótimas"
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice v = conteudo(n);
    if (vertice_particao(v) == METABOLITO && pai(v)) {
      printf("%s: ", vertice_rotulo(v));
      
      // cria lista de reações necessárias para sua produção
      lista R = cria_lista();
      empilha(pai(v), R);
      
      // seta todas as reações como ABERTOS, para não repetir
      for (no p = primeiro_no(vertices(G)); p; p = proximo(p)) {
        vertice w = conteudo(p);
        if (vertice_particao(w) == REACAO)
          w->estado = ABERTO;
      }
      
      // Enquanto tiver reações ainda não processadas, imprime
      while (!vazio(R)) {
        vertice w = desempilha(R);
        if (estado(w) == ABERTO && strcmp(vertice_rotulo(w), "RF")) { // não inclui a reação falsa
          printf("%s ", vertice_rotulo(w));
          w->estado = FECHADO;
          
          // coloca na lista as reações antecessoras
          for (no p = primeiro_no(fronteira_entrada(w)); p; p = proximo(p)) {
            aresta e = conteudo(p);
            vertice u = vertice_u(e);
            if (vertice_particao(u) == METABOLITO && pai(u))
              empilha(pai(u), R);
          }
        }
      }
      printf("\n");
      free(R);
    }
  }
}
