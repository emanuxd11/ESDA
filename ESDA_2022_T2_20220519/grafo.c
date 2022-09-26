/*****************************************************************/
/*   Grafo direcionado | ESDA | L.EEC | 2021/22      */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "grafo.h"
#include "heap.h"


grafo *grafo_novo()
{
    grafo *ret = malloc(sizeof(grafo));
    if(ret == NULL) return NULL;

    ret->tamanho = 0;
    ret->nos = NULL;

    return ret;
}

no_grafo *no_novo(char *estacao, char *distrito)
{
    if(estacao == NULL || distrito == NULL || strlen(distrito)+1 > 30) return NULL;

    no_grafo *ret = malloc(sizeof(no_grafo));
    if(ret == NULL) return NULL;

    ret->estacao = malloc((strlen(estacao)+1) * sizeof(char));
    strcpy(ret->estacao, estacao);

    strcpy(ret->distrito, distrito);
    ret->anterior = NULL;
    ret->arestas = NULL;
    ret->p_acumulado = 0;
    ret->tamanho = 0;
    
    return ret;
    return NULL;
}


no_grafo *no_remove(grafo *g, char *estacao)
{
    if(g == NULL || estacao == NULL) return NULL;

    for(int i = 0; i < g->tamanho; i++) {
        if(strcmp(g->nos[i]->estacao, estacao) == 0) {

            no_grafo *ret = g->nos[i];
            for(int j = i; j < g->tamanho-1; j++) {
                g->nos[j] = g->nos[j+1];
            }
            g->tamanho--;
            g->nos = realloc(g->nos, g->tamanho * sizeof(no_grafo**));

            return ret;
        }
    }
    
    return NULL;
}

int aresta_apaga(aresta_grafo *aresta)
{
    if(aresta == NULL) return -1;
    
    free(aresta->codigo);
    free(aresta->linha);
    free(aresta);

    return 0;
}

int no_apaga(no_grafo *no)
{
    if(no == NULL) return -1;

    for(int i = 0; i < no->tamanho; i++) {
        if(aresta_apaga(no->arestas[i]) == -1) return -1;
    }

    no->tamanho = 0;
    no->p_acumulado = 0;
    free(no->arestas);
    free(no->estacao);
    free(no);

    return 0;
}


int grafo_apaga(grafo *g)
{
    if(g == NULL) return -1;

    for(int i = 0; i < g->tamanho; i++) {
        if(no_apaga(g->nos[i]) == -1) return -1;
    }

    g->tamanho = 0;
    free(g->nos);
    free(g);

    return 0;
}

int no_insere(grafo *g, no_grafo *no)
{   
    if(g == NULL || no == NULL) return -1;

    int i;
    for(i = 0; i < g->tamanho; i++) {
        if(g->nos[i] == NULL) return -1;
            
        if(strcmp(g->nos[i]->estacao, no->estacao) == 0) return 1;
    }

    g->nos = realloc(g->nos, (g->tamanho+1) * sizeof(no_grafo**));
    g->nos[g->tamanho] = no;
    g->tamanho++;

    return 0;
}

int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *linha, int distancia, int ano)
{
    if(origem == NULL || destino == NULL || codigo == NULL || linha == NULL || distancia < 0 || ano < 0) { 
        return -1;
    }

    aresta_grafo *aresta = malloc(sizeof(aresta_grafo));
    if(aresta == NULL) return -1;
    
    aresta->codigo = malloc((strlen(codigo)+1) * sizeof(char));
    aresta->linha = malloc((strlen(linha)+1) * sizeof(char));
    strcpy(aresta->codigo, codigo);
    strcpy(aresta->linha, linha);

    aresta->destino = destino;
    aresta->distancia = distancia;
    aresta->inspecao = ano;

    int i;
    for(i = 0; i < origem->tamanho; i++) {
        if(origem->arestas[i] == NULL) return -1;

        if(strcmp(origem->arestas[i]->codigo, aresta->codigo) == 0) {
            aresta_apaga(aresta);
            return 1;
        }
    }

    origem->arestas = realloc(origem->arestas, (origem->tamanho+1) * sizeof(aresta_grafo**));
    origem->arestas[origem->tamanho] = aresta;
    origem->tamanho++;

    return 0;
}

no_grafo **pesquisa_avancada(grafo *g, char *destino, int *n)
{   
    if(g == NULL || destino == NULL || n == NULL);

    no_grafo **ret = malloc(g->tamanho * sizeof(no_grafo*));
    if(ret == NULL) return NULL;

    int i, j;
    *n = 0;
    for(i = 0; i < g->tamanho; i++) {
        for(j = 0; j < g->nos[i]->tamanho; j++) {
            if(strcmp(g->nos[i]->arestas[j]->destino->estacao, destino) == 0) {
                ret[*n] = g->nos[i];
                (*n)++;
            }
        }
    }

    ret = realloc(ret, (*n) * sizeof(no_grafo*));
    return ret;
}

no_grafo **estacoes_distrito (grafo *g, char *distrito, int *n)
{
    if(g == NULL || distrito == NULL || n == NULL) return NULL;
    
    no_grafo **ret = malloc((g->tamanho * sizeof(no_grafo*)));
    if(ret == NULL) return NULL;

    *n = 0;
    for(int i = 0; i < g->tamanho; i++) {
        if(g->nos[i] == NULL) return NULL;
            
        if(strcmp(g->nos[i]->distrito, distrito) == 0) {
            ret[*n] = g->nos[i];
            (*n)++;
        }
    }

    ret = realloc(ret, (*n) * sizeof(no_grafo*));
    return ret;
}

no_grafo **estacoes_linha (grafo *g, char *estacao, char *linha, int *n)
{
    if(g == NULL || estacao == NULL || n == NULL) return NULL;

    no_grafo *no_aux = encontra_no(g, estacao);
    if(no_aux == NULL) return NULL;

    no_grafo **ret = malloc((g->tamanho * sizeof(no_grafo*)));
    if(ret == NULL) return NULL;

    int i, j;
    *n = 0;
    ret[*n] = no_aux;
    (*n)++;
    for(i = 0; i < g->tamanho; i++) {
        for(j = 0; j < no_aux->tamanho; j++) {
            if(strcmp(no_aux->arestas[j]->linha, linha) != 0) continue;

            if(*n > 0 && no_aux->arestas[j]->destino != ret[(*n)-1]) {
                ret[*n] = no_aux;
                (*n)++;
                no_aux = no_aux->arestas[j]->destino;
            }
        }
    }

    ret = realloc(ret, (*n) * sizeof(no_grafo*));
    return ret;
}

int metros_linha(grafo *g, char *linha, char *origem)
{
    if(g == NULL || linha == NULL || origem == NULL) return -1;

    int tam = 0, ret = 0;
    no_grafo **estacoes = estacoes_linha(g, origem, linha, &tam);

    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < estacoes[i]->tamanho; j++) {
            if(strcmp(estacoes[i]->arestas[j]->linha, linha) == 0) {
                
                if(i > 0 && estacoes[i]->arestas[j]->destino != estacoes[i-1]) {
                    ret += estacoes[i]->arestas[j]->distancia;
                }
                
            }
        }
    }

    free(estacoes);
    return ret;
}


no_grafo **trajeto_mais_rapido(grafo *g, char *origem, char *destino, int *n)
{
    if(g == NULL || origem == NULL || destino == NULL || n == NULL) return NULL;

    no_grafo **ret = malloc(g->tamanho * sizeof(no_grafo*));
    if(ret == NULL) return NULL;

    heap *fila_p = heap_nova(g->tamanho), *fila_aux;
    if(fila_p == NULL) {
        free(ret);
        return NULL;
    }

    no_grafo *no_atual, **vet_cantos;
    int tam, dist = 0;
    *n = 0;

    for(int i = 0; i < g->tamanho; i++) {
        if(strcmp(g->nos[i]->estacao, destino) == 0) {
            g->nos[i]->p_acumulado = 0;
        } else {
            g->nos[i]->p_acumulado = 9999*1000;
        }

        g->nos[i]->anterior = NULL;

        if(!heap_insere(fila_p, g->nos[i], NULL, g->nos[i]->p_acumulado)) {
            free(ret);
            heap_apaga(fila_p);
            return NULL;
        }
    }

    while(fila_p->tamanho > 0) {
        no_atual = heap_remove(fila_p);
        vet_cantos = pesquisa_avancada(g, no_atual->estacao, &tam);

        if(vet_cantos == NULL) continue;

        for(int i = 0; i < tam; i++) {
            for(int j = 0; j < vet_cantos[i]->tamanho; j++) {
                if(no_atual == vet_cantos[i]->arestas[j]->destino) {
                    dist = vet_cantos[i]->arestas[j]->distancia;
                    break;
                }
            }

            if(vet_cantos[i]->p_acumulado > no_atual->p_acumulado + dist) {
                //Atualizar o peso acumulado do nó
                vet_cantos[i]->p_acumulado = no_atual->p_acumulado + dist;
                vet_cantos[i]->anterior = no_atual;

                //Procurar o nó na fila de prioridade e alterar a sua prioridade
                for(int j = 1; j <= fila_p->tamanho; j++) {
                    if(vet_cantos[i] != fila_p->elementos[j]->no) continue;

                    fila_p->elementos[j]->prioridade = vet_cantos[i]->p_acumulado;
                    
                    //Ajustar heap para refletir mudança na prioridade
                    fila_aux = heap_nova(fila_p->tamanho);
                    if(fila_aux == NULL) return NULL;

                    for(int k = 1; k <= fila_p->tamanho; k++) {
                        heap_insere(fila_aux, fila_p->elementos[k]->no, NULL, fila_p->elementos[k]->no->p_acumulado);
                    }
                    heap_apaga(fila_p);
                    fila_p = fila_aux;
                    
                    break;
                }
            }
        }

        free(vet_cantos);
    }

    for(no_atual = encontra_no(g, origem); no_atual != NULL; no_atual = no_atual->anterior) {
        ret[*n] = no_atual;
        (*n)++;
    }

    heap_apaga(fila_p);
    
    ret = realloc(ret, (*n) * sizeof(no_grafo*));
    if(ret == NULL) return NULL;

    return ret;
}


no_grafo *encontra_no(grafo *g, char *estacao)
{
    if(g == NULL || estacao == NULL) return NULL;

    for(int i = 0; i < g->tamanho; i++) {
        if(g->nos[i] != NULL) {
            if(strcmp(g->nos[i]->estacao, estacao) == 0) {
                return g->nos[i];
            }
        }
    }

    return NULL;
}


no_grafo *encontra_troco(grafo *g, char *codigo, int *aresta_pos)
{
    if(g == NULL || codigo == NULL) return NULL;

    for(int i = 0; i < g->tamanho; i++) {
        for(int j = 0; j < g->nos[i]->tamanho; j++) {
            if(strcmp(codigo, g->nos[i]->arestas[j]->codigo) == 0) {
                (*aresta_pos) = j;
                return g->nos[i];
            }
        }
    }

    return NULL;
}

grafo *grafo_importa(const char *nome_ficheiro)
{
    if (nome_ficheiro == NULL)
        return NULL;

    FILE *f = fopen(nome_ficheiro, "r");
    if (f == NULL)
        return NULL;

    grafo *g = grafo_novo();
    if (g == NULL)
    {
        fclose(f);
        return NULL;
    }
    char str[500] = {0}, codigo[15] = {0}, origem[50] = {0}, destino[50] = {0}, linha[40] = {0}, distritoorigem[40], distritodestino[40];
    int distancia = 0;
    int ano=0;
    int existearesta=0;
    

    char *token;
    no_grafo *no_origem, *no_destino;
    int ret;
    while (fgets(str, 500 * sizeof(char), f) != NULL)
    {
        str[strlen(str) - 1] = '\0';

        token = strtok(str, ";");
        if (!token)
            break;
        strcpy(codigo, token);
   
        token = strtok(NULL, ";");
        strcpy(linha, token);

        token = strtok(NULL, ";");
        strcpy(origem, token);

        token = strtok(NULL, ";");
        strcpy(distritoorigem, token);

        token = strtok(NULL, ";");
        strcpy(destino, token);

        token = strtok(NULL, ";");
        strcpy(distritodestino, token);
   
        token = strtok(NULL, ";");
        distancia = atoi(token);


        token = strtok(NULL, ";");
        ano = atoi(token);
      
      //  printf("%s - %s - %s -%s - %s -%s -%d -%d",codigo,linha,origem,distritoorigem,destino,distritodestino,distancia,ano);
        // procura no grafo um nó com o nome da origem
        no_origem = encontra_no(g, origem);
        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_origem)
        {
           no_origem = no_novo(origem,distritoorigem);
       

            if (no_insere(g, no_origem)==-1)
            {
                fclose(f);

                return NULL;
            }
        }
        // procura no grafo um nó com o nome do destino
        no_destino = encontra_no(g, destino);

        // se o nó ainda não existe, cria-o e insere-o no grafo
        if (!no_destino)
        {
           
           no_destino = no_novo(destino,distritodestino);
        

            if (no_insere(g, no_destino)==-1)
            {
                fclose(f);

                return NULL;
            }
        }


    
    existearesta=0;
    //pesquisa em todas as arestas se existe
    for (int i = 0; i < no_origem->tamanho; i++)
    {

        if ((no_origem->arestas[i]->destino == no_destino) && ((strcmp(no_origem->arestas[i]->codigo, codigo) == 0)))
            existearesta=1;
    }
        if (existearesta == 0)
        {
            
            ret = cria_aresta(no_origem, no_destino, codigo, linha,distancia,ano);

            if (ret == -1)
            {
                fclose(f);

                return NULL;
            }
             ret = cria_aresta(no_destino,no_origem, codigo, linha,distancia,ano);

            if (ret == -1)
            {
                fclose(f);

                return NULL;
            }
        }
    }

    fclose(f);
    return g;
}

