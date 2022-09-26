#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
int* cromos_em_falta(int *cromos, int n, int ntotal, int *tam)
{
	/*** Responder a 1.1 aqui ***/
	if(cromos == NULL || n <0 || ntotal < 0 || tam == NULL) return NULL;

	*tam = 0;

	int *ret = malloc(sizeof(int) * ntotal);
	if(ret == NULL) return NULL;

	for(int i = 1; i <= ntotal; i++) {
		int j;
		for(j = 0; j < n; j++) {
			if(i == cromos[j]) break;
		}

		if(j == n) {
			ret[*tam] = i;
			(*tam)++; 
		}	
	}
	
	if(*tam == 0) {
		free(ret);	
		return NULL;
	}

	ret = realloc(ret, sizeof(int) * (*tam));
	return ret;
}

/*** problema 1.2 ***/
void retirar_cromos_intervalo(pilha *cromos, int inicio, int fim)
{
	/*** Responder a 1.2 aqui ***/
	if(cromos == NULL || inicio < 0 || fim < 0 || inicio > fim) return;

	pilha *aux = pilha_nova();
	if(aux == NULL) return;


	while(cromos->tamanho > 0) {
		if(pilha_top(cromos)->elemento > fim || pilha_top(cromos)->elemento < inicio) {
			pilha_push(aux, pilha_top(cromos)->elemento);
		}

		pilha_pop(cromos);
	}

	while(aux->tamanho > 0) {
		pilha_push(cromos, pilha_top(aux)->elemento);
		pilha_pop(aux);
	}

	pilha_apaga(aux);
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{

	/* testes */
	int colecao1[] = {2,4,5,6,5,4,10,11,10,10,3,12,14,16,18};
	int falta[]={1,7,8,9,13,15,17,19,20};
	int tam1 = 15, ncolecao = 20, nfalta=9;
	int total = 0;
	int *ve;
	int flag=0;

	/****************************************************/
	/* inicio teste prob1.1 */
	printf("\nProblema 1.1\n");
	ve = cromos_em_falta(colecao1, tam1, ncolecao, &total);
	if (ve)
	{
		if (total == 9)
		{
			printf("\nNumero de cromos em falta: 9 (Certo)\n");
			for (int i=0;i<nfalta;i++)
			{
				if (falta[i]!=ve[i])
				flag=1;
			}
			if (flag==0)
			{
				printf("Lista correta dos cromos em falta: [");
				for (int i = 0; i < (total - 1); i++)
					printf("%d,", ve[i]);
				printf("%d]\n", ve[total - 1]);
			} else 
			{
				printf("Lista incorreta dos cromos em falta: [");
				for (int i = 0; i < (total - 1); i++)
					printf("%d,", ve[i]);
				printf("%d]\n", ve[total - 1]);
				printf("Era esperado esta lista: [");
				for (int i = 0; i < (nfalta - 1); i++)
					printf("%d,", falta[i]);
				printf("%d]\n", falta[nfalta - 1]);
			}
		
		} else
			{
				printf("\nNumero de cromos em falta: %d (errado, esperado 9)\n", total);
				printf("Lista incorreta dos cromos em falta: [");
				for (int i = 0; i < (total - 1); i++)
					printf("%d,", ve[i]);
				printf("%d]\n", ve[total - 1]);
			}
		free(ve);
	}
	else
		printf("\ncromos_em_falta retornou NULL\n");
	/* fim teste prob1.1 */
	/****************************************************/

	/* inicio teste prob1.2 */
	printf("\nProblema 1.2\n");
	pilha *cro = pilha_nova();
	if (cro == NULL)
	{
		printf("\nSem espaço de memoria\n");
		return 0;
	}
	pilha_push(cro, 24);
	pilha_push(cro, 5);
	pilha_push(cro, 35);
	pilha_push(cro, 25);
	pilha_push(cro, 34);
	pilha_push(cro, 11);
	pilha_push(cro, 6);
	pilha_push(cro, 5);
	pilha_push(cro, 2);
	
	
	int inicio=10, fim=25;
	int esperado[]={2,5,6,34,35,5};
	int  nesperado=6;
	pilhaItem *item;

	flag=0;
	retirar_cromos_intervalo(cro, inicio, fim);

	if (pilha_tamanho(cro) == 6)
	{
		item = cro->raiz;
		for (int i = 0; i < nesperado; i++)
		{
			if (item->elemento!=esperado[i])
				flag=1;
			item = item->proximo;
		}
		if (flag==0)
		{
			printf("\nOs cromos foram retirados corretamente (Certo)\n");
	
		}
		else
		{
			printf("\nOs cromos nao estao na ordem certa (Errado)\n");
			item = cro->raiz;
			for (int i = 0; i < pilha_tamanho(cro); i++)
			{
				if (item->elemento==11)
					printf("O cromo numero 11 nao foi retirado\n");
				if (item->elemento==24)
					printf("O cromo numero 24 nao foi retirado\n");
				if (item->elemento==25)
					printf("O cromo numero 25 nao foi retirado\n");
				item = item->proximo;
			}
		
		}
	}
	else
	{
		printf("\npilha com tamanho errado (tamanho: %d; esperado: 6)\n", pilha_tamanho(cro));
		item = cro->raiz;
		for (int i = 0; i < pilha_tamanho(cro); i++)
		{
				if (item->elemento==11)
					printf("O cromo numero 11 nao foi retirado\n");
				if (item->elemento==24)
					printf("O cromo numero 24 nao foi retirado\n");
				if (item->elemento==25)
					printf("O cromo numero 25 nao foi retirado\n");
				item = item->proximo;
		}
	}
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
	/****************************************************/
	return 0;
}
