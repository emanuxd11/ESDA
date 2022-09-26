#include "armazem.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * funcoes do armazem
 */
/* alinea b) */
/**
 *  \brief cria um novo armazem vazio
 *  \param comprimento valor maximo do comprimento da fila de pilhas de contentores
 *  \param altura valor maximo da altura das pilhas de contentores
 *  \return apontador para o armazem ou NULL se erro na alocacao de memoria
 *  \remark a fila de contentores devera ser criada nesta altura, 
 *          ainda que inicialmente fique vazia.
 */
armazem* armazem_novo(int comprimento, int altura)
{
	armazem *res = (armazem*)malloc(sizeof(armazem));

	res->altura = altura;
	res->comprimento = comprimento;
	res->contentores = fila_nova();
	
	return res;
}

/* alinea c) */
/**
 *  \brief verifica se o armazem esta' vazio
 *  \param armz apontador para o armazem
 *  \return 1 se armazem vazio; 0 se contem contentorese
 */
int armazem_vazio(armazem *armz)
{
	if(armz == NULL) return 1;
	if(armz->contentores->raiz == NULL) return 1;
	return 0;
}

/* alinea d) */
/**
 *  \brief verifica se o armazem pode receber mais contentores
 *  \param armz apontador para o armazem
 *  \return 1 se armazem nao pode receber mais contentores; 0 se pode
 *  \remark para um armazem estar cheio, tanto a fila de contentores como a 
 *          ultima pilha da fila devem estar na sua ocupacao maxima
 *          (comprimento da fila e altura da ultima pilha).
 */
int armazem_cheio(armazem *armz)
{
	if(armz == NULL) return 0;
	
	if(armz->contentores->tamanho == armz->comprimento) {
		pilhaItem *elem = armz->contentores->raiz->elemento->raiz;
		int i = 0;
		while(elem != NULL) {
			elem = elem->proximo;
			i++;
		}

		if(i == armz->altura) return 1;
	}

	/*filaItem *elem = armz->contentores->raiz;
	int i = 0;
	while(elem != NULL) {
		elem = elem->proximo;
		i++;
	}

	//printf("\ni = %d e comprimento = %d", i, armz->comprimento);

	if(i == armz->comprimento) {

	}*/
	
	return 0;
}

/* alinea e) */
/**
 *  \brief empilha contentor no armazem
 *  \param armz apontador para o armazem
 *  \param contr apontador para o contentor
 *  \return 1 se contentor foi descarregado; 0 se armazem cheio
 *  \remark contentor e' carregado na primeira pilha; quando a pilha
 *    esta' completa comeca a empilhar noutra;
 */
int armazenar_contentor(armazem *armz, contentor *contr)
{
	if(armz == NULL || contr == NULL || armazem_cheio(armz)) return 0;

	pilha *p = fila_back(armz->contentores);

	//se a pilha não existir ou estiver cheia, cria-se uma pilha nova
	if(p == NULL || p->tamanho == armz->altura) {
		p = pilha_nova();
		pilha_push(p, contr);
		fila_push(armz->contentores, p);
		return 1;
	} else {
		pilha_push(p, contr);
		return 1;
	}

	return 0;
}

/* alinea f) */
/**
 *  \brief retira um contentor do armazem para o navio
 *  \param armz apontador para o armazem
 *  \return apontador para o contentor retirado ou NULL se armazem vazio
 *  \remark contentor e' retirado da pilha mais proxima do navio
 */
contentor *expedir_contentor(armazem *armz)
{
	/*if(armz == NULL || armazem_vazio(armz)) return NULL;

	pilha *p = fila_front(armz->contentores);
	contentor *c = pilha_top(p);

	contentor *ret = contentor_novo(c->destino, c->valor);

	//contentor_apaga(c);
	if(pilha_tamanho(p) == 0) {
		fila_pop(armz->contentores);
	} else {
		pilha_pop(p);
	}

	return ret;*/
	return NULL;
}