/*****************************************************************/
/*   Grafo c/ matriz de adjacencias | ESDA | LEEC | 2021/22      */      
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

/* cria grafo com n vertices */
grafo* grafo_novo(int n)
{
    int v;
    grafo* g;
    
    g = (grafo*)malloc(sizeof(grafo));
    g->tamanho = n;

    /* cria array de listas de adjacencias */
    g->adjacencias = (int**)malloc(n * sizeof(int*));
    for(v=0; v<n; v++)
    {
        g->adjacencias[v] = (int*)calloc(n, sizeof(int));
    }

    return g;
}

/* apaga grafo e liberta memoria */
void grafo_apaga(grafo* g)
{
    if(g == NULL)
        return;

    if(g->adjacencias != NULL)
    {
        int v;
        for (v = 0; v < g->tamanho; v++)
            free(g->adjacencias[v]);
        free(g->adjacencias);
    }
    free(g);
}


/* adiciona no grafo g uma aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta ja existir e 1 se foi adicionada */
int grafo_adiciona(grafo *g, int origem, int dest)
{
    if(g == NULL || origem > g->tamanho || dest > g->tamanho)
        return -1;

    if(g->adjacencias[origem][dest] == 1)
        return 0;

    g->adjacencias[origem][dest] = 1;
    return 1;
}


/* remove do grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se foi removida */
int grafo_remove(grafo *g, int origem, int dest)
{
    if(g == NULL || origem > g->tamanho || dest > g->tamanho)
        return -1;
    
    if(g->adjacencias[origem][dest] == 0)
      return 0;

    g->adjacencias[origem][dest] = 0; 
    return 1;
}

/* testa no grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se existir */
int grafo_aresta(grafo *g, int origem, int dest)
{
     if(g == NULL || origem > g->tamanho || dest > g->tamanho)
        return -1;

    if(g->adjacencias[origem][dest] == 1)
        return 1;
    return 0;
}

/* cria um novo grafo com base numa lista de adjacencias
   parametro adjacencies e' um array de inteiros, representado
   um numero n_edges de arestas.
   retorna um apontador para o grafo criado */
grafo* grafo_deLista(int* adjacencias, int n_arestas)
{
    if(adjacencias == NULL)
        return NULL;
    
    grafo *novo = grafo_novo(n_arestas);
    for(int i = 0; i<2*n_arestas; i+=2)
    {
        if(grafo_adiciona(novo, adjacencias[i], adjacencias[i+1]) == -1)
        {
            grafo_apaga(novo);
            return NULL;
        }
    }
    return novo;

}

/* cria e retorna um vetor de inteiros contendo os vertices
   de destino de todas as arestas com origem em i */
vetor* grafo_arestasSaida(grafo* g, int i)
{
    if(g == NULL)
        return NULL;
    
    vetor *novo = vetor_novo(); 
    if(novo == NULL) 
        return NULL;
    
    for(int j = 0; j<g->tamanho; j++)
    {
        if(g->adjacencias[i][j] != 0)
            if(vetor_insere(novo, j,-1) == -1)
                return NULL;
    }
    return novo;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de origem de todas as arestas com destino a i */
vetor* grafo_arestasEntrada(grafo* g, int i)
{
    if(g == NULL)
        return NULL;
    
    vetor *novo = vetor_novo(); 
    if(novo == NULL) 
        return NULL;
    
    for(int j = 0; j<g->tamanho; j++)
    {
        if(g->adjacencias[j][i] != 0)
            if(vetor_insere(novo, j,-1) == -1)
                return NULL;
    }
    return novo;
}

/* verifica se o grafo g e' completo
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o grafo for completo e 0 se nao o for */
int grafo_completo(grafo* g)
{
    if(g == NULL)
        return -1;
    int i, j;

    for(i = 0; i<g->tamanho; i++)
        for(j = 0; j<g->tamanho; j++)
        {
            if(g->adjacencias[i][j] == 0 && i != j && g->adjacencias[j][i] == 0)
                return 0;
        }
    return 1;
}

/* imprime as adjacencias do grafo */
void grafo_imprime(grafo* g)
{
    int i, j;

    if (g == NULL)
        return;

    for (i = 0; i < g->tamanho; i++)
    {
        printf("%d: ", i);
        for(j = 0; j < g->tamanho; j++)
        {
            if(g->adjacencias[i][j] != 0)
                printf("%d ",j);
        }
        printf("\n");
    }
}

