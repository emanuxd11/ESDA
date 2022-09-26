#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "componentes.h"

/*** Para compilar: gcc -g -Wall componentes.c armazem-teste.c -o teste ***/

/* VERIFICACOES IMPLEMENTADAS */
int verifica_compra_pop(fatura **f)
{
    int er = 0;
    compra *c = cria_compra(*f);

    if (c == NULL)
    {
        printf("...verifica_compra_pop: falhou criacao da compra (ERRO)\n");
        return 1;
    }
    else
    {
        int n_prc = 3;
        parcela **vec_parcelas_rmv = (parcela**)malloc(n_prc * sizeof(parcela*));
        for (int i = 0; i < n_prc; i++) vec_parcelas_rmv[i] = compra_pop(c);
        for (int i = 0; i < n_prc; i++) {
            if (vec_parcelas_rmv[i] == NULL) {
                printf("...verifica_compra_pop: falhou remocao de parcela (ERRO)\n");
                er++;
            }
        }
        int tam = c->tamanho;
        if (tam != 4)
        {
            printf("...verifica_compra_pop: numero de parcelas da compra (= %d) e' diferente do esperado (= 4) (ERRO)\n", tam);
            er++;
        }
        else {
            printf("...verifica_compra_pop: numero de parcelas da compra coincide com o esperado (= 4) (ok)\n");
    
            if (strcmp(c->raiz->ID, "con009210") != 0 || strcmp(c->raiz->proximo->proximo->proximo->ID, "con008190") != 0)
            {
                printf("...verifica_compra_pop: IDs da 1ª (= %s) e 'ultima (= %s) parcelas da compra diferem do esperado (con009210 e con008190) (ERRO)\n", c->raiz->ID, c->raiz->proximo->proximo->proximo->ID);
                er++;
            }
            else
                printf("...verifica_compra_pop: IDs da 1ª e 'ultima parcelas da compra coincidem com o esperado (con009210 e con008190) (ok)\n");
        }
        if (strcmp(vec_parcelas_rmv[1]->ID, "cir000150") != 0)
        {
            printf("...verifica_compra_pop: ID da segunda parcela removida (= %s) da compra difere do esperado (cir000150) (ERRO)\n", c->raiz->ID);
            er++;
        }
        else
            printf("...verifica_compra_pop: IDs da segunda parcela removida coincide com o esperado (cir000150) (ok)\n");
        if (c->raiz->quantidade != 100)
        {
            printf("...verifica_compra_pop: quantidade da parcela no topo (= %d) e' diferente do esperado (= 100) (ERRO)\n", c->raiz->quantidade);
            er++;
        }
        else
            printf("...verifica_compra_pop: quantidade da parcela no topo coincide com o esperado (= 100) (ok)\n");

        for (int i = 0; i < n_prc; i++) parcela_apaga(vec_parcelas_rmv[i]);
        free(vec_parcelas_rmv);
    }

    compra_apaga(c);
    return er;
}

int main()
{
    int errorCount = 0, error;

    char ficheiro1[] = "db_small.txt";
    char ficheiro2[] = "lista_de_compras.txt";
    
    armazem *a = armazem_importa(ficheiro1);
    fatura *f = cria_fatura(a, ficheiro2);

    printf("INICIO DOS TESTES\n\n");

    error = verifica_compra_pop(&f);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_compra_pop\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_compra_pop passou\n\n");
    }
    
    armazem_apaga(a);
    fatura_apaga(f);

    if (errorCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errorCount);

    return 0;
}