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



// Funcao responsavel por separar as palavras dependendo de um char separador
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
            fprintf (stderr, "String nula\n");
            return NULL;
        }
    }
    *posSeparador = '\0'; // Substitui o separador por um '\0' que indicara o final da string
    return linha;
}

/*Ignora o cabeçalho do arquivo .mol*/
void ignora_cabecalho (FILE *arquivo) {
  if (!arquivo) {
    fprintf (stderr, "Erro ao ler arquivo.\n");
    return;
  }
  
  char linha[1024];
  for (int i = 0; i < 3; i++)
    fgets(linha, sizeof(linha), arquivo);  
  
}

/*Le o numero de arestas e vertices do arquivo .mol*/
void le_vertices_arestas (FILE *arquivo, int *numVertices, int *numArestas) {
  if (!arquivo) {
    fprintf (stderr, "Erro ao ler arquivo.\n");
    return;
  }
  char linha[1024];
  ignora_cabecalho (arquivo);
  
  fscanf (arquivo, "%d %d", numVertices, numArestas);
  fgets(linha, sizeof(linha), arquivo); 
}

/*Verifica se a palavra encontrada se trata de um atomo. Usa a tabela ASCII para verificar*/
int eh_atomo (char *nomeAtomo) {
 if (!nomeAtomo) return 0;
  printf ("nomeAtomo = %s\n ", nomeAtomo);
 for (int i = 0; i < strlen (nomeAtomo) - 1; i++){
    if (nomeAtomo[i] < 'A' || nomeAtomo[i] > 'Z')
      return 0;
 }
 return 1;
}

/* Adiciona vertice com o nome da molecula no grafo*/
void adiciona_moleculas (FILE *arquivo, grafo G, int numVertices) {

  if (!arquivo) {
    fprintf (stderr, "Erro ao ler arquivo.\n");
    return;
  }

  char linha[1024];
  char *nomeAtomo;  

  for (int i = 1; i <= numVertices; i++) {
    fgets(linha, sizeof(linha), arquivo);                               /*Le a linha do arquivo*/   
    nomeAtomo = separa (linha, ' ');                                    /*Separa as informações*/
    while (nomeAtomo) {                                           
      if (eh_atomo (nomeAtomo)) {                                       /*Confere se o dado é o nome do Atomo*/        
        adiciona_vertice(i, G, nomeAtomo);        
        break;
      }
      nomeAtomo = separa (nomeAtomo + strlen(nomeAtomo) + 1, ' ');      /*Continua lendo as informações da mesma linha*/
    }    
  }

}

/*Conecta 2 vertices conforme o tipo de ligação (simples/dupla/tripla)*/
void conecta_moleculas (FILE *arquivo, grafo G, int numArestas) {
  if (!arquivo) {
    fprintf (stderr, "Erro ao ler arquivo.\n");
    return;
  }
  char linha[1024];
  int vertice1, vertice2, tipoLigação, id = 1;
  
  for (int i = 1; i <= numArestas; i++) {
    int j = 0;
    fscanf (arquivo, "%d %d %d", &vertice1, &vertice2, &tipoLigação);       
    while (j < tipoLigação) {      
      adiciona_aresta(id++, vertice1, vertice2, G);
      j++;
    }    
    fgets (linha, sizeof(linha), arquivo);
  }

}

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
  int numVertices, numArestas;
  
  le_vertices_arestas (arquivo, &numVertices, &numArestas);
  adiciona_moleculas (arquivo, G, numVertices);
  conecta_moleculas (arquivo, G, numArestas);

  /*Limpa os dados na memória*/
  fclose (arquivo);
  imprime_grafo(G);
  destroi_grafo(G);
  
  return 0;
}
