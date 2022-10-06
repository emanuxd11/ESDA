#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#define RAIZ 1

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
heap *max_heap(heap *h)
{
    /*** Responder a 1.1 aqui ***/
    return NULL;
}

/*** problema 1.2 ***/
/*

Algoritmo:
ESCREVA AQUI A SUA RESPOSTA

Complexidade temporal (pior caso):
ESCREVA AQUI A SUA RESPOSTA

*/

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
    printf("\nProblema 1.1\n");
    char strs[6][2] = {"D", "B", "C", "E", "A", "F"};
    heap *min_h = heap_nova(6);
    for (int i = 0; i < 6; i++)
        heap_insere(min_h, strs[i], strs[i][0]);
    heap *max_h = max_heap(min_h);

    printf("Sequencia de elementos removidos da heap original (min-heap):\n");
    while (min_h->tamanho > 0)
    {
        char *str = heap_remove(min_h);
        printf("%s ", str);
        free(str);
    }
    printf("\n");

    if (max_h != NULL)
    {
        printf("Sequencia de elementos removidos da heap retornada (max-heap):\n");
        while (max_h->tamanho > 0)
        {
            char *str = heap_remove(max_h);
            printf("%s ", str);
            free(str);
        }
        printf("\n\n");
    }
    else
        printf("Erro: heap retornada e' NULL.\n\n");

    heap_apaga(min_h);
    heap_apaga(max_h);
    return 0;
}