#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
int *junta_colecoes(int *cromos1, int n1, int *cromos2, int n2, int *tam) {
	/*** Responder ao 1.1 aqui ***/

	//Alocar memória para n1 elementos num vetor de retorno "ret"
	int i, j;
	int *ret = (int*)malloc(sizeof(int));
	
	//Copiar os valores de "cromos1" para "ret" sem repetições
	for(i = 0; i < n1; i++) {
		for(j = 0; j < *tam; j++) {
			if(ret[j] == cromos1[i]) {
				break;
			}
		}
		if(j == *tam) {
			ret = (int*)realloc(ret, (*tam+1) * sizeof(int));
			ret[*tam] = cromos1[i];
			(*tam)++;
		}
	}

	//Copiar os valores de "cromos2" para "ret" sem repetições
	for(i = 0; i < n2; i++) {
		for(j = 0; j < *tam; j++) {
			if(ret[j] == cromos2[i]) {
				break;
			}
		}
		if(j == *tam) {
			ret = (int*)realloc(ret, (*tam+1) * sizeof(int));
			ret[*tam] = cromos2[i];
			(*tam)++;
		}
	}

	return ret;
}

/*** problema 1.2 ***/

void juntar_repetidos(pilha *cromos, int *acrescentar, int ac) {
	/*** Responder ao 1.2 aqui ***/

	int i, j, cont;
	pilha *aux = pilha_nova();

	for(i = 0; i < ac; i++) {
		cont = 0;
		//tamanho tem que ser maior que 1, se não, as comparações causam segmentation fault
		while(acrescentar[i] != pilha_top(cromos)->elemento && pilha_tamanho(cromos) > 0) {
			pilha_push(aux, pilha_top(cromos)->elemento);
			pilha_pop(cromos);
			cont++;
		}
		
		if(acrescentar[i] == pilha_top(cromos)->elemento) {
			pilha_push(cromos, acrescentar[i]);
		}

		for(j = 0; j < cont; j++) {
			pilha_push(cromos, pilha_top(aux)->elemento);
			pilha_pop(aux);
		}
	}

	pilha_apaga(aux);
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{

	/* testes */
	int colecao1[] = {2, 4, 5, 6, 5, 4, 10, 11, 10, 10};
	int colecao2[] = {3, 4, 6, 9, 12};
	int tam1 = 10, tam2 = 5;
	int total = 0;
	int *ve;

	/* inicio teste prob1.1 */
	ve = junta_colecoes(colecao1, tam1, colecao2, tam2, &total);
	if (ve)
	{
		if (total == 9)
			printf("\nNúmero de cromos na nova coleção: 9 (Certo)\n");
		else
			printf("\nNúmero de cromos na nova coleção : %d (errado, tem que dar 9)\n", total);
		printf("Lista da nova coleção: [");
		for (int i = 0; i < (total - 1); i++)
			printf("%d,", ve[i]);
		printf("%d]\n", ve[total - 1]);
		free(ve);
	}
	else
		printf("\njunta_colecoes retornou NULL\n");
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	pilha *cro = pilha_nova();
	if (cro == NULL)
	{
		printf("\nSem espaço de memoria\n");
		return 0;
	}

	pilha_push(cro, 24);
	pilha_push(cro, 5);
	pilha_push(cro, 35);
	pilha_push(cro, 11);
	pilha_push(cro, 6);
	pilha_push(cro, 2);
	int repetidos[] = {5, 34, 24};
	int nr = 3;
	pilhaItem *item;

	juntar_repetidos(cro, repetidos, nr);

	if (pilha_tamanho(cro) == 8)
	{
		item = cro->raiz->proximo->proximo->proximo->proximo;
		if (item->elemento != 5 || item->proximo->elemento != 5)
		{
			printf("\nO cromo numero 5 não foi inserido no local correto\n");
		}
		else
		{
			item = item->proximo->proximo;
			if (item->elemento != 24 || item->proximo->elemento != 24)
			{
				printf("\nO cromo numero 24 não foi inserido no local correto\n");
			}
			else
			{
				printf("\nOs cromos foram inseridos nos locais corretos\n");
			}
		}
	}
	else
		printf("\npilha com tamanho errado (tamanho: %d; esperado: 8)\n", pilha_tamanho(cro));
	printf("Cromos: [");
	item = cro->raiz;
	for (int i = 0; i < pilha_tamanho(cro) - 1; i++)
	{
		printf("%d,", item->elemento);
		item = item->proximo;
	}
	printf("%d]\n", item->elemento);
	pilha_apaga(cro);
	/* fim teste prob1.2 */

	return 0;
}
