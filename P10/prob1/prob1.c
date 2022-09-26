#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

/*** problema 1 ***/
char* avl_maiorstring(no_avl *no)
{
	/* complexidade do algoritmo: ________________ */
	if(no == NULL) return "";

	char *atual = no->str;
	char *maior_esquerda = avl_maiorstring(no->esquerda);
	char *maior_direita = avl_maiorstring(no->direita);
	
	if(strlen(maior_esquerda) < strlen(maior_direita)) {
		if(strlen(atual) < strlen(maior_direita)) {
			atual = maior_direita;
		}
	} else if(strlen(atual) < strlen(maior_esquerda)) {
		if(strlen(atual) < strlen(maior_esquerda)) {
			atual = maior_esquerda;
		}
	}

	return atual;
}

/* Aqui comeca o codigo de teste. Nao modificar! */

#define MAX_STR 500

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *fp=fopen("paises.txt", "r");
	char str_aux[MAX_STR], *str;

	arvore_avl *arv;
	puts("* Problema 1 *");
	arv = avl_nova();
	while(fgets(str_aux,MAX_STR,fp) != NULL)
	{
		if(str_aux[strlen(str_aux)-1] == '\n')
			str_aux[strlen(str_aux)-1] = '\0';
		avl_insere(arv, str_aux);
	}
	str = avl_maiorstring(arv->raiz);
	printf("Maior string: ");
	if(str != NULL)
		puts(str);
	else
		puts("(null)");
	avl_apaga(arv);

	fclose(fp);
	return 0;
}
