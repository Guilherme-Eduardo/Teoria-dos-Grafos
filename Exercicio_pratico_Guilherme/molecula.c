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
#include <string.h>

int main(int argc, char **argv) {

  /*Verifica a quantidade de argumentos na chamada do programa*/
  if (argc != 2) {
    fprintf (stderr, "Forma de uso: ./molecula.c <arquivo.mol>\n");
    return 1;
  }

  /*Abertura do arquivo*/
  FILE *arquivo = fopen (argv[1], "r");
  if (!arquivo) {
    fprintf (stderr, "Erro ao abrir arquivo\n");
    return 1;
  }

  
  grafo G = cria_grafo();
  char linha[1024];
  char *nomeAtomo;  
  int numVertices, numArestas,vertice1, vertice2, tipoLigação, id = 1;

  /*Ignora cabeçalho do arquivo*/
  for (int i = 0; i < 3; i++)
    fgets(linha, sizeof(linha), arquivo);   
  
  /*Le o número de vertices e arestas do grafo*/
  fscanf (arquivo, "%d %d", &numVertices, &numArestas);
  fgets(linha, sizeof(linha), arquivo); 

  //printf ("Testes\nVertices: %d\nArestas: %d\n", numVertices, numArestas);
  
  /* Adiciona vertice com o nome da molecula*/
  for (int i = 1; i <= numVertices; i++) {
    fgets(linha, sizeof(linha), arquivo);                               /*Le a linha do arquivo*/   
    nomeAtomo = separa (linha, ' ');                                    /*Separa as informações*/
    while (nomeAtomo) {                                           
      if (*nomeAtomo >= 'A' && *nomeAtomo <= 'Z') {                     /*Confere se o dado é o nome do Atomo*/
        //printf ("Nome do elemento: %s\n", nomeAtomo);
        adiciona_vertice(i, G, nomeAtomo);        
        break;
      }
      nomeAtomo = separa (nomeAtomo + strlen(nomeAtomo) + 1, ' ');      /*Continua lendo as informações da mesma linha*/
    }    
  }

  /*Conecta 2 vertices conforme o tipo de ligação (simples/dupla/tripla)*/
  for (int i = 1; i <= numArestas; i++) {
    int j = 0;
    fscanf (arquivo, "%d %d %d", &vertice1, &vertice2, &tipoLigação);       
    while (j < tipoLigação) {      
      adiciona_aresta(id++, vertice1, vertice2, G);
      j++;
    }    
    fgets (linha, sizeof(linha), arquivo);
  }

  /*Limpa os dados na memória*/
  fclose (arquivo);
  imprime_grafo(G);
  destroi_grafo(G);
  
  return 0;
}
