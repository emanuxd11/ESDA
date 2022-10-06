#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "componentes.h"

/*** Para compilar: gcc -g -Wall componentes.c armazem-teste.c -o teste ***/

/* VERIFICACOES IMPLEMENTADAS */
int verifica_parcela_remove (fatura **f){
    int er = 0;

    parcela *p;
    p = parcela_remove(*f, "parcela");
    if (p)
    {
        printf("...verifica_parcela_remove (teste de parcela inexistente): removeu uma parcela inexistente (ERRO)\n");
        er++;
    }
    else
        printf("...verifica_parcela_remove (teste de parcela inexistente): nao removeu nenhuma parcela (ok)\n");
    parcela_apaga(p);

    p = parcela_remove(*f, "con007290");
    if (!p)
    {
        printf("...verifica_parcela_remove (teste de parcela valida no inicio): nao removeu (ERRO)\n");
        er++;
    }
    else if (strcmp(p->ID, "con007290") != 0)
    {
        printf("...verifica_parcela_remove (teste de componente valida no inicio): removeu uma parcela errada (%s) (ERRO)\n",p->ID);
        er++;
    }
    else if((*f)->n_parcelas != 2){
        printf("...verifica_parcela_remove (teste de componente valida no inicio): o numero de parcelas da fatura (%d) é diferente do esperado (2)\n",(*f)->n_parcelas);
        er++;
    }
    else if (strcmp((*f)->inicio->ID,"con007350") != 0){
        printf("...verifica_parcela_remove (teste de componente valida no inicio): o inicio da fatura (%s) é diferente do esperado (con007350)\n",(*f)->inicio->ID);
        er++;
    }
    else
    {
        printf("...verifica_parcela_remove (teste de componente valida no inicio): removeu com sucesso (ok)\n");
    }
    parcela_apaga(p);

    p = parcela_remove(*f, "tra012720");
    if (!p)
    {
        printf("...verifica_parcela_remove (teste de parcela valida no fim): nao removeu (ERRO)\n");
        er++;
    }
    else if (strcmp(p->ID, "tra012720") != 0)
    {
        printf("...verifica_parcela_remove (teste de componente valida no fim): removeu uma parcela errada (%s) (ERRO)\n",p->ID);
        er++;
    }
    else if((*f)->n_parcelas != 1){
        printf("...verifica_parcela_remove (teste de componente valida no fim): o numero de parcelas da fatura (%d) é diferente do esperado (1)\n",(*f)->n_parcelas);
        er++;
    }
    else if (strcmp((*f)->inicio->ID,"con007350") != 0){
        printf("...verifica_parcela_remove (teste de componente valida no fim): o inicio da fatura (%s) é diferente do esperado (con007350)\n",(*f)->inicio->ID);
        er++;
    }
    else if ((*f)->inicio->proximo){
        printf("...verifica_parcela_remove (teste de componente no fim): o fim da fatura (%s) é diferente do esperado (null)\n",(*f)->inicio->proximo->ID);
        er++;
    }
    else
    {
        printf("...verifica_parcela_remove (teste de componente valida no fim): removeu com sucesso (ok)\n");
    }
    parcela_apaga(p);

    return er;
}

int main()
{
    int errorCount = 0, error;

    char ficheiro[] = "db_small.txt";
    
    armazem *a = armazem_importa(ficheiro);
    fatura *f = fatura_nova();
    parcela *p1 = parcela_nova("con007290", 5, 1.34);
    parcela *p2 = parcela_nova("con007350", 10, 3.12);
    parcela *p3 = parcela_nova("tra012720", 20, 1.20);
    insere_parcela_fatura(f, p1);
    insere_parcela_fatura(f, p2);
    insere_parcela_fatura(f, p3);

    printf("INICIO DOS TESTES\n\n");
    
    error = verifica_parcela_remove(&f);
    if (error)
    {
        printf("ERRO: %d erros encontrados em verifica_parcela_remove\n\n", error);
        errorCount += error;
    }
    else
    {
        printf("OK: verifica_parcela_remove passou\n\n");
    }

    armazem_apaga(a);
    fatura_apaga(f);

    if (errorCount == 0)
        printf("FIM DOS TESTES: Todos os testes passaram\n");
    else
        printf("FIM DOS TESTES: Foram encontrados %d ERROS no total\n", errorCount);

    return 0;
}