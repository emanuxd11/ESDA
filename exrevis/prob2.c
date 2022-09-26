#include <stdio.h>
#define MAX 5

void preenche_vetor(int v[], int n) {
    int i;
    for(i=0; i<n; i++) {
        printf("Insira a %dº posicao: ", i+1);
        scanf("%d", &v[i]);
    }
}

int pode_copiar(int num, int arr[], int n_elem) {
    //retorna 1 se não encontrar, 0 se encontrar
    int i;
    for(i=0; i<n_elem; i++) {
        if(num==arr[i]) {
            return 0;
        }
    }
    if(i==n_elem) {
        return 1;
    }
}

int main() {
    int i, j, n_elem=0, arr1[MAX], arr2[MAX], arraux[MAX];

    puts("Vetor 1:");
    preenche_vetor(arr1, MAX);
    puts("Vetor 2: ");
    preenche_vetor(arr2, MAX);

    for(i=0; i<MAX; i++) {
        for(j=0; j<MAX; j++) {
            if(arr1[i]==arr2[j]) {
                if(n_elem!=0 && pode_copiar(arr1[i], arraux, n_elem)) {
                    arraux[n_elem++]=arr1[i];
                } else if(n_elem==0) {
                    arraux[n_elem++]=arr1[i];
                }
            }
        }
    }

    printf("Comuns: ");
    for(i=0; i<n_elem; i++) {
        printf("%d ", arraux[i]);
    }
}