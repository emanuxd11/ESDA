#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "vetor.h"
#include "lista.h"

#define BUFFER 256

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
vetor* pesquisar_destinatarios(vetor *vrem, vetor *vdest, const char *remetente)
{
	/*** Responder a 2.1 aqui ***/
	if(vrem == NULL || vdest == NULL || remetente == NULL) return NULL;

	
	return NULL;
}

/*** problema 2.2 ***/
lista *contar_correspondencia(vetor *vcp_dest, int *cpdistintos)
{
	/*** Responder a 2.2 aqui ***/
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
	/****************************************************/
	/* inicio teste prob2.1 */
	printf("\nProblema 2.1\n");
	vetor *dst = pesquisar_destinatarios(vrem,vdest,"Carolina Costa");
	printf("Para o remetente Carolina Costa...\n");
	if (dst == NULL)
		printf("\nFuncao retornou NULL.\n");
	else {
		if(vetor_tamanho(dst) != 4)
			printf("\nERRO...Tamanho do vetor (%d; esperado: 4)", vetor_tamanho(dst));
		else
			printf("\nTamanho do vetor OK: %d\n", vetor_tamanho(dst));
		printf("\nConteudo do vetor de destinatarios:\n");
		for(int i=0; i<vetor_tamanho(dst);i++) {
			printf("%s\n", vetor_elemento(dst,i));
		}
	}
	/* fim teste prob2.1 */
	/****************************************************/

	/* inicio teste prob2.2 */
	printf("\nProblema 2.2\n");

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
	/* fim teste prob2.2 */
	/****************************************************/

	lista_apaga(cp);
	vetor_apaga(vrem);
	vetor_apaga(vdest);
  	vetor_apaga(vcp_dest);
	return 0;
}
