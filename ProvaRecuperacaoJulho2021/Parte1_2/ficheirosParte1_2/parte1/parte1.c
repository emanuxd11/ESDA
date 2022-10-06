#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilha.h"
#include "vetor.h"
#include "lista.h"
#define BUFFER 256


/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 1.1 ***/
void retirar_cromos_intervalo(pilha *cromos, int inicio, int fim)
{
	/*** Responder a 1.1 aqui ***/
}

/*** problema 1.2 ***/
lista *contar_correspondencia(vetor *vcp_dest, int *cpdistintos)
{
	/*** Responder a 1.2 aqui ***/
	return NULL;
}
/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

void lerParaVetores(FILE* ficheiro, vetor* vrem, vetor *vdest, vetor *vcp_dest)
{
	char buffer[BUFFER], *nlptr;

	if (ficheiro == NULL)
		return;

	while(fgets(buffer, BUFFER, ficheiro) != NULL)
	{
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vrem, buffer, -1);

		fgets(buffer, BUFFER, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vdest, buffer, -1);

		fgets(buffer, BUFFER, ficheiro);
		nlptr = strchr(buffer, '\n');
		if (nlptr)
			*nlptr = '\0';
		vetor_insere(vcp_dest, buffer, -1);
	}
}

int main()
{
	/****************************************************/
	/* inicio teste prob1.1 */
	printf("\nProblema 1.1\n");
	int flag=0;

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
			printf("\nOs cromos não estão na ordem certa (Errado)\n");
			item = cro->raiz;
			for (int i = 0; i < pilha_tamanho(cro); i++)
			{
				if (item->elemento==11)
					printf("O cromo numero 11 não foi retirado\n");
				if (item->elemento==24)
					printf("O cromo numero 24 não foi retirado\n");
				if (item->elemento==25)
					printf("O cromo numero 25 não foi retirado\n");
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
					printf("O cromo numero 11 não foi retirado\n");
				if (item->elemento==24)
					printf("O cromo numero 24 não foi retirado\n");
				if (item->elemento==25)
					printf("O cromo numero 25 não foi retirado\n");
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
	/* fim teste prob1.1 */
	/****************************************************/

	FILE *fin;
	vetor* vrem;
	vetor* vdest;
	vetor* vcp_dest;
	int cpdistintos;

	vrem=NULL; vdest=NULL; vcp_dest=NULL;

	fin = fopen("correspondencia.txt", "r");
	if(fin == NULL)
	{
		printf("Erro ao abrir ficheiro.\n");
		return 1;
	}

	vrem = vetor_novo();
	vdest = vetor_novo();
	vcp_dest = vetor_novo();
	lerParaVetores(fin, vrem, vdest, vcp_dest);

	fclose(fin);
	
	/* inicio teste prob1.2 */
	printf("\nProblema 1.2\n");

	lista *cp = contar_correspondencia(vcp_dest,&cpdistintos);

	if (cp == NULL)
		printf("\nFuncao retornou NULL.\n");
	else {
		if(lista_tamanho(cp) != 11)
			printf("\nERRO...Tamanho da lista (%d; esperado: 11)", lista_tamanho(cp));
		else
			printf("\nTamanho da lista OK: %d", lista_tamanho(cp));
	}
	if(cpdistintos != 11)
		printf("\nERRO...Numero de codigos postais distinto retornado (%d; esperado: 11)\n", cpdistintos);
	else
		printf("\nNumero de codigos postais distintos retornado OK: %d\n", cpdistintos);

  if(cp) {
		printf("\n");
		for (int i=0; i< lista_tamanho(cp); i++) {
			l_elemento *pos=lista_elemento(cp,i);
			printf("%s : %d cartas\n", pos->str, pos->count);
		}
	}
	

	lista_apaga(cp);
	vetor_apaga(vrem);
	vetor_apaga(vdest);
  	vetor_apaga(vcp_dest);
	
	/* fim teste prob1.2 */
	/****************************************************/
	return 0;
}
