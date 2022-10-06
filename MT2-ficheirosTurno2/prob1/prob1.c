#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bst.h"
#include "heap.h"

int bst_cheia(no_bst *no)
{
    //Conceito: uma árvore BST encontra-se cheia se todos os
    //seus nós têm dois ou zero filhos.

    //Se o nó for nulo, a árvore está cheia.
    if(no == NULL) return 1;
    //Se os dois filhos forem nulos, a árvore está cheia.
    if(no->esquerda == NULL && no->direita == NULL) return 1;

    //Se os dois filhos não forem nulos, verifica-se se a árvore
    //que parte de cada um deles está cheia. Caso ambas estejam
    //cheias, a árvore está cheia. Caso contrário, está vazia.
    if(no->esquerda != NULL && no->direita != NULL) {
        return bst_cheia(no->esquerda) && bst_cheia(no->direita);
    }

    //Para todos os casos não contemplados anteriormente (i.e. 
    //apenas um dos filhos é nulo), a árvore não está cheia.
    return 0;
}

int altera_prioridade(heap *h, char *valor, int nova_prioridade)
{
    /*
    //Conceito: usar uma heap auxiliar para guardar os elementos da original.
    //Depois, voltar a inserir os elementos na heap original, substituindo a
    //prioridade do elemento com a string "valor" pela "nova_prioridade".

    //Verificação de argumentos.
    if(h == NULL || valor == NULL || nova_prioridade < 0) return -1;

    //Criar uma heap auxiliar para usar como cópia da heap original.
    heap *aux = heap_nova(h->tamanho);
    //Variáveis auxiliares que permitem: obter e guardar a prioridade
    //do elemento atual, distinguir se o elemento que procuramos existe
    //ou não na heap e guardar a string do elemento atual.
    int prio_atual = 0, enconrou_elem = 0;
    char *atual;

    //Copiar a heap h para a heap auxiliar.
    while(h->tamanho > 0) {
        //Removemos o elemento da heap e guardamo-lo
        //na variável "atual" para o inserir novamente.
        //Guardamos também a sua prioridade, para manter
        //a ordem na heap entre cópias.
        prio_atual = h->elementos[1]->prioridade;
        atual = heap_remove(h);
        if(atual == NULL) return -1;

        //Caso a inserção do elemento na heap dê algum erro,
        //retornamos -1, saindo diretamente da função.
        if(!heap_insere(aux, atual, prio_atual)) return -1;

        //Importante libertar esta memória.
        free(atual);
    }

    //Voltar a copiar os elementos para a heap original, substituindo
    //a prioridade do elemento desejado pela nova prioridade.
    while(aux->tamanho > 0) {
        prio_atual = aux->elementos[1]->prioridade;
        atual = heap_remove(aux);
        if(atual == NULL) return -1;
        
        //Caso o "valor" corresponda ao desejado, alteramos a prioridade.
        //Caso contrário, inserimos normalmente.
        if(strcmp(atual, valor) == 0) {
            //Quando o elemento é encontrado, ativamos esta flag
            //para saber o que retornar (0 ou -1) no fim da função.
            enconrou_elem = 1;
            if(!heap_insere(h, valor, nova_prioridade)) return -1;
        } else {
            if(!heap_insere(h, atual, prio_atual)) return -1;
        }

        free(atual);
    }

    //Libertar todo o espaço ocupado
    //em memória pela heap auxiliar.
    heap_apaga(aux);

    if(!enconrou_elem) return -1;
    return 0;*/

    if (h == NULL || valor == NULL){
        return -1;
    }
    heap *aux = heap_nova(h->capacidade); //heap->elementos[i]->valor nao se pode fzr neste ex
    if (aux == NULL){
        return -1;
    }
    //verificar se valor existe na heap
    int existe = 0;
    //int tam = h->tamanho; não é necessário
    char *val;
    int prio;
    //1o organizar heap  h passando-a para aux. 2o ja ta direia, passar de aux para h
    while (h->tamanho > 0){
        prio = h->elementos[1]->prioridade; //so troca a prio num dos elemntos, no resto tem de se manter
        val = heap_remove(h); //return de heap remove e' o valor de h
        //o val vai ser inserido na heap aux, mas se for o valor pelo qual se quer trocar a prio
        //vai se inserir com a nova prio
        if (strcmp(val,valor) == 0){ //e' este o valor a trocar (cuidado, n posso fzr val == valor)
            existe = 1;
            heap_insere(aux, val, nova_prioridade); //inseri-lo na aux mas agr com a prio mudada
        }
        else {
            heap_insere(aux, val, prio);
        }

        free(val); //importante fazer este free
    }

    //ok a heap aux ta organizada, agr e' passar isso para a original h 
    //if (existe == 0){
    //    return -1;
    //} não podes retornar aqui, porque se o fizeres o programa não vai copiar a heap auxiliar de volta
    //para a original!!

    while (aux->tamanho > 0) {
        prio = aux->elementos[1]->prioridade; //prioridades ja tao arranjadas
        val = heap_remove(aux);
        heap_insere(h, val, prio);

        free(val); //importante fazer este free
    }
    heap_apaga(aux);

    if(existe == 0) return -1;
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

    char strs[5][2] = {"D", "B", "C", "F", "A"};
    for (int i = 0; i < 5; i++)
        bst_insere(bst1, strs[i]);

    if (bst_cheia(bst1->raiz) == 1)
        printf("bst1 e' uma arvore cheia (OK)\n");
    else
        printf("bst1 nao e' uma arvore cheia (ERRO)\n");

    char novas_strs[6][2] = {"D", "B", "C", "E", "A", "F"};
    for (int i = 0; i < 6; i++)
        bst_insere(bst2, novas_strs[i]);

    if (bst_cheia(bst2->raiz) == 1)
        printf("bst2 e' uma arvore cheia (ERRO)\n");
    else
        printf("bst2 nao e' uma arvore cheia (OK)\n");

    bst_apaga(bst1);
    bst_apaga(bst2);

    // Pergunta 1.2
    printf("\n\nAlinea 1.2\n");
    heap *h = heap_nova(6);
    for (int i = 0; i < 6; i++)
        heap_insere(h, novas_strs[i], novas_strs[i][0]);

    printf("Heap original\n");
    heap_imprime(h, 1);

    altera_prioridade(h, "C", 60);
    altera_prioridade(h, "D", 75);
    altera_prioridade(h, "X", 0);
    printf("\n\n\nHeap apos alteracoes\n");
    heap_imprime(h, 1);

    heap_apaga(h);
}