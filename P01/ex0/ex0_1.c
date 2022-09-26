// Para compilar: gcc -g -Wall ex0_1.c -o ex0_1

#include <stdio.h>
#include <stdlib.h>

void imprime_vetor(int *v, int n)
{
    for(int i = 0; i < n; i++)
        printf("%d ", v[i]);
}

int main()
{
    // (a) pede ao utilizador o número de elementos do vetor
    int num_elem;
    printf("Insira o numero de elementos do vetor: ");
    scanf("%d", &num_elem);
    
    // (b) cria um vetor de forma dinâmica (dica: calloc)
    int *arr=(int*)calloc(num_elem, sizeof(int));
    
    // (c) pede ao utilizador números inteiros e preenche o vetor com os mesmos    
    int i;
    for(i=0; i<num_elem; i++) {
        printf("Insira o %dº elemento: ", i+1);
        scanf("%d", &arr[i]);
    }    
    
    // (d) no final chama a função imprime_vetor que te é fornecida
    imprime_vetor(arr, num_elem);
    
    return 0;
}
