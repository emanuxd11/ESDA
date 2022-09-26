#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "grafo.h"
#define RAIZ 1
#define N_VERTICES 5

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
heap *max_heap(heap *h)
{
    /*** Responder a 2.1 aqui ***/
    return NULL;
}

/*** problema 2.2 ***/
int subgrafo(grafo *g1, grafo *g2)
{
	/*** Responder a 2.2 aqui ***/
	return -1;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
    /****************************************************/
    printf("\nProblema 2.1\n");
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

    /****************************************************/
    printf("\nProblema 2.2\n");
    grafo *gf = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *gf2 = grafo_novo(N_VERTICES, DIGRAFO);
	int eSubgrafo;
	  
	/******** Grafo 1 *********/
	
	grafo_adiciona(gf, 0, 2);
	grafo_adiciona(gf, 0, 3);
	
	grafo_adiciona(gf, 1, 2);
	grafo_adiciona(gf, 1, 4);

	grafo_adiciona(gf, 2, 1);
	grafo_adiciona(gf, 2, 4);

	grafo_adiciona(gf, 3, 2);

	grafo_adiciona(gf, 4, 1);
	grafo_adiciona(gf, 4, 2);

	printf("Grafo 1 para teste:\n");
	grafo_imprime(gf);
	printf("==========================\n");

	/******** Grafo 2 *********/

	grafo_adiciona(gf2, 0, 2);
	grafo_adiciona(gf2, 0, 3);
	
	grafo_adiciona(gf2, 1, 0);
	grafo_adiciona(gf2, 1, 2);
	grafo_adiciona(gf2, 1, 4);
	
	grafo_adiciona(gf2, 2, 0);
	grafo_adiciona(gf2, 2, 1);
	grafo_adiciona(gf2, 2, 3);
	grafo_adiciona(gf2, 2, 4);

	grafo_adiciona(gf2, 3, 2);

	grafo_adiciona(gf2, 4, 1);
	grafo_adiciona(gf2, 4, 2);

	printf("Grafo 2 para teste:\n");
	grafo_imprime(gf2);
	printf("==========================\n");

	eSubgrafo = subgrafo(gf, gf2);
	if (eSubgrafo == 1)
	  printf("g1 E subgrafo de g2\n");
	else
	  if (eSubgrafo == 0)
	    printf("g1 NAO E subgrafo de g2\n");
	  else
	    printf("ERRO!\n");
	
	eSubgrafo = subgrafo(gf2, gf);
	if (eSubgrafo == 1)
	  printf("g1 E subgrafo de g2\n");
	else
	  if (eSubgrafo == 0)
	    printf("g1 NAO E subgrafo de g2\n");
	  else
	    printf("ERRO!\n");

	eSubgrafo = subgrafo(gf2, gf2);
	if (eSubgrafo == 1)
	  printf("g1 E subgrafo de g2\n");
	else
	  if (eSubgrafo == 0)
	    printf("g1 NAO E subgrafo de g2\n");
	  else
	    printf("ERRO!\n");

	//  liberta espaco usado
	grafo_apaga(gf);
	grafo_apaga(gf2);
    /****************************************************/
    return 0;
}