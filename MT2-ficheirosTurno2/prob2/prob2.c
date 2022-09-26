#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

#define N_VERTICES 5

int numeroDeArestas(grafo *g, int verticeId)
{
	if(g == NULL || verticeId < 0) return -1;
	
	int ret = g->adjacencias[verticeId].tamanho;

	for(unsigned int i = 0; i < g->tamanho; i++) {
		if(i == verticeId) continue;

		if(grafo_aresta(g, i, verticeId)) {
			ret++;
		}
	}

	return ret;
}

grafo *uniao(grafo *g1, grafo *g2)
{
	if(g1 == NULL || g2 == NULL) return NULL;

	grafo *g3 = grafo_novo(N_VERTICES, DIGRAFO);

	/*for(unsigned int i = 0; i < N_VERTICES; i++) {
		for(unsigned int j = 0; j < N_VERTICES; j++) {
			if(i == j) continue;

			if(grafo_aresta(g1, i, j) || grafo_aresta(g2, i, j)) {
				grafo_adiciona(g3, i, j);
			}
		}
	}*/

	//Maneira alternativa, usando nó auxiliar. Deste modo obtém-se
	//idêntico ao pretendido no enunciado, ao contrário do método
	//acima, cujo resultado é correto, porém não idêntico ao previsto.
	lista_no *no_aux;

	//Adicionar primeiro as adjacências do grafo 1.
	for(unsigned int i = 0; i < g1->tamanho; i++) {
		no_aux = g1->adjacencias[i].inicio;
		
		for(unsigned int j = 0; j < g1->adjacencias[i].tamanho; j++) {
			grafo_adiciona(g3, i, no_aux->vertice);
			no_aux = no_aux->proximo;
		}
	}

	//Repetir o processo para as adjacências do grafo 2.
	for(unsigned int i = 0; i < g1->tamanho; i++) {
		no_aux = g2->adjacencias[i].inicio;
		
		for(unsigned int j = 0; j < g2->adjacencias[i].tamanho; j++) {
			grafo_adiciona(g3, i, no_aux->vertice);
			no_aux = no_aux->proximo;
		}
	}

	return g3;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
	grafo *g1 = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *g2 = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *g3 = grafo_novo(N_VERTICES, DIGRAFO);
	grafo *gproposto = NULL;

	// Grafo gf (uniao de g1 e g2)
	grafo_adiciona(g3, 0, 4);
	grafo_adiciona(g3, 0, 1);
	grafo_adiciona(g3, 1, 3);
	grafo_adiciona(g3, 3, 4);
	grafo_adiciona(g3, 3, 1);
	grafo_adiciona(g3, 3, 0);
	grafo_adiciona(g3, 4, 3);
	grafo_adiciona(g3, 4, 0);

	// Grafo 1
	grafo_adiciona(g1, 3, 0);
	grafo_adiciona(g1, 3, 1);
	grafo_adiciona(g1, 4, 0);
	grafo_adiciona(g1, 4, 3);

	// Grafo 2
	grafo_adiciona(g2, 0, 4);
	grafo_adiciona(g2, 0, 1);
	grafo_adiciona(g2, 1, 3);
	grafo_adiciona(g2, 3, 4);

	
	printf("Grafo 3:\n");
	grafo_imprime(g3);

	// Pergunta 2.1
	printf("\n\nAlinea 2.1\n");
	printf("Numero de arestas do no 3: %d\n", numeroDeArestas(g3, 3));
	printf("Numero de arestas do no 2: %d\n", numeroDeArestas(g3, 2));
	printf("Numero de arestas do no 4: %d\n", numeroDeArestas(g3, 4));

	
	// Pergunta 2.2
	printf("\n\n\nAlinea 2.2\n");
	printf("==========================\n");
	printf("Grafo 1:\n");
	grafo_imprime(g1);
	printf("==========================\n");
	printf("Grafo 2:\n");
	grafo_imprime(g2);
	printf("==========================\n");
	printf("Grafo UNIAO:\n");
	gproposto = uniao(g1, g2);
	if (gproposto == NULL)
	  printf("NULL\n");
	else
	  grafo_imprime(gproposto);
	printf("==========================\n");

	grafo_apaga(g1);
	grafo_apaga(g2);
	grafo_apaga(g3);
	grafo_apaga(gproposto);

	return 0;
}
