/*****************************************************************/
/*          Biblioteca vetor | PROG2 | MIEEC | 2018/19          */
/*****************************************************************/

#include "vetor.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

vetor* vetor_novo()
{
	vetor* vec;

	/* aloca memoria para a estrutura vetor */
	vec = (vetor*)malloc(sizeof(vetor));
	if(vec == NULL)
		return NULL;

	vec->tamanho = 0;
	vec->capacidade = 0;
	vec->elementos = NULL;

	return vec;
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

int vetor_atribui(vetor* vec, int pos, const char* valor)
{
	unsigned int len_valor;

	if (vec == NULL || pos < 0 || pos >= vec->tamanho)
	return -1;

	len_valor = strlen(valor);

	/* reserva mais espaco se necessario */
	if(len_valor > strlen(vec->elementos[pos].str))
	{
		vec->elementos[pos].str = (char*)realloc(vec->elementos[pos].str, (len_valor+1)*sizeof(char));
		if(vec->elementos[pos].str == NULL)
		return -1;
	}

	/* copia valor */
	strcpy(vec->elementos[pos].str, valor);

	return pos;
}

int vetor_tamanho(vetor* vec)
{
	if(vec == NULL)
	return -1;

	return vec->tamanho;
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
	if(pos == -1)
		pos = vec->tamanho;

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

	vec->tamanho++;

	return pos;
}

int vetor_remove(vetor* vec, int pos)
{
	int i;

	if(vec == NULL || pos < 0 || pos >= vec->tamanho)
	return -1;

	/* liberta string na posicao a remover */
	free(vec->elementos[pos].str);

	/* copia todos os elementos a partir da posicao pos+1 ate' ao fim do vetor para pos */
	for(i=pos+1; i<vec->tamanho; i++)
	{
		vec->elementos[i-1] = vec->elementos[i];
	}

	vec->tamanho--;

	return 0;
}

int vetor_pesquisa(vetor* vec, const char* valor)
{
	int i;

	if(vec == NULL)
	return -1;

	/* pesquisa sequencial */
	for (i = 0; i < vec->tamanho; i++)
	{
		if (strcmp(vec->elementos[i].str, valor) == 0)
		return i;
	}

	return -1;
}

int vetor_ordena(vetor* vec)
{
	int i, j;
	char *tmp;

	if(vec == NULL)
	return -1;

	/* ordenacao por insercao */
	for (i = 1; i < vec->tamanho; i++)
	{
		tmp = vec->elementos[i].str;
		for (j = i; j > 0 && strcmp(tmp, vec->elementos[j-1].str) < 0; j--)
		{
			vec->elementos[j] = vec->elementos[j-1];
		}
		vec->elementos[j].str = tmp;
	}

	return 0;
}

vetor* vetor_concatena(vetor *vec1, vetor *vec2) {
	if(vec1==NULL || vec2==NULL) {
		printf("\nErro fatal!\n");
		return NULL;
	}
	int i, j;
	vetor *res=vetor_novo();

	for(i=0; i<vetor_tamanho(vec1); i++) {
		vetor_insere(res, vec1->elementos[i].str, i);
	}
	for(j=0; i< vec1->tamanho+vetor_tamanho(vec2); i++, j++) {
		vetor_insere(res, vec2->elementos[j].str, i);
	}
	
	return res;
}

int vetor_swap(vetor *vec, int pos1, int pos2) {
	if(vec==NULL) return -1;

	char temp[1024];

	strcpy(temp, vetor_elemento(vec, pos1));
	vetor_atribui(vec, pos1, vetor_elemento(vec, pos2));
	vetor_atribui(vec, pos2, temp);

	return 0;
}

int vetor_inverte(vetor *vec) {
	if(vec==NULL) return -1;
	
	int i, tam=vec->tamanho, j;

	for(i=0; i<j; i++) {
		j=tam-1-i;
		vetor_swap(vec, i, j);
	}

	return 0;
}

vetor* vetor_baralha(vetor *vec) {
	if(vec==NULL) {
		printf("\nErro fatal!\n");
		return NULL;
	}

	srand(time(NULL));
	
	int i, randpos, *posOcupadas=calloc(vetor_tamanho(vec), sizeof(int));
	vetor *res=vetor_novo();
	
	for(i=0; i<vetor_tamanho(vec); i++) {
		do {
            randpos=rand()%vetor_tamanho(vec);
		} while(posOcupadas[randpos]);
        posOcupadas[randpos]=1;
		vetor_insere(res, vetor_elemento(vec, randpos), i);
		printf("%d\n", i);
		printf("%d\n", randpos);
	}

	return res;
}
