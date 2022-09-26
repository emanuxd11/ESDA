#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LISTA_INICIO 0
#define LISTA_FIM 1

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

//imprime a lista
void lista_imprime(lista *lst) {
    if (lst != NULL && lst->tamanho != 0) {
        l_elemento *l_elem = lst->inicio;
        for (int i = 0; i < lst->tamanho; i++) {
            printf("Pos %d -> %s\n", i, l_elem->str);
            l_elem = l_elem->proximo;
        }
    }
}

//cria um novo elemento da lista
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

//cria nova lista vazia 
lista* lista_nova() {
    lista *res=malloc(sizeof(lista));
    if(res==NULL) {
        return NULL;
    }
    
    res->inicio=NULL;
    res->fim=NULL;
    res->tamanho=0;

    return res;
}

//inserir elemento no fim da lista
l_elemento* lista_insere(lista *lst, const char *str) {
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

//apaga uma lista
void lista_apaga(lista *lst) {
    if(lst==NULL) {
        return;
    }

    l_elemento *aux;

    while(lst->inicio!=NULL) {
        aux=lst->inicio;
        lst->inicio=lst->inicio->proximo;
        free(aux->str);
        free(aux);
    }

    lst->tamanho=0;
    free(lst);
}

//ordenar lista por ordem alfabética
int lista_ordena(lista *lst) {
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

//remover elemento da lista
l_elemento* lista_remove(lista *lst, l_elemento *pos) {
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

//pesquisar um elemento da lista
l_elemento* lista_pesquisa(lista *lst, const char *str, l_elemento *init, int sentido) {
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

    //se não encontrar num sentido, faz com que pesquise no outro até encontrar:

    /*while(!encontrado) {
        while(sentido>0 ? elem->proximo!=NULL : elem->anterior!=NULL) {
            if(strcmp(elem->str, str)==0) {
                encontrado=1;
                break;
            }

            elem=sentido>0 ? elem->proximo : elem->anterior;
        }
        sentido*=-1;
    }*/
    
    //assumindo que a lista é ordenada, pode também
    //trocar-se o sentido imediatamente, caso necessário:

    //afinal, não era necessário fazer isto
    //o prof. disse para manter o sentido

    /*if(sentido*strcmp(init->str, str)>0) {
        sentido*=-1;
    }*/

    while(sentido==LISTA_INICIO ? elem->proximo!=NULL : elem->anterior!=NULL) {
        if(strstr(elem->str, str)!=NULL) {
            encontrado=1;
            break;
        }

        elem=sentido==LISTA_INICIO ? elem->proximo : elem->anterior;
    }

    return encontrado==1 ? elem : NULL;
}

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
    //criar lista vazia 
    lista *teste=lista_nova();

    //imprimir lista sem nenhum elemento
    printf("Primeira impressao, sem inserir nada:\n");
    lista_imprime(teste);

    //inserir um elemento na lista
    /*lista_insere(teste, "h");
    printf("\nApos ter inserido uma string:\n");
    lista_imprime(teste);*/

    //inserir mais elementos na lista
    char randstr[100]="";
    srand(time(NULL));

    for(int i=0; i<100; i++) {
        for(int j=0; j<90; j++) {
            randstr[j]=('a'+rand()%26);
        }
        lista_insere(teste, randstr);
    }

    printf("\nApos inserir varias strings:\n");
    lista_imprime(teste);

    //apagar lista (penso que funciona)
    /*lista_apaga(teste);
    printf("\nLista apagada:\n");
    lista_imprime(teste);*/

    //ordenar lista
    lista_ordena(teste);
    printf("\nLista ordenada:\n");
    lista_imprime(teste);

    //remover elemento
    lista_remove(teste, teste->inicio);
    printf("\nLista com um item removido:\n");
    lista_imprime(teste);

    //imprimir elemento encontrado pela pesquisa
    l_elemento *elemPesquisa=lista_pesquisa(teste, "g", teste->inicio, LISTA_INICIO);
    if(elemPesquisa==NULL) {
        printf("\nElemento nao encontrado!\n");
    } else {
        printf("\nElemento encontrado: %s\n", elemPesquisa->str);
    }
}