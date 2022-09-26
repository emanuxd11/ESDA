/*****************************************************************/
/*          Biblioteca vetor | ESDA | LEEC | 2021/22             */
/*****************************************************************/

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

vetor* vetor_novo() {
	vetor *ret = (vetor*)malloc(sizeof(vetor));
	ret->elementos = (v_elemento*)malloc(sizeof(v_elemento));
	ret->capacidade = 1;
	ret->tamanho = 0;

	return ret;
}

void vetor_apaga(vetor* vec)
{
	int i;

	if(vec == NULL)
	return;

	/* liberta memoria de cada string */
	for (i = 0; i < vec->tamanho; i++)
	{
		free(vec->elementos[i].str);
	}

	/* liberta memoria dos apontares para as strings */
	free(vec->elementos);

	/* liberta memoria da estrutura vetor */
	free(vec);
}

const char* vetor_elemento(vetor* vec, int indice)
{
	if (vec == NULL || indice < 0 || indice >= vec->tamanho)
	return NULL; 

	return vec->elementos[indice].str;
}

int vetor_insere(vetor* vec, const char* valor, int pos)
{
	int i;
	if(vec == NULL || pos < -1 || pos > vec->tamanho)
		return -1;

	/* aumenta elementos do vetor se capacidade nao for suficiente */
	if(vec->tamanho == vec->capacidade)
	{
		if(vec->capacidade == 0)
			vec->capacidade = 1;
		else
			vec->capacidade *= 2;

		vec->elementos = (v_elemento*)realloc(vec->elementos, vec->capacidade * sizeof(v_elemento));
		if(vec->elementos == NULL)
		return -1;
	}

	/* se pos=-1 insere no fim do vetor */
	if(pos == -1){
		pos = vec->tamanho;
	}

	/* copia todos os elementos a partir da posicao pos ate' ao fim do vetor para pos+1 */
	for(i=vec->tamanho-1; i>=pos; i--)
	{
		vec->elementos[i+1] = vec->elementos[i];
	}

	/* aloca espaco para a nova string na posicao pos */
	vec->elementos[pos].str = (char*)calloc(strlen(valor)+1, sizeof(char));
	if(vec->elementos[pos].str == NULL)
	return -1;

	/* copia valor */
	strcpy(vec->elementos[pos].str, valor);
	//printf("Inserido na pos %d: %s\n", pos, vec->elementos[vec->tamanho].str);

	vec->tamanho++;
	//printf("tamanho atualizado do vetor: %d ", vec->tamanho);

	return pos;
}

int vetor_imprime(vetor *vec){
	if (vec == NULL){
		printf("Erro a imprimir, o vetor nao existe\n");
		return -1;
	}
	printf("tamanho do vetor: %d\n", vec->tamanho);
	printf("Vetor: [ ");
    for(int i = 0; i < vec->tamanho; i++){
		printf("%s, ", vetor_elemento(vec, i));
	}
    printf("]\n");
	return 0;
}