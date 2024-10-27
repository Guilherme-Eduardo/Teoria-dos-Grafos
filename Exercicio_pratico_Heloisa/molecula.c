#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "lista.h"


// Retorno a posição do primeiro espaço encontrado em Linha.
char *separa (char *linha, char delimitador) {

    char *pos_del;

    if (!linha || !strlen (linha))
        return NULL;
    
    pos_del = strchr (linha, delimitador);

    if (!pos_del) {
        if (strlen (linha))
            return linha;
        return NULL;
    }

    pos_del[0] = 0;

    return pos_del;
}


void vertice_aresta (FILE *arq, int *v, int *a) {

    char buffer[1024], *linha, *pos_del;

    // Ignora as três primeiras linhas do arquivo
    for (int i = 0; i < 4; i++) {
        fscanf (arq, "%[^\n]", buffer);
        fgetc (arq);
    }

    // Pega a linha que contém o número de vértice e arestas 
    fscanf (arq, "%[\n]", buffer);
    fgetc (arq);
    linha = buffer;

    //Retira o primeiro espaço
    pos_del = separa (linha, ' ');

    // Pega o número de vértices
    linha = pos_del + 1;
    pos_del = separa (linha, ' ');
    *v = atoi (linha);

    // Pega o número de arestas
    linha = pos_del + 1;
    pos_del = separa (linha, ' ');
    *a = atoi (linha);
}


void adiciona_atomos (FILE *arq, grafo G, int v) {

    char buffer[1024], *linha, *pos_del;

    if (!arq){
        printf ("ERRO\n");
        return;
    }

    for (int i = 1; i <= v; i++) {
        fgets (buffer, sizeof (buffer), arq);
        fscanf (arq, "%[\n]", buffer);
        fgetc (arq);
        //printf ("%s", buffer);
        linha = buffer;
        for (int i = 0; i < 3; i++) {
            pos_del = separa (linha, '.');
            linha = pos_del + 1;
        }
        pos_del = separa (linha, ' ');
        linha = pos_del + 1;
        pos_del = separa (linha, ' ');
        adiciona_vertice (i, linha, G);
    }
}

void adiciona_ligacoes (FILE *arq, grafo G, int a) {

    char buffer[1024], *linha, *pos_del;
    int dados[3], k = 1;

    if (!arq || !G || !a) 
        return;

    for (int i = 0; i < a; i++) {
        fgets (buffer, sizeof (buffer), arq);
        fscanf (arq, "%[\n]", buffer);
        fgetc (arq);
        linha = buffer;
        for (int j = 0; j < 3; j++) {
            pos_del = separa (linha, ' ');
            dados[j] = atoi(linha);
            while (!dados[j]) {
                linha = pos_del + 1;
                pos_del = separa (linha, ' ');
                dados[j] = atoi(linha);
            }
            linha = pos_del + 1;
        }            
        //printf ("%d %d %d\n", dados[0], dados[1], dados[2]);
        while (dados[2]) {
            adiciona_aresta (k, dados[0], dados[1], G);
            dados[2]--;
            k++;
        }
    }
}


int main (int argc, char **argv) {

    FILE *mol;
    grafo G;
    int v, a;
    char buffer[1024], *linha, *pos_del;
    
    //Verifica entrada
    if (argc != 2)
        return 0;
    
    //Abre arquivo  
    mol = fopen (argv[1], "r");
    if (!mol)
        return 0;

    G = cria_grafo();

    vertice_aresta(mol, &v, &a);
    printf ("Vertices = %d      Arestas = %d\n", v, a);

    adiciona_atomos(mol, G, v);
    adiciona_ligacoes (mol, G, a);

    fclose(mol);

    imprime_grafo (G);
    destroi_grafo (G);

    return 0;
}