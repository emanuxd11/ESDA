#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
void trocar(fila *f, int pos1, int pos2) {
	/*** Responder ao problema 2.1 aqui ***/

	if(pos1 > fila_tamanho(f) || pos2 > fila_tamanho(f) || pos1 == 0 || pos2 == 0 || pos1 == pos2 || f == NULL) {
		printf("Troca entre a posição %d e a posição %d não realizada!\n", pos1, pos2);
		return;
	}

	filaItem *nome1 = f->cabeca, *nome2 = f->cabeca, *temp;
	int i;
	for(i = 0; i < pos1-1; i++) {
		nome1 = nome1->proximo;
	}
	for(i = 0; i < pos2-1; i++) {
		nome2 = nome2->proximo;
	}

	temp = nome1;
	nome1 = nome2;
	nome2 = temp;

	printf("O %s trocou com o %s!!!1!!!!\n", nome2->string, nome1->string);
}

/*** problema 2.2 ***/

lista *sublista_apelido(fila *f, const char *apelido) {
	/*** Responder ao problema 2.2 aqui ***/
	lista *ret = lista_nova();
	char *linha;

	while(!fila_vazia(f)) {
		linha = (char*)fila_front(f);

		//ver se tem apelido, e se o apelido não se encontra no primeiro nome
		if(strchr(linha, ' ') != NULL && strtok(linha, " ") != apelido) {
			//se o apelido corresponde ao desejado, adiciona-se à lista
			if(strcmp(strtok(NULL, " "), apelido) == 0) {
				//voltamos a juntar o apelido ao primeiro nome
				linha = strcat(linha, " ");
				linha = strcat(linha, apelido);
				lista_insere(ret, linha, NULL);
			}
		}

		//pop para passar ao próximo elemento
		fila_pop(f);
	}

	return ret;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{

	/* testes */
	fila *fila1 = fila_nova();

	lista *nomes;
	l_elemento *ptr;

	const char *str = "Costa";

	/* preenche a fila 1 */
	if (fila_push(fila1, "João Teixeira") == -1)
		return -1;
	if (fila_push(fila1, "Júlia Costa") == -1)
		return -1;
	if (fila_push(fila1, "Pedro") == -1)
		return -1;
	if (fila_push(fila1, "Henrique") == -1)
		return -1;
	if (fila_push(fila1, "Paulo") == -1)
		return -1;
	if (fila_push(fila1, "Susana") == -1)
		return -1;
	if (fila_push(fila1, "Teresa Santos") == -1)
		return -1;
	if (fila_push(fila1, "Afonso Costa") == -1)
		return -1;

	/* início do teste de prob2.1 */

	trocar(fila1, 3, 5); // caso em que as posições existem

	trocar(fila1, 3, 15); // caso em que pelo menos uma posição NÃO existe

	/* fim do teste de prob2.1 */

	/* início do teste de prob2.2 */

	nomes = sublista_apelido(fila1, str);

	if (nomes != NULL)
	{
		ptr = nomes->inicio;

		while (ptr)
		{
			printf("%s\n", ptr->str);
			ptr = ptr->proximo;
		}
	}
	/* fim do teste de prob2.2 */

	fila_apaga(fila1);

	lista_apaga(nomes);

	return 0;
}
