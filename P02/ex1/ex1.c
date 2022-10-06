/***********************************************************/
/*      PL2 - Listas Ligadas | ESDA | L.EEC | 2021/22      */
/***********************************************************/

/* Para compilar: gcc -g -Wall ex1.c -o ex1 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN_STR 100
#define LISTA_INICIO 0
#define LISTA_FIM 1

/*
 *   Registo para armazenar elementos de uma lista duplamente ligada.
 *   Este registo contém uma string e apontadores para o próximo e
 *   anterior elementos da lista.
 */
typedef struct _l_elemento {
	// string armazenada
	char *str;
	// apontadores para os elementos vizinhos
    struct _l_elemento *proximo;
    struct _l_elemento *anterior;
} l_elemento;

typedef struct {
	l_elemento *inicio;
	l_elemento *fim;
	int tamanho;
} lista;

/******* Funções já implementadas *******/
void lista_imprime(lista *lst);
l_elemento* novo_elemento(const char *valor);

/******* Funções a implementar *******/

/*
 * Cria uma nova lista ligada vazia.
 *  > retorno: apontador para a lista; se a lista não foi criada retorna NULL
 */
lista* lista_nova() {
	/* a) criar nova lista vazia */
    lista *res=malloc(sizeof(lista));
    
    if(res==NULL) {
        return NULL;
    }
    
    res->inicio=NULL;
    res->fim=NULL;
    res->tamanho=0;

    return res;
}

/*
 * Insere um elemento no fim da lista.
 *  > parâmetro 'lst': apontador para a lista
 *  > parâmetro 'str': string a inserir
 *  > retorno: apontador para novo elemento inserido na lista ou NULL se ocorrer um erro
 */
l_elemento* lista_insere(lista *lst, const char *str) {
	/* b) inserir elemento na lista (dica: recorra também à função novo_elemento) */
    l_elemento *novoElem=novo_elemento(str);
    if(novoElem==NULL) {
        return NULL;
    }

    if(lst->inicio==NULL) {
        lst->inicio=novoElem;
    } else {
        lst->fim->proximo=novoElem;
        novoElem->anterior=lst->fim;
    } 

    lst->fim=novoElem;
    lst->tamanho++;

    return novoElem;
}

/*
 * Elimina uma lista, libertando toda a memória ocupada.
 *  > parâmetro 'lst': apontador para a lista
 *  - obs: se lst é NULL, não há operações a realizar
 */
void lista_apaga(lista *lst) {
    /* c) apagar lista */
    if(lst==NULL) {
        return;
    }

    l_elemento *l_elem=lst->inicio;
    l_elemento *temp;

    while(1) {
        temp=l_elem;
        free(l_elem);
        l_elem=temp->proximo;
        if(l_elem->proximo==NULL) break;
    }

    lst->tamanho=0;
    free(l_elem);
}

/*
 * Ordena uma lista por ordem alfabética.
 *  > parâmetro 'lst': apontador para a lista
 *  > retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
 */
int lista_ordena(lista *lst) {
    /* e) ordenar lista */
    if(lst==NULL) {
        return -1;
    }
    if(lst->tamanho == 0)
        return 0;

    l_elemento *elem, *indice;
    char *temp;

    for(elem=lst->inicio; elem->proximo!=NULL; elem=elem->proximo) {
        for(indice=elem->proximo; indice!=NULL; indice=indice->proximo) {
            //se strcmp(str1, str2)<0, str1 vem antes, alfabeticamente, de str2
            if(strcmp(elem->str, indice->str)>0) {
                temp=elem->str;
                elem->str=indice->str;
                indice->str=temp;            
            }
        }
    }

    return 0;
}

/*
 * Remove o elemento especificado.
 *  > parâmetro 'lst': apontador para a lista
 *  > parâmetro 'pos': elemento que se pretende remover
 *  > retorno: apontador para o elemento seguinte ao que foi removido ou NULL se ocorrer um erro
 */
l_elemento* lista_remove(lista *lst, l_elemento *pos) {
	/* g) remover elemento da lista */
    if(lst==NULL) {
        return NULL;
    }
    
    l_elemento *res=pos->proximo;;
    
    if(lst->tamanho==1) {
        lst->inicio=NULL;
        lst->fim=NULL;
        lst->tamanho--;
        free(pos);
        return NULL;
    }

    if(pos->proximo==NULL) {
        pos->anterior->proximo=NULL;
    }
    if(pos->anterior==NULL) {
        lst->inicio=pos->proximo;
    } 
    if(pos->anterior!=NULL && pos->proximo!=NULL) {
        pos->anterior->proximo=pos->proximo;
        pos->proximo->anterior=pos->anterior;
    }

    lst->tamanho--;
    free(pos);

    return res;
}

/*
 * Devolve a posição do primeiro elemento da lista que contém a string especificada
 *  > parâmetro 'lst': apontador para a lista
 *  > parâmetro 'str': string a pesquisar
 *  > parâmetro 'init': apontador para elemento onde a pesquisa é iniciada
 *  > parâmtero 'sentido': pesquisa efetuada a partir do início (LISTA_INICIO) ou a partir do fim (LISTA_FIM)
 *  > retorno: elemento encontrado ou NULL (caso não encontre o elemento ou caso ocorra um erro)
 */
l_elemento* lista_pesquisa(lista *lst, const char *str, l_elemento *init, int sentido) {
	/* h) pesquisar a lista */
    if(lst==NULL) {
        return NULL;
    }

    l_elemento *elem;
    int encontrado=0;

    if(init==NULL) {
        elem=sentido==LISTA_INICIO ? lst->inicio : lst->fim;
    } else {
        elem=init;
    }

    while(sentido==LISTA_INICIO ? elem->proximo!=NULL : elem->anterior!=NULL) {
        if(strstr(elem->str, str)!=NULL) {
            encontrado=1;
            break;
        }

        elem=sentido==LISTA_INICIO ? elem->proximo : elem->anterior;
    }

    return encontrado==1 ? elem : NULL;
}

/*
* Função para alínea i)
* Procura todos os elementos que contêm a string indicada
* e remove-os
* Devolve -1 caso não encontre ou 0 em caso contrário
*/
int procura_remove(lista *lst, const char* str, l_elemento *init, int sentido) {
    l_elemento *prox=init, *elem_encontrado=NULL;
    for( ;init!=NULL; init=prox) {
        elem_encontrado=lista_pesquisa(lst, str, init, sentido);
        if(elem_encontrado==NULL) {
            return -1;
        } else {
            prox=elem_encontrado->proximo;
            lista_remove(lst, elem_encontrado);
        }
    }

    return 0;
}

int main() {
    char f_nome[] = "arquivo.txt";
    FILE *ficheiro;
    ficheiro = fopen(f_nome, "r");
    if (ficheiro == NULL) {
        printf("Erro a abrir %s.\n", f_nome);
        exit(0);
    }

    lista *lst_jogos = lista_nova();
    char jogo[MAX_LEN_STR];

    /* d) preencher a lista com a informação do ficheiro */
    while(fgets(jogo, MAX_LEN_STR, ficheiro)!=NULL) {
        lista_insere(lst_jogos, jogo);
    }

    fclose(ficheiro);

    printf("Foram carregados %d jogos:\n", lst_jogos->tamanho);
    lista_imprime(lst_jogos);
    printf("\n");

    /* f) ordenar a lista */
    lista_ordena(lst_jogos);
    printf("Lista ordenada:\n");
    lista_imprime(lst_jogos);
    printf("\n");

	/* i) pesquisar jogos PS2 e removê-los da lista */
    procura_remove(lst_jogos, "PS2", lst_jogos->inicio, LISTA_INICIO);

    printf("Após remoção de jogos PS2 a lista tem %d jogos.\n", lst_jogos->tamanho);
    lista_imprime(lst_jogos);
    printf("\n");

	lista_apaga(lst_jogos);

    return 0;
}

/*
 * Imprime os elementos de uma lista.
 *  > parâmetro 'lst': apontador para a lista
 */
void lista_imprime(lista *lst) {
    if (lst != NULL && lst->tamanho != 0) {
        l_elemento *l_elem = lst->inicio;
        for (int i = 0; i < lst->tamanho; i++) {
            printf("Pos %d -> %s\n", i, l_elem->str);
            l_elem = l_elem->proximo;
        }
    }
}

/*
 * Cria novo elemento.
 *  > parâmetro 'valor': string
 *  > retorno: apontador para o elemento criado ou NULL se ocorrer um erro
 */
l_elemento* novo_elemento(const char *valor) {
	// alocar memória para a estrutura l_elemento
	l_elemento *item = (l_elemento*)malloc(sizeof(l_elemento));
	if (item == NULL) return NULL;

	// alocar memória para string
    item->str = (char*)malloc((strlen(valor) + 1) * sizeof(char));
	if(item->str == NULL) {
		free(item);
		return NULL;
	}

	// copiar valor
	strcpy(item->str, valor);

	// item ainda não tem próximo
    item->proximo = NULL;
    item->anterior = NULL;

	return item;
}