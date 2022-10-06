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
    grafo *g = (grafo*)malloc(sizeof(grafo));
    if(g==NULL) return NULL;
    g->nos = NULL;
    g->tamanho = 0;
    return g;
    
}  

no_grafo *no_novo(char *estacao, char *distrito)
{
    if(estacao==NULL || distrito == NULL) return NULL;

    no_grafo *novo = malloc(sizeof(no_grafo));
    novo->estacao = (char*)malloc(sizeof(char)*(strlen(estacao)+1));
    strcpy(novo->estacao,estacao);
    strcpy(novo->distrito,distrito);
    novo->tamanho=0;
    novo->anterior=NULL;
    novo->arestas = NULL;
    novo->p_acumulado = 0;

   return novo;
}


no_grafo *no_remove(grafo *g, char *estacao)
{
    if(g==NULL || estacao == NULL) return NULL;
    for(int i =0; i<g->tamanho; i++){
        if(strcmp(g->nos[i]->estacao,estacao)==0){
            no_grafo *novo = g->nos[i];
            if (novo==NULL) return NULL;
            int j;
            for(j=i;j<g->tamanho-1;j++){
                g->nos[j]=g->nos[j+1];
            }
            g->tamanho = g->tamanho - 1;
            g->nos = realloc(g->nos, g->tamanho * sizeof(no_grafo**));
            return novo;
        } 
    }
    return NULL;
}

int aresta_apaga(aresta_grafo *aresta)
{
    if(aresta==NULL) return -1;
    aresta->distancia = 0;
    aresta->inspecao = 0;
    free(aresta->codigo);
    free(aresta->linha);
    free(aresta);
    return 0;


}
int no_apaga(no_grafo *no)
{
    if(no==NULL) return -1;
    for(int i=0; i<no->tamanho;i++){
        if(aresta_apaga(no->arestas[i])==-1) return -1;
    }
    no->tamanho = 0;                     
    no->p_acumulado = 0;       
    free(no->estacao);
    free(no->arestas);
    free(no);
    return 0;
}


int grafo_apaga(grafo *g)
{
    if(g==NULL) return -1;

    for(int i = 0; i<g->tamanho;i++){
        if(no_apaga(g->nos[i])==-1) return -1;
    }
    g->tamanho = 0;
    free(g->nos);
    free(g);
    return 0;


}

int no_insere(grafo *g, no_grafo *no)
{
    if(g == NULL || no == NULL) return -1;
    for(int i=0; i<g->tamanho; i++){
        if(g->nos[i]==no) return 1;
    }
    g->tamanho = g->tamanho + 1;
    g->nos = realloc(g->nos, g->tamanho * sizeof(no_grafo**));
    g->nos[g->tamanho-1] = no;

    return 0;
}

int cria_aresta(no_grafo *origem, no_grafo *destino, char *codigo, char *linha, int distancia, int ano)
{
    if(origem == NULL || destino == NULL || codigo == NULL || linha == NULL || distancia < 0 || ano < 0){
        return -1;
    }

    int i;
    for(i=0; i< origem->tamanho; i++){
        if(strcmp(origem->arestas[i]->codigo,codigo)==0){
            return 1;
        }
    }

    
    aresta_grafo *novo = malloc(sizeof(aresta_grafo));

    if(novo==NULL) return -1;

    novo->codigo=malloc(sizeof(char)*(strlen(codigo)+1));
    strcpy(novo->codigo,codigo);
    novo->linha=malloc(sizeof(char)*(strlen(linha)+1));
    strcpy(novo->linha,linha);
    novo->destino = destino;
    novo->inspecao = ano;
    novo->destino = destino;
    origem->arestas = realloc(origem->arestas, (origem->tamanho +1)*sizeof(aresta_grafo**));
    
    origem->arestas[i] = novo;
    origem->tamanho++;

    return 0;

    
}
no_grafo **pesquisa_avancada(grafo *g, char *destino, int *n)
{
    if(g==NULL || destino == NULL || n == NULL) return NULL;

    no_grafo **vetor = malloc(g->tamanho * sizeof(no_grafo*));
    if(vetor==NULL) return NULL;
    *n = 0;
    int i,k;
    for(i=0; i<g->tamanho;i++){
        for(k=0; k<g->nos[i]->tamanho;k++){
            if(strcmp(g->nos[i]->arestas[k]->destino->estacao,destino)==0){
                vetor[*n] = g->nos[i];
                (*n)++;
            }
        }
    }
    vetor = realloc(vetor,(*n) * sizeof(no_grafo*));
    return vetor;
    

}

no_grafo **estacoes_distrito (grafo *g, char *distrito, int *n)
{
    if(g==NULL || distrito == NULL || n == NULL) return NULL;
    no_grafo **vetor = malloc((sizeof(no_grafo*)*g->tamanho));
    *n = 0;
    for(int i = 0; i<g->tamanho;i++){
        if(strcmp(g->nos[i]->distrito,distrito)==0){
            vetor[(*n)++] = g->nos[i];
        }
    }
    vetor = realloc(vetor,sizeof(no_grafo*)*(*n));
    return vetor;
    
}

no_grafo **estacoes_linha (grafo *g, char *estacao, char *linha, int *n)
{
   if(g==NULL || estacao == NULL || linha == NULL || n == NULL) return NULL;
   *n = 0;
   no_grafo *aux;
   aux = encontra_no(g,estacao);
   no_grafo **vetor = malloc(sizeof(no_grafo*)*g->tamanho);
   vetor[*n]=aux;
   (*n)++;
    for(int i = 0; i < g->tamanho; i++) {
        for(int j = 0; j < aux->tamanho; j++) {
            if(strcmp(aux->arestas[j]->linha, linha) != 0) continue;

            if(aux->arestas[j]->destino != vetor[(*n)-1]) {
                vetor[*n] = aux;
                (*n)++;
                aux = aux->arestas[j]->destino;
            }
       }
   }
    vetor = realloc(vetor, (*n) * sizeof(no_grafo*));
    return vetor; 
}

int metros_linha (grafo *g, char *linha, char *origem)
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
   
    return NULL;
}

no_grafo *encontra_no(grafo *g, char *estacao)
{
    if(g == NULL || estacao == NULL) return NULL;
    for(int i = 0; i<g->tamanho; i++){
        if(strcmp(g->nos[i]->estacao,estacao)==0) return g->nos[i];
    }
    return NULL;
}


no_grafo *encontra_troco(grafo *g, char *codigo, int *aresta_pos)
{
    if(g==NULL || codigo == NULL) return NULL;
    int pos1, pos2, encontrou_primeiro=0;
    char *est1, *est2;
    no_grafo *novo1, *novo2;


    for(int i=0; i<g->tamanho;i++){

        if(g->nos[i]==NULL) return NULL;

        for(int k=0; k < g->nos[i]->tamanho; k++){
            
            if(g->nos[i]->arestas[k]==NULL) return NULL;
            if(strcmp(g->nos[i]->arestas[k]->codigo,codigo)==0){
                
                if(encontrou_primeiro==0){
                    pos1 = k;
                    
                    est1 = g->nos[i]->estacao;
                    encontrou_primeiro=1;
                    novo1 = g->nos[i];
                }
                else{
                    pos2 = k;
                    
                    est2 = g->nos[i]->estacao;
                    novo2 = g->nos[i];
                }
            }
        }
    }
        
        if(strcmp(est1,est2)<0){
            *aresta_pos=pos1;
            return novo1;
        }
            *aresta_pos=pos2;
            return novo2;

    
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

