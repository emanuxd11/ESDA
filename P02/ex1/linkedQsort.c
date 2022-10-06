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

int listQsort(lista *lst, l_elemento *left, l_elemento *right) {
    //Caso base. Uma lista com tamanho 0 ou 1 já se encontra ordenada.
    if(lst->tamanho<2) {
        return 0;
    }

    //Escolha do pivot através de um elemento aleatório.
    //Implementar através de mediana de 3 elementos quando
    //a função estiver a funcionar.
    srand(time(NULL));
    int ind_pivot=rand()%lst->tamanho, i;
    l_elemento *pivot=lst->inicio;
    for(pivot=lst->inicio, i=0; i<ind_pivot; pivot=pivot->proximo, i++);

    
}



int main() {
    lista *teste=lista_nova();

    char randstr[100]="";
    srand(time(NULL));

    for(int i=0; i<10; i++) {
        for(int j=0; j<10; j++) {
            randstr[j]=('a'+rand()%26);
        }
        lista_insere(teste, randstr);
    }

    lista_imprime(teste);
}