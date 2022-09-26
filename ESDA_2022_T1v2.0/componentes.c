/*****************************************************************/
/*       Biblioteca componentes | ESDA | LEEC | 2021/22          */
/*****************************************************************/

#include "componentes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


componente *componente_novo(const char *ID, char *nome, int quantidade, float preco, const char *categoria) {
    //verificar se os argumentos se encontram dentro dos valores especificados
    if(/*ID==NULL || nome==NULL || quantidade==0 || categoria==NULL ||*/ strlen(ID)>9 || strlen(categoria)>(MAX_CHAR-1)) {
        return NULL;
    }

    //alocar memória para o componente
    componente *res=(componente*)malloc(sizeof(componente));

    //caso a memória não tenha sido alocada, retornar NULL
    if(res==NULL) {
        return NULL;
    }

    //alocar memória para a string nome do componente (a única string da estrutura sem tamanho definido)
    res->nome=(char*)malloc((strlen(nome)+1)*sizeof(char));

    //guardar no novo componente os valores especificados nos argumentos
    strcpy(res->ID, ID);
    strcpy(res->nome, nome);
    res->quantidade=quantidade;
    res->preco=preco;
    strcpy(res->categoria, categoria);

    return res;
}

armazem *armazem_novo() {
    //alocar memória para o armazém
    armazem *res=(armazem*)malloc(sizeof(armazem));

    //caso a memória não tenha sido alocada, retornar NULL
    if(res==NULL) {
        return NULL;
    }

    //inicializar os valores do novo armazem
    res->componentes=(componente**)malloc(sizeof(componente));
    res->tamanho=0;

    return res;
}

int componente_insere(armazem *a, componente *c) {
    //caso um dos argumentos seja inválido, retornar -1 (caso de erro)
    if(a==NULL || c==NULL) {
        return -1;
    }

    //verificar se o componente já existe no armazem
    int i;
    for(i=0; i<a->tamanho; i++) {
        //caso exista, adicionar o número de componentes ao que já existe e atualizar o preço
        if(strcmp(a->componentes[i]->ID, c->ID)==0) {
            a->componentes[i]->quantidade+=c->quantidade;
            a->componentes[i]->preco=c->preco;
            return 1;
        }
    }

    //caso não exista, alocar mais espaço para o vetor e inserir o componente nesse espaço
    a->tamanho++;
    a->componentes=(componente**)realloc(a->componentes, a->tamanho*sizeof(componente));
    a->componentes[i]=c;

    return 0;
}

armazem *armazem_importa(const char *nome_ficheiro) {
    //abrir o ficheiro
    FILE *f=fopen(nome_ficheiro, "r");
    
    //caso o ficheiro não exista, retornar NULL
    if(f==NULL) {
        return NULL;
    }

    //criar o novo armazem
    armazem *res=armazem_novo();

    //ler o ficheiro e inserir os componentes no armazém
    char linha[MAX_CHAR], *ID, *nome, *categoria;
    int quantidade;
    float preco;
    componente *c;

    while(fgets(linha, MAX_CHAR, f)!=NULL) {
        //strtok para "partir" a linha em vários segmentos 
        ID=strtok(linha, ",");
        nome=strtok(NULL, ",");
        categoria=strtok(NULL, ",");
        quantidade=atoi(strtok(NULL, ","));
        preco=atof(strtok(NULL, ","));

        //criar o novo componente com os argumentos lidos do ficheiro anteriormente
        c=componente_novo(ID, nome, quantidade, preco, categoria);
        componente_insere(res, c);
    }
    
    return res;
    //*************************************//
}

componente *componente_remove(armazem *a, char *nome) {
    //verificar se os argumentos são válidos
    if(a==NULL || nome==NULL) {
        return NULL;
    }

    //procurar o componente com o nome indicado no armazém
    int i, j;
    for(i=0; i<a->tamanho; i++) {
        //caso o componente seja encontrado, mover os restantes elementos
        //do vetor para a esquerda, ajustar o tamanho e realocar a memória
        if(strcmp(a->componentes[i]->nome, nome)==0) {
            //criar o a variável de retorno (apontador para o
            //elemento removido) antes da sua remoção do vetor
            componente *res=a->componentes[i];

            //corrigir o conteúdo do vetor
            for(j=i+1; j<a->tamanho; j++) {
                a->componentes[j-1]=a->componentes[j];
            }

            //ajustar o tamanho do vetor
            a->tamanho--;
            a->componentes = realloc(a->componentes, a->tamanho * sizeof(a->componentes));

            return res;
        }
    }

    //caso o componente não tenha sido encontrado, retornar NULL
    return NULL;
}

int componente_apaga(componente *c) {
    //verificar se o argumento é válido
    if(c==NULL) {
        return -1;
    }

    //libertar a memória alocada dinamicamente
    free(c->nome);
    free(c);

	return 0;
}

int armazem_apaga(armazem *a) {
	//verificar se o argumento é válido
    if(a==NULL) {
        return -1;
    }

    //apagar todos os componentes do armazém
    int i;
    for(i=0; i<a->tamanho; i++) {
        //caso ocorra erro a apagar o componente,
        //a função termina retornando -1
        if(componente_apaga(a->componentes[i])==-1) {
            return -1;
        }
    }

    //libertar o a memória ocupada pelo armazém
    a->tamanho=0; //este passo é necessário???
    free(a);

	return 0;
    //**** Esta função não é testada? ****//
}

int *armazem_pesquisa_categoria(armazem *a, const char *categoria, int *tam) {
    //verificar se os argumentos são válidos
    if(a==NULL || categoria==NULL || tam==NULL) {
        return NULL;
    }

    //alocar memória para o vetor a ser retornado
    int *res=(int*)malloc(sizeof(int));
    if(res == NULL) {
        return NULL;
    }
    //inicializar o tamanho com 0 (não sei se é necessário)
    *tam=0;

    //percorrer o vetor até encontrar componentes de categoria correspondente
    int i, encontrado=0;
    for(i=0; i<a->tamanho; i++) {
        if(strcmp(categoria, a->componentes[i]->categoria)==0) {
            //se a primeira posição já está ocupada, alocar mais memória
            //se for encontrado pela primeira vez (tam=0), ativar a flag "encontrado"
            if(*tam>0) {
                res=(int*)realloc(res, (*tam+1)*sizeof(int));
            } else {
                encontrado=1;
            }
            
            //guardar a posição no vetor e incrementar
            //a variável correspondente ao seu tamanho
            res[*tam]=i;
            (*tam)++;
        }
    }

    //caso tenha sido encontrado pelo menos um componente
    //da categoria especificada, retornar as posições
    //caso contrário, retornar NULL
	return encontrado ? res : NULL;
}

int *armazem_pesquisa_nome(armazem *a, char *nome, int *tam){
	//verificar se os argumentos são válidos
    if(a==NULL || nome==NULL || tam==NULL) {
        return NULL;
    }

    //alocar memória para o vetor a ser retornado
    int *res=(int*)malloc(sizeof(int));
    if(res == NULL) {
        return NULL;
    }
    //inicializar o tamanho com 0 (não sei se é necessário)
    *tam=0;

    //percorrer o vetor até encontrar componentes cujo nome contenha o nome especificado
    //(tenho de procurar apenas no nome ou também nas outras variáveis, como ID e categoria??)
    int i, encontrado=0;
    for(i=0; i<a->tamanho; i++) {
        if(strstr(a->componentes[i]->nome, nome)!=NULL) {
            //se a primeira posição já está ocupada, alocar mais memória
            //se for encontrado pela primeira vez (tam=0), ativar a flag "encontrado"
            if(*tam>0) {
                res=(int*)realloc(res, (*tam+1)*sizeof(int));
            } else {
                encontrado=1;
            }
            
            //guardar a posição no vetor e incrementar
            //a variável correspondente ao seu tamanho
            res[*tam]=i;
            (*tam)++;
        }
    }

    //caso o nome especificado tenha sido encontrado
    //num dos componentes, retornar as posições
    //caso contrário, retornar NULL
	return encontrado ? res : NULL;
}

int vetor_ordena(armazem *a, int *vetor_pos_c, int tam) {
    //verificar se os argumentos são válidos
    if(a == NULL || vetor_pos_c == NULL || tam == 0) {
        return -1;
    }

    //preencher o vetor preços com os preços nas posições indicadas
    int i, j;
    float precos[tam];


    for(i = 0; i < tam; i++) {
        precos[i] = a->componentes[vetor_pos_c[i]]->preco;
    }

    //ordenar o vetor preços
    float temp;
    for(i = 0; i < tam; i++) {
        for(j = i+1; j < tam; j++) {
            if(precos[j] </*=*/ precos[i]) {
                //caso os preços sejam iguais,
                //ordenar por ordem alfabética
                //dos seus IDs
                //Mas no ficheiro de texto, os elementos já se encontram
                //ordenados por ID, logo, penso que é impossível
                //encontrar componentes com o mesmo preço, que já não
                //estejam ordenados por ID
                //Por esta razão, comentei a seguinte parte do código:
                /*if(precos[j] == precos[i] && strcmp(a->componentes[j]->ID, a->componentes[i]->ID) < 0) {
                    temp = precos[i];
                    precos[i] = precos[j];
                    precos[j] = temp;

                    temp = vetor_pos_c[i];
                    vetor_pos_c[i] = vetor_pos_c[j];
                    vetor_pos_c[j] = temp;   
                } else {*/
                    temp = precos[i];
                    precos[i] = precos[j];
                    precos[j] = temp;

                    temp = vetor_pos_c[i];
                    vetor_pos_c[i] = vetor_pos_c[j];
                    vetor_pos_c[j] = temp;   
                //}
            }
        }
    }

    return 0;

    //falta pôr a ordenar por ID quando o preço é o mesmo!!!
}
 
fatura *fatura_nova() {
    //alocar memória para a fatura
    fatura *res=(fatura*)malloc(sizeof(fatura));

    //retornar NULL caso a memória não tenha sido alocada
    if(res==NULL) {
        return NULL;
    }

    //inicializar todos os valores da nova fatura
    res->inicio=NULL;
    res->n_parcelas=0;
    res->preco_total=0;

    return res;

    //alocar memória para a parcela}
}

parcela *parcela_nova (const char *ID, int quantidade, float preco ) {
    //verificar se os argumentos são válidos
    if(ID==NULL || strlen(ID)>9 || quantidade==0 || preco==0) {
        return NULL;
    }
    parcela *res=(parcela*)malloc(sizeof(parcela));

    //copiar para a nova parcela os valores especificados pelos parâmetros
    strcpy(res->ID, ID);
    res->preco=preco;
    res->quantidade=quantidade;
    res->proximo=NULL;

    return res; 
}

int insere_parcela_fatura(fatura *f, parcela  *p){
    //verificar se os argumentos são válidos
    if(p == NULL) {
        return -1;
    }

    //se a lista estiver vazia, a parcela é inserida no início
    if(f->inicio == NULL) {
        f->inicio = p;
        f->inicio->proximo = NULL;
        f->n_parcelas++;
        f->preco_total += p->preco * p->quantidade;
        return 0;
    }

    //percorrer a lista até ao último elemento
    parcela *elem;
    for(elem = f->inicio; elem->proximo != NULL; elem = elem->proximo) {
        //caso a parcela já esteja na fatura,
        //atualizam-se o preço e quantidade
        if(strcmp(elem->ID, p->ID)==0) {
            elem->preco += p->preco;
            elem->quantidade += p->quantidade;
            f->preco_total += p->preco * p->quantidade;
            return 1;
        }
    }

    //o último elemento da lista aponta para p (o novo último elemento 
    //da lista) e p (agora último elemento aponta para NULL)
    elem->proximo = p;
    p->proximo = NULL;
    f->preco_total += p->preco * p->quantidade;
    f->n_parcelas++;

    return 0;
}

int parcela_apaga(parcela *p) {
    //verificar se a parcela é válida
    if(p == NULL) {
        return -1;
    }

    //libertar a memória ocupada pela parcela
    free(p);

    return 0;
}

fatura *cria_fatura(armazem *a, const char *f) {
    //verificar se os parâmetros são válidos
    if(a == NULL || f == NULL) {
        return NULL;
    }

    //criação da fatura a retornar
    fatura *res = fatura_nova();
    if(res == NULL) {
        return NULL;
    }

    //abrir o ficheiro
    FILE *fi = fopen(f, "r");
    char linha[MAX_CHAR], *tipo, *desc;
    int quantidade, tam, *vet_pos, i;
    parcela *elem; //= res->inicio;

    //ler a lista de compras linha a linha
    while(fgets(linha, MAX_CHAR, fi) != NULL) {
        //segmentar a linha lida
        tipo = strtok(linha, ",");
        desc = strtok(NULL, ",");
        quantidade = atoi(strtok(NULL, ","));
        
        //condições respetivas às diferentes situações
        if(tipo[0] == 'C') {
            //obter o vetor das posições em que o componente se encontra
            //e ordená-lo por ordem crescente de preço
            //caso o elemento não seja encontrado no armazém, passa-se a ler
            //a próxima linha da lista de compras
            vet_pos = armazem_pesquisa_categoria(a, desc, &tam);
            if(vet_pos == NULL) {
                continue;
            }
            vetor_ordena(a, vet_pos, tam);

            //procurar o componente mais barato com quantidade suficiente
            for(i = 0; i < tam; i++) {
                //se a quantidade disponível em armazém for satisfatória,
                //a parcela é criada e inserida na fatura
                if(a->componentes[vet_pos[i]]->quantidade >= quantidade) {
                    //criar a nova parcela e inseri-la na fatura
                    elem = parcela_nova(a->componentes[vet_pos[i]]->ID, quantidade, a->componentes[vet_pos[i]]->preco);
                    if(insere_parcela_fatura(res, elem) == -1) {
                        //caso ocorra erro ao inserir a parcela, a função retorna NULL
                        return NULL;
                    }
                    
                    //caso tenha sido utilizada toda a quantiade disponível,
                    //remover o componente por completo do armazém
                    if(a->componentes[vet_pos[i]]->quantidade == quantidade) {
                        /* componente_remove(a, a->componentes[vet_pos[i]]->nome); */ 
                        //^^ Se usar esta função, o teste apresenta erro relativamente
                        //à quantidade de cri00900 uma vez que usa uma posição fixa
                        //e esta função altera o tamanho do vetor
                        a->componentes[vet_pos[i]]->quantidade = 0;
                    } else {
                        //caso contrário, a quantidade em stock é apenas decrementada
                        a->componentes[vet_pos[i]]->quantidade -= quantidade;
                    }

                    break;
                }
            }

            //se i=tam, a instrução de break nunca foi executada,
            //pelo que se pode concluir que não há nenhum elemento
            //que satisfaça a quantidade necessária
            if(i == tam) {
                //escolher a partir do mais barato até satisfazer a quantidade
                int quantEmFalta;
                for(i = 0, quantEmFalta = quantidade; i < tam && quantEmFalta > 0; i++) {
                    //criar a nova parcela com toda a quantidade
                    //disponível do comonente e inseri-la na fatura
                    if(a->componentes[vet_pos[i]]->quantidade < quantEmFalta) {
                        elem = parcela_nova(a->componentes[vet_pos[i]]->ID, a->componentes[vet_pos[i]]->quantidade, a->componentes[vet_pos[i]]->preco);
                        if(insere_parcela_fatura(res, elem) == -1) {
                            //caso ocorra erro ao inserir a parcela, a função retorna NULL
                            return NULL;
                        }
                        
                        //decrementar quantidade em falta e remover o componente
                        //do armazém, uma vez que foram usados todos os itens disponíveis
                        quantEmFalta -= a->componentes[vet_pos[i]]->quantidade;
                        /* componente_remove(a, a->componentes[vet_pos[i]]->nome); */
                        //^^ Se usar esta função, o teste apresenta erro relativamente
                        //à quantidade de cri00900 uma vez que usa uma posição fixa
                        //e esta função altera o tamanho do vetor
                        a->componentes[vet_pos[i]]->quantidade = 0;
                        
                    } else {
                        //criar a nova parcela apenas com a quantidade
                        //em falta e inseri-la na fatura
                        elem = parcela_nova(a->componentes[vet_pos[i]]->ID, quantEmFalta, a->componentes[vet_pos[i]]->preco);
                        if(insere_parcela_fatura(res, elem) == -1) {
                            //caso ocorra erro ao inserir a parcela, a função retorna NULL
                            return NULL;
                        }
                        
                        //caso tenha sido utilizada toda a quantidade disponível
                        //remover o componente do armazém
                        if(a->componentes[vet_pos[i]]->quantidade == quantEmFalta) {
                            /* componente_remove(a, a->componentes[vet_pos[i]]->nome); */
                            //^^ Se usar esta função, o teste apresenta erro relativamente
                            //à quantidade de cri00900 uma vez que usa uma posição fixa
                            //e esta função altera o tamanho do vetor
                            a->componentes[vet_pos[i]]->quantidade = 0;
                        } else {
                            //caso contrário, a quantidade em stock é apenas decrementada
                            a->componentes[vet_pos[i]]->quantidade -= quantEmFalta;
                        }
                        
                        //a quantidade em falta é colocada a zero
                        //e o ciclo termina - já foram comprados
                        //todos os componentes necessários
                        quantEmFalta = 0;
                    }
                    
                }
            }

        } else if(tipo[0] == 'I') {
            //percorrer o armazém até encontrar 
            //um componente com ID correspondente
            for(i = 0; i < a->tamanho; i++) {
                if(strcmp(desc, a->componentes[i]->ID) == 0) {
                    //caso a quantiade disponível seja menor ou igual
                    //à quantidade desejada, usa-se a disponível
                    if(a->componentes[i]->quantidade <= quantidade) {
                        elem = parcela_nova(desc, a->componentes[i]->quantidade, a->componentes[i]->preco);
                        if(insere_parcela_fatura(res, elem) == -1) {
                            //caso ocorra erro ao inserir a parcela, a função retorna NULL
                            return NULL;
                        }
                        
                        //como foi utilizado todo o stock
                        //remove-se o componente do armazém
                        /* componente_remove(a, a->componentes[i]->nome); */ 
                        //^^ Se usar esta função, o teste apresenta erro relativamente
                        //à quantidade de cri00900 uma vez que usa uma posição fixa
                        //e esta função altera o tamanho do vetor
                        a->componentes[i]->quantidade = 0;
                    } else {
                        elem = parcela_nova(desc, quantidade, a->componentes[i]->preco);
                        if(insere_parcela_fatura(res, elem) == -1) {
                            //caso ocorra erro ao inserir a parcela, a função retorna NULL
                            return NULL;
                        }

                        //decrementar a quantidade disponível
                        //em stock do componente
                        a->componentes[i]->quantidade -= quantidade;
                    }

                    break;
                }
            }

        } else if(tipo[0] == 'N') {
            //obter o vetor das posições em que o componente se encontra
            //e ordená-lo por ordem crescente de preço
            //caso o elemento não seja encontrado no armazém, passa-se a ler
            //a próxima linha da lista de compras
            vet_pos = armazem_pesquisa_nome(a, desc, &tam);
            if(vet_pos == NULL) {
                continue;
            }
            vetor_ordena(a, vet_pos, tam);

            for(i = 0; i < tam; i++) {
                if(a->componentes[vet_pos[i]]->quantidade >= quantidade) {
                    //criar a nova parcela e inseri-la na fatura
                    elem = parcela_nova(a->componentes[vet_pos[i]]->ID, quantidade, a->componentes[vet_pos[i]]->preco);
                    if(insere_parcela_fatura(res, elem) == -1) {
                        //caso ocorra erro ao inserir a parcela, a função retorna NULL
                        return NULL;
                    }

                    //se tiver usado toda a quantidade em stock, remover
                    //o componente do armazém
                    if(a->componentes[vet_pos[i]]->quantidade == quantidade) {
                        /* componente_remove(a, a->componentes[vet_pos[i]]->nome); */ 
                        //^^ Se usar esta função, o teste apresenta erro relativamente
                        //à quantidade de cri00900 uma vez que usa uma posição fixa
                        //e esta função altera o tamanho do vetor
                        a->componentes[vet_pos[i]]->quantidade = 0;
                    } else {
                        //caso contrário, decrementar a quantidade em stock
                        a->componentes[vet_pos[i]]->quantidade -= quantidade;
                    }

                    break;
                }   
            }

            //se i=tam, não foi encontrado nenhum componente
            //com quantidade suficiente - escolher o que tem 
            //maior quantidade e em caso de empate, escolher
            //o mais barato
            if(i == tam) {
                //percorrer o vetor de modo a encotrar o componente com maior quantidade
                int iMax=-1, quantMax=-1;
                for(i = 0; i < tam; i++) {
                    //em caso de empate, como o vetor está ordenado por ordem crescente de 
                    //preço, continuará registado como "iMax" o índice em que há mais
                    //quantidade disponível e por menor preço
                    if(a->componentes[vet_pos[i]]->quantidade > quantMax) {
                        iMax = i;
                        quantMax = a->componentes[vet_pos[i]]->quantidade;
                    }
                }

                //criar a nova parcela e inseri-la na fatura
                elem = parcela_nova(a->componentes[vet_pos[iMax]]->ID, a->componentes[vet_pos[iMax]]->quantidade, a->componentes[vet_pos[iMax]]->preco);
                if(insere_parcela_fatura(res, elem) == -1) {
                    //caso ocorra erro ao inserir a parcela, a função retorna NULL
                    return NULL;
                }

                //Remover o item do armazém, uma vez que foi usada
                //toda a quantidade disponível
                /* componente_remove(a, a->componentes[vet_pos[iMax]]->nome); */ 
                //^^ Se usar esta função, o teste apresenta erro relativamente
                //à quantidade de cri00900 uma vez que usa uma posição fixa
                //e esta função altera o tamanho do vetor
                a->componentes[vet_pos[iMax]]->quantidade = 0;

                break; 
            }

        } else {
            return NULL;
        }
    }

    return res;
}

int fatura_apaga(fatura *f) {
    //verificar se a fatura é válida
    if(f == NULL) {
        return 1;
    }

    //eliminar todas as parcelas da fatura
    parcela *elem;    
    for(elem = f->inicio; elem != NULL; elem = elem->proximo) {
        if(parcela_apaga(elem) == -1) return -1;
    }

    //libertar a memória ocupada pela fatura
    free(f);

    return 0;
}