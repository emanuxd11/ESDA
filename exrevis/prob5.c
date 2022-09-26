#include <stdio.h>
#include <string.h>
#define STRMAX 100

void le_frase(char *frase, int tam) {
    fgets(frase, tam, stdin);
    frase[strlen(frase)-1]='\0';
}

void inverte(char *frase, char* fraseInvertida) {
    int i, j, comp=strlen(frase);
    for(i=0, j=comp-1; i<comp; i++, j--) {
        fraseInvertida[i]=frase[j];
    }
    fraseInvertida[i]='\0';
}

int main() {
    char frase[STRMAX], fraseInvertida[STRMAX];
    while(1) {
        printf("Insira uma frase: ");
        le_frase(frase, STRMAX);
        if(frase[0]=='.') break;
        inverte(frase, fraseInvertida);
        if(strcmp(frase, fraseInvertida)==0) {
            printf("A string e capicua!\n");
        } else {
            printf("A string nao e capicua :(\n");
        }
    }
}