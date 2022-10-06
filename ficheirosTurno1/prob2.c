#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"
#include "fila.h"

/****************************************************/
/*              Funcoes a implementar               */
/****************************************************/

/*** problema 2.1 ***/
int contar_apelidos(fila *f) {
	/*** Responder ao 2.1 aqui ***/

	filaItem *cauda = f->cauda, *cabeca = f->cabeca;;
	int cont = 0;

	//cabeça é o que está para sair
	while(cabeca != cauda) {
		if(strchr(cabeca->proximo->string, ' ') != NULL) {
			cont++;
		}
		
		cabeca = cabeca->proximo;
	}

	return cont;
}

/*** problema 2.2 ***/

lista *lista_a_j(fila *f) {
	/*** Responder ao 2.2 aqui ***/

	lista *ret = lista_nova();

	while(!fila_vazia(f)) {
		if(fila_front(f)[0] <= 'J' && fila_front(f)[0] >= 'A') {
			lista_insere(ret, fila_front(f), NULL);
		}

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

	lista *nomes_A_J;
	l_elemento *ptr;

	/* preenche a fila 1 */
	if (fila_push(fila1, "Maria") == -1)
		return -1;
	if (fila_push(fila1, "João Teixeira") == -1)
		return -1;
	if (fila_push(fila1, "Júlia Costa") == -1)
		return -1;
	if (fila_push(fila1, "Henrique") == -1)
		return -1;
	if (fila_push(fila1, "Afonso Costa") == -1)
		return -1;
	if (fila_push(fila1, "Nuno Antunes") == -1)
		return -1;

	/* início do teste de prob2.1 */

	printf("Número de pessoas com apelido: %d\n", contar_apelidos(fila1));

	/* fim do teste de prob2.1 */

	/* início do teste de prob2.2 */

	nomes_A_J = lista_a_j(fila1);
	if (nomes_A_J != NULL)
	{

		ptr = nomes_A_J->inicio;

		while (ptr)
		{
			printf("%s\n", ptr->str);
			ptr = ptr->proximo;
		}
	}

	/* fim do teste de prob2.2 */

	lista_apaga(nomes_A_J);

	fila_apaga(fila1);

	return 0;
}
