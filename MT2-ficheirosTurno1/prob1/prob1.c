#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"
#include "heap.h"

int compara_bsts(no_bst *noA, no_bst *noB)
{
    if(noA == NULL && noB == NULL) return 1;

    if(strcmp(noA->str, noB->str) != 0) return 0;
    if(compara_bsts(noA->esquerda, noB->esquerda) == 0) return 0;
    if(compara_bsts(noA->direita, noB->direita) == 0) return 0;

    return 1;
}

int altera_valor(heap *h, char *valor_original, char *valor_novo)
{
    if(h == NULL || valor_original == NULL || valor_novo == NULL) return -1;

    int prio_atual;
    char *atual;
    heap *aux = heap_nova(h->tamanho);

    //Copiar os valores de h para aux, substituindo valor_original por valor_novo
    while(h->tamanho > 0) {
        prio_atual = h->elementos[1]->prioridade;
        atual = heap_remove(h);
        if(atual == NULL) return -1;

        if(strcmp(valor_original, atual) == 0) {
            if(!heap_insere(aux, valor_novo, /*valor_novo[0]*/prio_atual)) return -1;;
        } else {
            if(!heap_insere(aux, atual, /*atual[0]*/prio_atual)) return -1;
        }

        free(atual);
    }

    //Copiar aux para h
    while(aux->tamanho > 0) {
        prio_atual = aux->elementos[1]->prioridade;
        atual = heap_remove(aux);
        if(atual == NULL) return -1;

        if(!heap_insere(h, atual, /*atual[0]*/prio_atual)) return -1;
        
        free(atual);
    }

    heap_apaga(aux);
    return 0;
}

/****************************************************/
/*     Funcoes ja implementadas (nao modificar)     */
/****************************************************/

int main()
{
    // Pergunta 1.1
    printf("Alinea 1.1\n");
    arvore_bst *bst1 = bst_nova();
    arvore_bst *bst2 = bst_nova();
    arvore_bst *bst3 = bst_nova();

    char strs[6][2] = {"D", "B", "C", "E", "A", "F"};
    for (int i = 0; i < 6; i++)
    {
        bst_insere(bst1, strs[i]);
        bst_insere(bst2, strs[i]);
    }

    if (compara_bsts(bst1->raiz, bst2->raiz) == 1)
    {
        printf("bst1 e bst2 sao iguais (OK)\n");
    }
    else
        printf("bst1 e bst2 nao sao iguais (ERRO)\n");

    char novas_strs[6][2] = {"D", "B", "C", "F", "A", "E"};
    for (int i = 0; i < 6; i++)
    {
        bst_insere(bst3, novas_strs[i]);
    }
    if (compara_bsts(bst1->raiz, bst3->raiz) == 1)
    {
        printf("bst1 e bst3 sao iguais (ERRO)\n");
    }
    else
        printf("bst1 e bst3 nao sao iguais (OK)\n");

    bst_apaga(bst1);
    bst_apaga(bst2);
    bst_apaga(bst3);

    // Pergunta 1.2
    printf("\n\nAlinea 1.2\n");
    heap *h = heap_nova(6);
    for (int i = 0; i < 6; i++)
        heap_insere(h, strs[i], strs[i][0]);

    printf("Heap original\n");
    heap_imprime(h, 1);

    altera_valor(h, "C", "Cc");
    altera_valor(h, "F", "PROG2");
    altera_valor(h, "X", "-");
    printf("\n\n\nHeap apos alteracoes\n");
    heap_imprime(h, 1);

    heap_apaga(h);
}