#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "avl.h"

/*** problema 3 ***/
arvore_avl* sugestao_amizade(grafo *g, int u)
{
	if(g == NULL) return NULL;
	if(u < 0 || u > g->tamanho) return NULL;

	arvore_avl *ret = avl_nova();
	if(ret == NULL) return NULL;

	int tam_amigos = 0, tam_amigos_amigos;
	int *vet_amigos = grafo_adjacentes(g, u, &tam_amigos);
	int *vet_amigos_amigos;
	
	for(int i = 0; i < tam_amigos; i++) {
		vet_amigos_amigos = grafo_adjacentes(g, vet_amigos[i], &tam_amigos_amigos);
		
		for(int j = 0; j < tam_amigos_amigos; j++) {
			if(!grafo_aresta(g, u, vet_amigos_amigos[j]) && vet_amigos_amigos[j] != u) {
				avl_insere(ret, vet_amigos_amigos[j]);
			}
		}
		
		free(vet_amigos_amigos);
	}

	free(vet_amigos);
	return ret;
}


/********************************************************************/
/********************************************************************/
grafo* init_rede()
{
	grafo* g = grafo_novo(10,NAODIRECIONADO);
	if (!g)
		return NULL;
	grafo_adiciona(g,1,2);
	grafo_adiciona(g,1,3);
	grafo_adiciona(g,2,3);
	grafo_adiciona(g,2,4);
	grafo_adiciona(g,2,5);
	grafo_adiciona(g,3,5);
	grafo_adiciona(g,3,6);
	grafo_adiciona(g,3,7);
	grafo_adiciona(g,7,6);
	return g;
}

	
int main ()
{
	puts("* Problema 3 *");

	grafo *rede = init_rede();
	arvore_avl *sugestoes =NULL;
	
	sugestoes = sugestao_amizade(rede,2);
	if (sugestoes==NULL)
		printf("\nUtilizador '2' ou rede nao existe\n");
	else{
		printf("\nSugestoes de amizade para '2': ");
		avl_imprime(sugestoes);
		avl_apaga(sugestoes);
	}

	sugestoes = sugestao_amizade(rede,12);
	if (sugestoes==NULL)
		printf("\nUtilizador '12' ou rede nao existe\n");
	else{
		printf("\nSugestoes de amizade para '9': ");
		avl_imprime(sugestoes);
		avl_apaga(sugestoes);
	}

	grafo_apaga(rede);
	return 1;
}
