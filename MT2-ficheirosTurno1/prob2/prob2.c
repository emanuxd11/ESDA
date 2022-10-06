#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define N_VERTICES 5

float mediaDeArestasPorVertice(grafo *g)
{ 
    if(g == NULL) return -1;
    
    int n_arestas = 0;
    for(unsigned int i = 0; i < g->tamanho; i++) {
        n_arestas += g->adjacencias[i].tamanho;
        /*for(lista_no *no = g->adjacencias[i].inicio; no != NULL; no = no->proximo) {
        }*/
    }

    return (float)n_arestas/(g->tamanho);
}

grafo *complementar(grafo *g)
{
    if(g == NULL) return NULL;

    grafo *g_comp = grafo_novo(g->tamanho, DIGRAFO);
    if(g_comp == NULL) return NULL;

    for(unsigned int i = 0; i < g->tamanho; i++) {
        for(unsigned int j = 0; j < g->tamanho; j++) {
            if(j == i) continue;

            if(!grafo_aresta(g, i, j)) {
                grafo_adiciona(g_comp, i, j);
            }
        }
    }

    return g_comp;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
    grafo *gf = grafo_novo(N_VERTICES, DIGRAFO);
    grafo *comp;

    grafo_adiciona(gf, 0, 4);
    grafo_adiciona(gf, 0, 1);
    grafo_adiciona(gf, 1, 3);
    grafo_adiciona(gf, 3, 4);
    grafo_adiciona(gf, 3, 1);
    grafo_adiciona(gf, 3, 0);
    grafo_adiciona(gf, 4, 3);
    grafo_adiciona(gf, 4, 0);

    printf("Grafo original para teste:\n");
    grafo_imprime(gf);

    // Pergunta 2.1
    printf("\n\nAlinea 2.1\n");
    printf("Media de arestas por vertice: %.2f\n", mediaDeArestasPorVertice(gf));


    // Pergunta 2.2
    printf("\n\nAlinea 2.2\n");
    printf("Grafo complementar:\n");

    comp = complementar(gf);

    if (comp == NULL)
        printf("NULL\n\n");
    else
        grafo_imprime(comp);

    grafo_apaga(gf);
    grafo_apaga(comp);

    return 0;
}
