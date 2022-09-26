// Para compilar: gcc -g -Wall ex1_2.c vetor.c -o ex1_2

#include "vetor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 1024

int main() {
    // 1. Criar um novo vetor vazio.
    vetor *arr=vetor_novo();
    
    // 2. Solicitar ao utilizador 5 strings para inserir no vetor.
    int i;
    char string[MAXSTR];
    printf("Insira o primeiro vetor:\n");
    for(i=0; i<5; i++) {
        printf("Insira a %dº string: ", i+1);
        fgets(string, MAXSTR, stdin);
        string[strlen(string)-1]='\0';
        vetor_insere(arr, string, i);
    }
    
    // 3. Imprimir o conteúdo do vetor.
    printf("\nConteudo do primeiro vetor:\n");
    for(i=0; i<5; i++) {
        printf("%s\n", vetor_elemento(arr, i));
    }
    
    /*
    // 4. Solicitar ao utilizador uma string; se essa string existir no vetor, apagar a string.
    printf("\nInsira uma string (para procurar no vetor e remover): ");
    fgets(string, MAXSTR, stdin);
    string[strlen(string)-1]='\0';
    int pos=vetor_pesquisa(arr, string);
    if(pos>=0) {
        printf("\nA string que inseriu foi encontrada no vetor e sera removida!\n");
        vetor_remove(arr, pos);
        printf("Vetor sem a string removida:\n");
    } else {
        printf("\nVetor:\n");
    }
    
    // 5. Imprimir o conteúdo do vetor
    for(i=0; i<vetor_tamanho(arr); i++) {
        printf("%s\n", vetor_elemento(arr, i));
    }
    
    // 6. Ordenar o vetor.
    vetor_ordena(arr);
    
    // 7. Imprimir o conteúdo do vetor.
    printf("\nPrimeiro vetor ordenado:\n");
    for(i=0; i<vetor_tamanho(arr); i++) {
        printf("%s\n", vetor_elemento(arr, i));
    }
    */

    // 8. concatenar 2 vetores
    vetor *arr2=vetor_novo();
    printf("\nInsira o segundo vetor:\n");
    for(i=0; i<5; i++) {
        printf("Insira a %dº string: ", i+1);
        fgets(string, MAXSTR, stdin);
        string[strlen(string)-1]='\0';
        vetor_insere(arr2, string, i);
    }

    vetor *concarr=vetor_concatena(arr, arr2);
    printf("\nVetores concatenados:\n");
    for(i=0; i<vetor_tamanho(concarr); i++) {
        printf("%s\n", vetor_elemento(concarr, i));
    }
    
    // 9. inverter elementos do vetor
    vetor_inverte(concarr);

    printf("\nVetor invertido:\n");
    for(i=0; i<vetor_tamanho(concarr); i++) {
        printf("%s\n", vetor_elemento(concarr, i));
    }


    //10. baralhar o vetor
    vetor *arr_baralhado=vetor_baralha(concarr);;
    
    printf("\nVetor baralhado:\n");
    for(i=0; i<vetor_tamanho(arr_baralhado); i++) {
        printf("%s\n", vetor_elemento(arr_baralhado, i));
    }
    

    return 0;
}