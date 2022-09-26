/*****************************************************************/
/*   Fila de prioridade / min-heap | ESDA | L.EEC | 2021/22     */
/*****************************************************************/

#include "heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAIZ 		(1)
#define PAI(x) 		(x/2)
#define FILHO_ESQ(x) 	(x*2)
#define FILHO_DIR(x) 	(x*2+1)

int menor_que(elemento * e1, elemento * e2);

heap* heap_nova(int capacidade)
{
    heap * h = (heap *) malloc(sizeof(heap));

    if (!h)
        return NULL;

    h->tamanho = 0;
    h->capacidade = capacidade;
    h->elementos = (elemento **) calloc(capacidade+1, sizeof(elemento *));


    if (!h->elementos) {
        free(h);
        return NULL;
    }
    for (int i=0;i<=capacidade;i++)
        h->elementos[i]=NULL;
    return h;
}

void heap_apaga(heap *h)
{
    int i;

    if(!h)
        return;

    /* apaga todos os elementos e respetivas strings */
    for(i=RAIZ; i<=h->tamanho; i++)
    {
    //    free(h->elementos[i]->no);
        free(h->elementos[i]);
        h->elementos[i]=NULL;
    }

    free(h->elementos);
    free(h);
}


elemento * elemento_novo(double prioridade, no_grafo * no, aresta_grafo *aresta)
{
	if(!no && !aresta)
	return NULL;   

	elemento * elem = (elemento *) malloc(sizeof(elemento));

    if (!elem)
        return NULL;


    elem->no=no;
    elem->aresta=aresta;
    elem->prioridade = prioridade;

    return elem;
}


int heap_insere(heap * h,  no_grafo* no,aresta_grafo *aresta, double prioridade)
{
    elemento * aux=NULL, * elem;
    int i=0;

    /* se heap esta' cheia, nao insere elemento */
    if (h->tamanho >= h->capacidade)
        return 0;

    elem = elemento_novo(prioridade,no, aresta);
    if (!elem)
        return 0;

    /* coloca elemento no fim da heap */
    h->tamanho++;
    i = h->tamanho;
    h->elementos[i] = elem;

     /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
    while (i != RAIZ && menor_que(h->elementos[i], h->elementos[PAI(i)]))
    {
        aux = h->elementos[PAI(i)];
        h->elementos[PAI(i)] = h->elementos[i];
        h->elementos[i] = aux;
        i = PAI(i);
    }
    return 1;
}

no_grafo * heap_remove(heap * h)
{
    int i, filho_maior;
    elemento * aux;
    no_grafo * ret;

    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->tamanho <= 0)
        return NULL;

    ret = h->elementos[RAIZ]->no;
    free(h->elementos[RAIZ]);

    /* coloca ultimo elemento da heap na raiz */
    h->elementos[RAIZ] = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = NULL;
    h->tamanho--;

     i = RAIZ;

    /* enquanto nao chegar 'a base da heap */
    while(FILHO_ESQ(i) <= h->tamanho)
    {
        filho_maior = FILHO_ESQ(i);

        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) <= h->tamanho && menor_que(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)]))
            filho_maior = FILHO_DIR(i);

        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (menor_que(h->elementos[filho_maior], h->elementos[i]))
        {
            aux = h->elementos[filho_maior];
            h->elementos[filho_maior] = h->elementos[i];
            h->elementos[i] = aux;
            i = filho_maior;
        }
        else
            break;
    }

    return ret;
}


aresta_grafo * heap_remove_aresta(heap * h)
{
    int i, filho_maior;
    elemento * aux;
    aresta_grafo * ret;

    /* se heap estiver vazia, nao remove elemento */
    if (!h || h->tamanho <= 0)
        return NULL;

    ret = h->elementos[RAIZ]->aresta;
    free(h->elementos[RAIZ]);

    /* coloca ultimo elemento da heap na raiz */
    h->elementos[RAIZ] = h->elementos[h->tamanho];
    h->elementos[h->tamanho] = NULL;
    h->tamanho--;

     i = RAIZ;

    /* enquanto nao chegar 'a base da heap */
    while(FILHO_ESQ(i) <= h->tamanho)
    {
        filho_maior = FILHO_ESQ(i);

        /* verifica se existe filho 'a direita e se este e' mais prioritario do que 'a esquerda */
        if (FILHO_DIR(i) <= h->tamanho && menor_que(h->elementos[FILHO_DIR(i)], h->elementos[FILHO_ESQ(i)]))
            filho_maior = FILHO_DIR(i);

        /* enquanto elemento for mais prioritario do que o respetivo pai, troca-os */
        if (menor_que(h->elementos[filho_maior], h->elementos[i]))
        {
            aux = h->elementos[filho_maior];
            h->elementos[filho_maior] = h->elementos[i];
            h->elementos[i] = aux;
            i = filho_maior;
        }
        else
            break;
    }

    return ret;
}


int menor_que(elemento * e1, elemento * e2)
{
    if (e1 == NULL || e2 == NULL)
    {
        return 0;
    }

    return e1->prioridade < e2->prioridade;
}

heap *heap_carrega(grafo *g, int capacidade)
{   
    heap *ret = heap_nova(capacidade);
    if(ret == NULL) return NULL;

    int i, j, k;
    for(i = 0; i < g->tamanho; i++) {
        if(g->nos[i] == NULL) return NULL;

        for(j = 0; j < g->nos[i]->tamanho; j++) {
            if(g->nos[i]->arestas[j] == NULL) return NULL;

            for(k = 1; k < ret->tamanho+1; k++) {
                if(strcmp(g->nos[i]->arestas[j]->codigo, ret->elementos[k]->aresta->codigo) == 0) {
                    break;
                }
            }

            if(k == ret->tamanho+1 || ret->tamanho == 0) {
                if(heap_insere(ret, NULL, g->nos[i]->arestas[j], g->nos[i]->arestas[j]->inspecao) == 0) {
                    heap_apaga(ret);
                    return NULL;
                }
            }
        }
    }

    return ret;
}

aresta_grafo **inspecao_trocos (heap *h, int dias, int *n)
{
    if(h == NULL || dias < 0 || n == NULL) return NULL;

    aresta_grafo **ret = malloc((h->tamanho) * sizeof(aresta_grafo*));
    if(ret == NULL) return NULL;

    aresta_grafo *atual;
    int tempo_insp_total = 0, tempo_insp_atual;
    *n = 0;

    while(h->tamanho > 0 && tempo_insp_total != dias) {
        atual = heap_remove_aresta(h);
        /*
        O tempo de inspeção de uma aresta de distancia d em metros
        é igual a essa distancia em km dividida por 10, daí dividir
        por 1000 e depois por 10. Soma-se 1 a esse valor porque o
        enunciado especifica que os dias são arredondados para cima.
        */
        tempo_insp_atual = (atual->distancia/1000)/10 + 1;

        if(tempo_insp_total + tempo_insp_atual <= dias) {
            tempo_insp_total += tempo_insp_atual;
            ret[*n] = atual;
            (*n)++;
        }
    }

    if(*n == 0) {
        free(ret);
        return NULL;
    }

    ret = realloc(ret, (*n) * sizeof(aresta_grafo*));
    return ret;
}