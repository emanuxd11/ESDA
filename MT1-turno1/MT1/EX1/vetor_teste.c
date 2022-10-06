#include <stdio.h>
#include <string.h>
#include "vetor.h"

vetor *vetor_teste(char *s1, char *s2, char *s3)
{
    vetor *ret = vetor_novo();
    
    vetor_insere(ret, s1, ret->tamanho);
    vetor_insere(ret, s2, ret->tamanho);
    vetor_insere(ret, s3, ret->tamanho);

    return ret;
}

int main()
{
    vetor *vec = vetor_teste("mini", "teste", "ESDA");

    printf("---------\n");
    printf("Esperado:\n");
    printf("tamanho do vetor: 3\n");
    printf("Vetor: [ mini, teste, ESDA, ]\n");

    printf("---------\n");
    printf("Obtido:\n");
    vetor_imprime(vec);

    return 0; 
}
