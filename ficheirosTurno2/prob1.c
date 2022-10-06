#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"


/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
int *troca(int *cromos1, int n1, int *cromos2, int n2, int *tam) {
	/***  Responder ao problema 1.1 aqui  ***/
	
	//No início, alocar a memória máxima necessária. No final, ajusta-se com base no tamanho.
	int *ret = (int*)malloc((n1+n2) * sizeof(int));
	int i, j, repetido;

	for(i = 0; i < n1; i++) {
		repetido = 0;

		//procurar repetidos
		//se estivermos no último elemento,
		//percorremos o vetor de trás para a frente 
		if(i+1 == n1) {
			for(j = i-1; j > 0; j++) {
				if(cromos1[i] == cromos1[j]) {
					repetido = 1;
					break;
				}
			}
		} else {
			for(j = i+1; j < n1; j++) {
				if(cromos1[i] == cromos1[j]) {
					repetido = 1;
					break;
				}
			}
		}
		
		//se j < n1, encontrou repetido
		if(repetido) {
			//ver se o repetido não existe em cromos2
			for(j = 0; j < n2; j++) {
				if(cromos1[i] == cromos2[j]) {
					break;
				}
			}

			//se j == n2, não encontrou
			if(j == n2) {
				//verificar se o elemento existe em ret
				for(j = 0; j < *tam; j++) {
					if(cromos1[i] == ret[j]) {
						break;
					}
				}
				
				if(j == *tam) {	
					ret[(*tam)++] = cromos1[i];
				}
			}
		}

	}

	//realocar apenas a memória necessária
	ret = (int*)realloc(ret, (*tam) * sizeof(int));

	return ret;
}

/*** problema 1.2 ***/

void retirar_cromos(pilha *cromos, int *retirar, int nr) {
	/***  Responder ao problema 1.2 aqui  ***/

	pilha *aux = pilha_nova();
	int i, j, cont;

	for(i = 0; i < nr; i++) {
		cont = 0;
		while(pilha_tamanho(cromos) > 1) {
			while(pilha_top(cromos)->elemento != retirar[i] && pilha_tamanho(cromos) > 1) {
				pilha_push(aux, pilha_top(cromos)->elemento);
				pilha_pop(cromos);
				cont++;
			}

			if(retirar[i] == pilha_top(cromos)->elemento) {
				pilha_pop(cromos);
			}
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
	int colecao1[] = {2,4,5,6,5,4,10,11,10,10};
	int colecao2[] = {3,4,6,9,12};
	int tam1=10,tam2=5;
	int total=0;
	int *ve;

	/* inicio teste prob1.1 */
	ve = troca(colecao1, tam1, colecao2, tam2, &total);
	if(ve) { 
		//troquei para 2 pq no enunciado diz 2
		if (total==2) printf("\nNúmero de cromos trocados: 2 (Certo)\n");
		else printf("\nNúmero de cromos trocados errado : (tamanho: %d; esperado: 4)\n",total);
		printf("Cromos trocados: [");
		for (int i=0;i<(total-1);i++)
		printf("%d,",ve[i]);
		printf("%d]\n",ve[total-1]);
		free(ve);
		
	} else
		printf("\ntroca retornou NULL\n"); 
	/* fim teste prob1.1 */

	/* inicio teste prob1.2 */
	pilha *cro=pilha_nova();
	if (cro == NULL)
		{  	printf("\nSem espaço de memoria\n");
			return 0;}

	pilha_push(cro,24);
	pilha_push(cro,5);
	pilha_push(cro,35);
	pilha_push(cro,25);
	pilha_push(cro,34);
	pilha_push(cro,11);
	pilha_push(cro,6);
	pilha_push(cro,5);
	pilha_push(cro,2);
	int repetidos[] = {5,34,25};
	int nr=3;
	pilhaItem *item;
	int erro1=0,erro2=0,erro3=0, errototal=0;
	
	retirar_cromos(cro, repetidos, nr);
	
		item=cro->raiz;
		while (item) {
			if (item->elemento==5)
			erro1=1;
			if (item->elemento==34)
			erro2=1;
			if (item->elemento==25)
			erro3=1;
			item=item->proximo;
		}
		if (erro1==1) {
				printf("\nO cromo numero 5 não foi retirado da pilha\n");
				errototal++;

		} 
		if (erro2==1) {
				printf("\nO cromo numero 34 não foi retirado da pilha\n");
				errototal++;

		} 
		if (erro3==1) {
				printf("\nO cromo numero 25 não foi retirado da pilha\n");
				errototal++;

		} 

	if(pilha_tamanho(cro)==5)
	{
	
		if (errototal==0) {
				printf("\nOs cromos foram todos retirados corretamente\n"); 
		}
				
	}
	else
		printf("\npilha com tamanho errado (tamanho: %d; esperado: 5)\n",pilha_tamanho(cro));
		printf("Cromos: [");
		item=cro->raiz;
		for (int i=0;i<pilha_tamanho(cro)-1;i++) {
		printf("%d,",item->elemento);
		item=item->proximo;
		}
		printf("%d]\n",item->elemento);
		pilha_apaga(cro);
	/* fim teste prob1.2 */


	return 0;
}
