#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vetor.h"
#include "heap.h"

/*** problema 2 ***/
vetor* heap_ordena(vetor *v)
{
	if(v == NULL) return NULL;
	
	int prioridade;
	char *string;
	heap *aux = heap_nova(v->tamanho);
	if(aux == NULL) return NULL;

	vetor *ret = vetor_novo();
	if(ret == NULL) return NULL;

	for(int i = 0; i < v->tamanho; i++) {
		string = v->elementos[i].str;
		prioridade = (string[0] << 8) + string[1]; 

		//por ser min-heap, inserimos com o simétrico da prioridade
		if(!heap_insere(aux, string, -prioridade)) {
			heap_apaga(aux);
			return NULL;
		}
	}

	while(aux->tamanho > 0) {
		vetor_insere(ret, heap_remove(aux), -1);
	}

	heap_apaga(aux);

	return ret;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_LINE	100

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);

	int i, j;
	char cidade[MAX_LINE];
	vetor *v, *res;
	FILE *fp;

	puts("* Problema 2 *");
	v = vetor_novo();
	fp=fopen("cidades.txt", "r");
	while(fgets(cidade, MAX_LINE, fp) != NULL)
	{
		*strchr(cidade, ',') = '\0';
		vetor_insere(v,cidade,v->tamanho);
	}
	res=heap_ordena(v);
	if(res != NULL)
	{
		for(i=0; i<3 && i<vetor_tamanho(res); i++)
			printf("%s\n", vetor_elemento(res,i));
		if(vetor_tamanho(res) > 3)
		{
			if(vetor_tamanho(res) > 6)
				puts("...");
			j = i;
			if(vetor_tamanho(res)-3 > j)
				j = vetor_tamanho(res)-3;
			for (i=j; i<vetor_tamanho(res); i++)
				printf("%s\n", vetor_elemento(res,i));
		}
	}
	vetor_apaga(v);
	vetor_apaga(res);

	return 0;
}
