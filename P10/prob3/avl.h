/*****************************************************************/
/*           Arvore AVL | PROG2 | LEEC | 2021/22                 */
/*****************************************************************/

#ifndef ARVOREAVL_H
#define ARVOREAVL_H

/**
 * registo para armazenar cada no'
 */
typedef struct no_avl_
{
	int valor;
	struct no_avl_ *esquerda;
	struct no_avl_ *direita;
	int altura;
} no_avl;

/**
 * arvore_avl contem apenas um apontador para a raiz
 */
typedef struct
{
	no_avl *raiz;
} arvore_avl;

/**
 *  cria uma nova arvore AVL vazia
 *  retorno: apontador para a arvore criada
 *  nota: se arvore nao foi criada retorna NULL
 */
arvore_avl* avl_nova();


/**
 *  elimina uma arvore, libertando toda a memoria ocupada
 *  parametro: avl apontador para arvore
 *  nota: se avl = NULL retorna sem fazer nada
 */
void avl_apaga(arvore_avl* avl);

/**
 *  devolve o no' que contem o valor especificado
 *  parametro: avl apontador para arvore
 *  parametro: v valor pretendido
 *  retorno: elemento pretendido ou NULL se ocorrer algum erro ou nao encontrar elemento
 */
no_avl* avl_pesquisa(arvore_avl* avl, const int v);

/**
 *  insere um novo no' com o valor especificado
 *  parametro: avl apontador para arvore
 *  parametro: v valor a inserir
 *  retorno: -1 se ocorrer algum erro ou 0 se bem sucedido
 *  nota: executa as rotacoes necessarias caso a arvore deixe de estar balanceada apos a insercao
 */
int avl_insere(arvore_avl* avl, const int v);

/**
 *  remove o no' com o valor especificado
 *  parametro: avl apontador para arvore
 *  parametro: v valor a remover
 *  retorno: -1 se ocorrer algum erro ou 0 caso contrario
 *  nota: executa as rotacoes necessarias caso a arvore deixe de estar balanceada apos a remocao
 */
int avl_remove(arvore_avl* avl, const int v);

/**
 *  devolve o valor mais baixo possivel de encontrar na arvore
 *  parametro: avl apontador para arvore
 *  retorno: NULL se ocorrer algum erro ou a string pretendida caso contrario
 */

int avl_min(arvore_avl* avl);

/**
 *  devolve o valor mais alto possivel de encontrar na arvore
 *  parametro: avl apontador para arvore
 *  retorno: NULL se ocorrer algum erro ou a string pretendida caso contrario
 */

int avl_max(arvore_avl* avl);

/**
 *  devolve a altura da (sub-)arvore com origem no no' especificado
 *  parametro: no raiz da (sub-)arvore
 *  retorno: -1 se no' nao existe ou a altura do no' caso contrario
 */
int avl_altura(no_avl* no);

/**
 *  percorre a arvore em pre-ordem e imprime as strings de cada no'
 *  parametro: avl apontador para arvore
 */
void avl_imprime(arvore_avl* avl);


#endif  /* ARVOREAVL_H */
