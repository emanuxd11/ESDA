#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"

#define N_VERTICES 5

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

//2.1  Calcula o numero de vertices com dupla ligacao a outro vertice
int contaVerticesComDuplaLigacao(grafo *g)
{
	/*** Responder a 2.1 aqui ***/
	return -1;
}

//2.2  Verifica se g1 e subgrafo de g2
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
	grafo *gf = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *gf2 = grafo_novo(N_VERTICES, DIGRAFO);
	int nVertices;
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

	/****************************************************/
	// Pergunta 2.1
	printf("Problema 2.1\n");
	nVertices = contaVerticesComDuplaLigacao(gf);
	if (nVertices == -1)
	  printf("ERRO!\n");
	else
	  printf("Grafo 1 tem %d vertices duplamente ligados\n", nVertices);

	nVertices = contaVerticesComDuplaLigacao(gf2);
	if (nVertices == -1)
	  printf("ERRO!\n");
	else
	  printf("Grafo 2 tem %d vertices duplamente ligados\n", nVertices);
	/****************************************************/

	// Pergunta 2.2
	printf("==========================\n");
	printf("Problema 2.2\n");
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

	/****************************************************/

	//  liberta espaco usado
	grafo_apaga(gf);
	grafo_apaga(gf2);

	return 0;
}
