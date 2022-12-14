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
    /* alinea 1.1 */
    if(g == NULL || origem < 0 || dest < 0 || origem > g->tamanho || dest > g->tamanho) return -1;

    if(g->adjacencias[origem][dest] == 1) return 0;

    g->adjacencias[origem][dest] = 1;

    return 1;
}

/* remove do grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se foi removida */
int grafo_remove(grafo *g, int origem, int dest)
{
    /* alinea 1.1 */
    if(g == NULL || origem < 0 || dest < 0 || origem > g->tamanho || dest > g->tamanho) return -1;

    if(g->adjacencias[origem][dest] == 0) return 0;

    g->adjacencias[origem][dest] = 0;

    return 1;
}

/* testa no grafo g a aresta entre os vertices origem e destino
   retorna -1 em caso de erro (parametros invalidos)
   retorna 0 se a aresta nao existir e 1 se existir */
int grafo_aresta(grafo *g, int origem, int dest)
{
    /* alinea 1.1 */
    if(g == NULL || origem < 0 || dest < 0 || origem > g->tamanho || dest > g->tamanho) return -1;

    if(g->adjacencias[origem][dest] == 0) return 0;
    return 1;
}

/* cria um novo grafo com base numa lista de adjacencias
   parametro adjacencias e' um array de inteiros, representado
   um numero n_edges de arestas.
   retorna um apontador para o grafo criado */
grafo* grafo_deLista(int* adjacencias, int n_arestas)
{
    /* alinea 1.2 */
    if(adjacencias == NULL) return NULL;

    grafo *ret = grafo_novo(n_arestas);
    
    for(int i = 0; i < 2*n_arestas; i += 2) {
        if(grafo_adiciona(ret, adjacencias[i], adjacencias[i+1]) == -1) {
            grafo_apaga(ret);
            return NULL;
        }
    }

    return ret;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de destino de todas as arestas com origem em i */
vetor* grafo_arestasSaida(grafo* g, int i)
{
    /* alinea 1.3 */
    if(g == NULL) return NULL;
    if(i < 0 || i > g->tamanho) return NULL;

    vetor *vet = vetor_novo();

    int cont = 0;
    for(int j = 0; j < g->tamanho; j++) {
        if(grafo_aresta(g, i, j)) {
            vetor_insere(vet, j, cont++);
        }
    }

    if(cont == 0) {
        vetor_apaga(vet); 
        return NULL;
    }

    return vet;
}

/* cria e retorna um vetor de inteiros contendo os vertices
   de origem de todas as arestas com destino a i */
vetor* grafo_arestasEntrada(grafo* g, int i)
{
    /* alinea 1.3 */
    if(g == NULL) return NULL;
    if(i < 0 || i > g->tamanho) return NULL;

    vetor *vet = vetor_novo();

    int cont = 0;
    for(int j = 0; j < g->tamanho; j++) {
        if(grafo_aresta(g, j, i)) {
            vetor_insere(vet, j, cont++);
        }
    }

    if(cont == 0) {
        vetor_apaga(vet); 
        return NULL;
    }

    return vet;
}

/* verifica se o grafo g e' completo
   retorna -1 em caso de erro (parametros invalidos)
   retorna 1 se o grafo for completo e 0 se nao o for */
int grafo_completo(grafo* g)
{
    /* alinea 1.4 */
    if(g == NULL) return -1;

    for(int i = 0; i < g->tamanho; i++) {
        for(int j = 0; j < g->tamanho; j++) {
            if(!grafo_aresta(g, i, j)) return 0;
        }
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
                printf("%d ", j);
        }
        printf("\n");
    }
}

