#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "bst.h"
#include "avl.h"

#define MAX_STR 100

int main() {
    char linha[MAX_STR], *pais;
    FILE *f = fopen("cidades.txt", "r");
    arvore_avl *arvore = avl_nova();

    int i = 0; 
    while(fgets(linha, MAX_STR, f) != NULL ) {
        strtok(linha, ",");
        pais = strtok(NULL, ",");
        pais[strlen(pais)-1] = '\0';
        avl_insere(arvore, pais);
        i++;
    }

    printf("Portugal - %d\n", avl_pesquisa(arvore, "Portugal")->cont);
    printf("Spain - %d\n", avl_pesquisa(arvore, "Spain")->cont);
    printf("Russia - %d\n", avl_pesquisa(arvore, "Russia")->cont);

    avl_apaga(arvore);
    fclose(f);

    return 0;
}