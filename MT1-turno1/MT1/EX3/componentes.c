/*****************************************************************/
/*       Biblioteca componentes | ESDA | LEEC | 2021/22          */
/*****************************************************************/

#include "componentes.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

parcela* compra_pop(compra *c)
{
	/* Exercicio 3 */
    
    return NULL;
}

componente *componente_novo(const char *ID, char *nome, int quantidade, float preco, const char *categoria){
    
    if (ID == NULL || nome == NULL || quantidade < 0 || preco <0 || categoria == NULL){
        return NULL;
    }
    
    componente *c = (componente *)malloc(sizeof(componente)); 
    if (c == NULL){
        return NULL;
    }
    strcpy(c->ID, ID);
    c->nome = (char *)malloc((strlen(nome) + 1)*sizeof(char));
    strcpy(c->nome, nome);
    c->quantidade = quantidade;
    c->preco = preco;
    strcpy(c->categoria, categoria);

    return c;
}

armazem *armazem_novo(){
    armazem *a = (armazem*)malloc(sizeof(armazem));
    if (a == NULL){
        return NULL;
    }
    a->componentes = NULL;
    a->tamanho = 0;
    return a;
}

int componente_insere(armazem *a,componente *c){
    if(a == NULL || c == NULL){
        return -1;
    }
    int i;
    //verifica se é o inicio

    if(a->tamanho == 0){
        a->componentes =  (componente **)malloc(sizeof(componente*));
        a->componentes[0] = c;
        a->tamanho++;

        return 0;
    } else{
        for (i = 0; i < a->tamanho; i++){
            if(strcmp(a->componentes[i]->ID,c->ID) == 0){ //ja existe
                //printf("Sao iguais");
                a->componentes[i]->quantidade += c->quantidade;
                a->componentes[i]->preco = c->preco;
                return 1;
            }
        }
        //ainda nao existe
        a->tamanho++;
        a->componentes = (componente **)realloc(a->componentes, (a->tamanho) * sizeof(componente *));

	    if (a->componentes == NULL){
            return -1;
        }
        a->componentes[i] = c;       
        return 0;
    
    }
}

armazem *armazem_importa(const char *nome_ficheiro){
    if (nome_ficheiro == NULL ){
        return NULL;
    }
    FILE *f = fopen(nome_ficheiro, "r");
	if (f == NULL)
		return NULL;
    armazem *a = armazem_novo();
	if (a == NULL)
	{
		fclose(f);
		return NULL;
	}
    char str[500] = {0}, id[10] = {0}, nome[MAX_CHAR], categoria[MAX_CHAR];
	int quantidade = 0; 
    float preco = 0;
	char *token;
	componente *c;
	int ret;


    int count = 0;
    while(fgets(str, 500 * sizeof(char), f) != NULL){
        count ++;
        str[strlen(str) - 1] = '\0';
        
		token = strtok(str, ",");
		if(!token)
		    break;
		strcpy(id, token);

		token = strtok(NULL, ",");
		strcpy(nome, token);

        token = strtok(NULL, ",");
		strcpy(categoria, token);

        token = strtok(NULL, ",");
		quantidade = atoi(token);

        token = strtok(NULL, ",");
		preco = atof(token);

        c = componente_novo(id,nome,quantidade,preco,categoria);
		if (c == NULL)
		{
			fclose(f);
			armazem_apaga(a);
			return NULL;
		}

        ret = componente_insere(a,c);
        
        if (ret == -1) // deu erro a inserir
		{
			fclose(f);
			componente_apaga(c);
			armazem_apaga(a);
			return NULL;
		} else if (ret == 1){ //componente ja existia, podemos libertar
            componente_apaga(c);
        }
    }


    fclose(f);
    return a;
}

componente *componente_remove(armazem *a,  char *nome){
    if (a == NULL || nome == NULL)
		return NULL;

    int i, pos = -1;
	for (i = 0; i < a->tamanho; i++) // encontra posição do elemento
	{
		if (strcmp(a->componentes[i]->nome, nome) == 0)
		{
			pos = i;
			break;
		}
	}
	if (pos == -1){ // o elemento a remover não existe na coleção
		return NULL;
    }
    componente *c1 = a->componentes[pos];

	/* copia todos os elementos a partir da posicao pos+1 ate' ao fim do vetor para pos */
	for (i = pos + 1; i < a->tamanho; i++)
	{
		a->componentes[i - 1] = a->componentes[i];
	}

	(a->tamanho)--;
	a->componentes = (componente **)realloc(a->componentes, a->tamanho * sizeof(componente *));
	return c1;
}


int componente_apaga(componente *c)
{
	if (c == NULL)
		return -1;
    if (c->nome != NULL){
        free(c->nome);
    }

	free(c);
	return 0;
}


int armazem_apaga(armazem *a){
	if (a == NULL)
		return -1;
	for (int i = 0; i < a->tamanho; i++)
	{
		componente_apaga(a->componentes[i]);
	}
	free(a->componentes);
	free(a);
	return 0;
}

int *armazem_pesquisa_categoria(armazem *a, const char *categoria, int *tam){
    if (a == NULL || categoria == NULL)
		return NULL;

	int *idxs = NULL;
	*tam = 0;

	for (int i = 0; i < a->tamanho; i++)
	{
		if (strcmp(categoria, a->componentes[i]->categoria) == 0) // verifica na categoria
		{
			(*tam)++;
			idxs = (int *)realloc(idxs, *tam * sizeof(int));
			if (idxs == NULL)
				return NULL;
			idxs[*tam - 1] = i;
		}
	}

	return idxs;
}



int *armazem_pesquisa_nome(armazem *a, char *nome, int *tam)
{
	if (a == NULL || nome == NULL)
		return NULL;

	int *idxs = NULL;
	*tam = 0;

	for (int i = 0; i < a->tamanho; i++)
	{
		if (strstr(a->componentes[i]->nome, nome)) // verifica no nome se contem substring
		{
			(*tam)++;
			idxs = (int *)realloc(idxs, *tam * sizeof(int));
			if (idxs == NULL)
				return NULL;
			idxs[*tam - 1] = i;
		}
	}

	return idxs;
}


int  vetor_ordena(armazem *a, int *vetor_pos_c, int tam){
    if (a == NULL || vetor_pos_c == NULL || tam == 0)
		return -1;
    float preco[tam];
    int i = 0, j = 0, temp;
    //Vai buscar os preços
    for (i = 0; i < tam; i++){
        preco[i] = a->componentes[vetor_pos_c[i]]->preco;
        //printf("Preço da posição %d: %f \n", vetor_pos_c[i], preco[i]);
        }

    //Ordenação dos preços e por consequencia do vetor de indices
    for (i = 0; i < tam; i++){
        for (j = i+1; j < tam; j++){
            if ((preco[j] < preco[i]) || ((preco[j] < preco[i])&& (strcmp(a->componentes[vetor_pos_c[j]]->ID,a->componentes[vetor_pos_c[i]]->ID)<0))){

                temp = preco[i];
                preco[i] = preco[j];
                preco[j] = temp;

                temp = vetor_pos_c[i]; 
                vetor_pos_c[i] = vetor_pos_c[j]; 
                vetor_pos_c[j] = temp; 
            }
        }
    }

    return 0;
}







fatura *fatura_nova(){
    fatura *f = (fatura*) malloc (sizeof(fatura));
    if (f == NULL){
        return NULL;
    }
    f->inicio = NULL;
    f->n_parcelas = 0;
    f->preco_total = 0.0;

    return f;
}




parcela *parcela_nova (const char *ID, int quantidade,   float preco ){
    if(ID == NULL || quantidade == 0 || preco < 0){
        return NULL;
    }
    parcela *p = (parcela*) malloc(sizeof(parcela));
    if (p == NULL){
        return NULL;
    }
   // printf("Criei nova parcela\n");
    strcpy(p->ID, ID);
    p->quantidade = quantidade;
    p->preco = preco;
    p->proximo = NULL;
    
    return p; 
}


int insere_parcela_fatura(fatura *f, parcela  *p){
    //printf("Fatura (n_parcelas) antes de entrar na função de inserir parcela : %d\n", f->n_parcelas);
    if(f == NULL || p == NULL){
        return -1;
    }
    parcela *aux = NULL;
    //verifica se é o inicio
    if(f->n_parcelas == 0){
        f->inicio = p;
        f->n_parcelas = (int)f->n_parcelas + 1;
        f->preco_total+=(p->preco*p->quantidade);
        p->proximo = NULL;
        return 0;
    } else {  //percorremos até encontrarmos o final
        aux = f->inicio;
        int count = 0;
        while(aux->proximo != NULL){
            count++;
           if (strcmp(aux->ID,p->ID) == 0){
               // printf("são iguais\n");
                aux->quantidade = aux->quantidade + p->quantidade;
             //   f->n_parcelas++;
                f->preco_total+= p->quantidade*p->preco;

                return 1;
           }
           aux = aux->proximo;
        }
        aux->proximo = p;
        f->n_parcelas++;
        f->preco_total+= p->quantidade*p->preco;

    }
    return 0;
}


void parcela_apaga(parcela *p){
    if (p == NULL){
        return;
    }
    free(p);
    p = NULL;
    return;
}








int  vetor_ordena_quantidade(armazem *a, int *vetor_pos_c, int tam){
    if (a == NULL || vetor_pos_c == NULL || tam == 0)
		return -1;
    float quantidade[tam];
    int i = 0, j = 0, temp;
    //Vai buscar as quantidades
    for (i = 0; i < tam; i++){
        quantidade[i] = a->componentes[vetor_pos_c[i]]->quantidade;
        //printf("Preço da posição %d: %f \n", vetor_pos_c[i], preco[i]);
        }

    //Ordenação dos preços e por consequencia do vetor de indices
    for (i = 0; i < tam; i++){
        for (j = i+1; j < tam; j++){
            if (quantidade[j] < quantidade[i]){

                temp = quantidade[i];
                quantidade[i] = quantidade[j];
                quantidade[j] = temp;

                temp = vetor_pos_c[i]; 
                vetor_pos_c[i] = vetor_pos_c[j]; 
                vetor_pos_c[j] = temp; 
            }
        }
    }

    return 0;
}













fatura *cria_fatura(armazem *a, const char *f){
    if (f == NULL){
        return NULL;
    }

    FILE *file = fopen(f, "r");
	if (f == NULL)
		return NULL;
    
    fatura *fa;
    fa = fatura_nova();
    
    if (fa == NULL){
        return NULL;
    }
    
    char str[500] = {0}, type[2],  nome[MAX_CHAR], ID[10], categoria[MAX_CHAR];
    int *categorias_idx, *nomes_idx, *nomes_idx1;
    int ret = 0; 
    char *token; 
    int tam;   
	int quantidade = 0;
    int count = 0;
    
    while(fgets(str, 500 * sizeof(char), file) != NULL){
        str[strlen(str) - 1] = '\0';
        //printf("Linha\n");

        token = strtok(str, ",");
		if(!token)
		    break;
		strcpy(type,token);
        if (strstr(type, "C")){
           //é do tipo categoria -> proximos tokens são a categoria e a quantidade
            token = strtok(NULL, ",");
		    strcpy(categoria, token);
            token = strtok(NULL, ",");
		    quantidade = atoi(token);
           //printf("Categoria: %s, Quantidade: %d\n", categoria, quantidade);



            //Escolhe-se pelo mais barato, que tenha a quantidade necessária;
            //Se não houver nenhum componente que tenha a quantidade necessaria, 
            //deve-se ir ao mais barato usar toda a quantidade,
            // depois ir ao 2º mais barato e usar a quantidade necessária para fazer o pretendido 
            //se isso ainda não for suficiente continua-se sempre pelo mais barato até chegar à quantidade pretendida. 
            //Se não se conseguir chegar a essa quantidade pretendida, só se fatura o que se consegue.

            //ir buscar os indices dos componentes pertencentes à categoria: 
            categorias_idx = armazem_pesquisa_categoria(a, categoria,  &tam);

            //ordenar por preco: 
            ret = vetor_ordena(a,categorias_idx,tam);
	    if (ret==-1 )  
		{
		fclose(file);		
		return NULL;

		}
            //Criar parcela e verificar se satisfazemos a quantidade!
            count = quantidade;
            parcela *p;
            //Verificar se existe algum com toda a quantidade
            for (int h = 0; h < tam; h++){
                
                 int j1 = categorias_idx[h];
                 if (a->componentes[j1]->quantidade >= count){  //tem quantidade suficiente para acabar com o pedido
                    //printf("Tem quantidade para acabar - %s - %d - %d\n",a->componentes[j1]->ID,a->componentes[j1]->quantidade,count);
                    //criar nova parcela
                    p = parcela_nova(a->componentes[j1]->ID, count ,a->componentes[j1]->preco);
                    //insere parcela
                    //printf("A inserir na fatura \n");
                    insere_parcela_fatura(fa,p);
                    a->componentes[j1]->quantidade=a->componentes[j1]->quantidade-count;
                    //Atualizar count
                    count = 0;
                    break; 
                 }
            }
            if (count!=0)
            for (int i = 0; i < tam; i++){
                //printf("Count no inicio do ciclo %d\n", count);
                if (count == 0){
                    break; 
                }
                int j = categorias_idx[i];

                if (a->componentes[j]->quantidade >= count){  //tem quantidade suficiente para acabar com o pedido
                    //printf("Tem quantidade para acabar\n");
                    //criar nova parcela
                    p = parcela_nova(a->componentes[j]->ID, count ,a->componentes[j]->preco);
                    //insere parcela
                    //printf("A inserir na fatura \n");
                    insere_parcela_fatura(fa,p);
                    a->componentes[j]->quantidade=a->componentes[j]->quantidade-count;
                    //Atualizar count
                    count = 0;

                }else{  //nao tem quantidade suficiente para acabar com o pedido
                    //printf("Não tem quantidade para acabar\n");
                    //criar nova parcela
                    p = parcela_nova(a->componentes[j]->ID, a->componentes[j]->quantidade,a->componentes[j]->preco);
                    
                    //insere parcela
                    //printf("A inserir na fatura \n");
                    insere_parcela_fatura(fa,p);
                    
                    //Atualizar count
                    count = count - a->componentes[j]->quantidade;
                    a->componentes[j]->quantidade=0;
                }   
                //printf("Indice em armazem %d\n ",j);
                //printf("ID %s, nome %s, preco %f, quantidade %d, categoria %s\n", a->componentes[j]->ID,a->componentes[j]->nome, a->componentes[j]->preco, a->componentes[j]->quantidade, a->componentes[j]->categoria);
            }
            free(categorias_idx); 

        } else if (strstr(type, "I")){
            //é do tipo ID -> proximos tokens são o ID e a quantidade
            token = strtok(NULL, ",");
		    strcpy(ID, token);
            token = strtok(NULL, ",");
		    quantidade = atoi(token);
            parcela *p;
            int count = 0;
            //ir buscar o indice do ID: 
            for (int j = 0; j < a->tamanho; j++)
	        {
		        if (strcmp(ID, a->componentes[j]->ID) == 0) // verifica na categoria
		        {
                    if (a->componentes[j]->quantidade >= quantidade){
                        count = quantidade;
                    } else{
                        count = a->componentes[j]->quantidade;
                    }
                    //criar nova parcela
                    p = parcela_nova(a->componentes[j]->ID, count ,a->componentes[j]->preco);
                    //insere parcela
                    //printf("A inserir na fatura \n");
                    insere_parcela_fatura(fa,p);
                    a->componentes[j]->quantidade=a->componentes[j]->quantidade-count;
                }
                
            }

	
            //printf("ID: %s, Quantidade: %d\n", ID, quantidade);

            //Usa-se a quantidade que houver do componente



        } else{
            //é do tipo Nome -> proximos tokens são o nome e a quantidade
            token = strtok(NULL, ",");
		    strcpy(nome, token);
            token = strtok(NULL, ",");
		    quantidade = atoi(token);
            parcela *p = NULL;
            
        //    printf("Nome: %s, Quantidade: %d\n", nome, quantidade);

            //escolhe-se pelo mais barato, que tenha a quantidade pretendida. 
            //Se não houve nenhum escolhe-se o que tiver a maior quantidade, em caso de empate escolhe-se o mais barato 
            //( logicamente não se vai conseguir a quantidade toda)

            //ir buscar os indices dos componentes pertencentes à categoria: 
            nomes_idx = armazem_pesquisa_nome(a, nome,  &tam);
            nomes_idx1 = nomes_idx;
            //ordenar por preco: 
            ret = vetor_ordena(a,nomes_idx,tam);

            for (int i = 0; i < tam; i++){
                int j = nomes_idx1[i];
                //printf("Quantidade dos componentes na lista ordenada: %d \n",a->componentes[j]->quantidade);
                if (a->componentes[j]->quantidade >= quantidade){  //escolhe-se pelo mais barato, que tenha a quantidade pretendida
                    //criar nova parcela
                    p = parcela_nova(a->componentes[j]->ID, quantidade ,a->componentes[j]->preco);
                    
                    //insere parcela
                    insere_parcela_fatura(fa,p);
                    a->componentes[j]->quantidade=a->componentes[j]->quantidade-quantidade;
                    i = tam;
                } 
            }

            if (p == NULL){ //Se não houve nenhum escolhe-se o que tiver a maior quantidade, em caso de empate escolhe-se o mais barato
                //ordenar os indices por quantidade: 
                ret = vetor_ordena_quantidade(a,nomes_idx1,tam);
                if ((a->componentes[nomes_idx1[tam-1]]->quantidade != a->componentes[nomes_idx1[tam-2]]->quantidade)){ // escolhe-se o que tiver a maior quantidade
                    //criar nova parcela
                    p = parcela_nova(a->componentes[nomes_idx1[tam-1]]->ID, a->componentes[nomes_idx1[tam-1]]->quantidade ,a->componentes[nomes_idx1[tam]]->preco);
                    //insere parcela
                    insere_parcela_fatura(fa,p);
                    a->componentes[nomes_idx1[tam-1]]->quantidade=0;
                } else{ //em caso de empate escolhe-se o mais barato
                    int maior_quantidade = a->componentes[nomes_idx1[tam-1]]->quantidade;
                    for (int i = 0; i < tam; i++){
                        int j = nomes_idx[i];
                        if (a->componentes[j]->quantidade == maior_quantidade){  //escolhe-se pelo mais barato, que tenha a quantidade pretendida
                            //criar nova parcela
                            p = parcela_nova(a->componentes[j]->ID, a->componentes[j]->quantidade ,a->componentes[j]->preco);
                            //insere parcela
                            insere_parcela_fatura(fa,p);
                            a->componentes[j]->quantidade=0;
                   
                            i = tam;
                        } 
                    }
                }
            }


    free(nomes_idx);

        }
        
    }

    
    fclose(file);
  


    return fa;



}


int fatura_apaga(fatura *f){
    //percorrer a lista toda dentro e libertar as parcelas. so depois se apaga a fatura
    parcela *aux = f->inicio;
    
    if (f != NULL){
         while (f->inicio) {
            aux = f->inicio;
            f->inicio = f->inicio->proximo;
            free(aux);
        }
        free(f);
		f = NULL;
    }

    free(f);
    return 0;
}

void troca_parcelas(parcela *p1, parcela *p2)
{
    char idt[10] = {'\0'};
    strcpy(idt, p1->ID);
    int quant = p1->quantidade;
    float pr = p1->preco;
    strcpy(p1->ID, p2->ID);
    p1->preco = p2->preco;
    p1->quantidade = p2->quantidade;
    strcpy(p2->ID, idt);
    p2->preco = pr;
    p2->quantidade = quant;
}

compra* compra_nova()
{
    compra *c = (compra*)malloc(sizeof(compra));
    if (c != NULL){
        c->raiz = NULL;
        c->tamanho = 0;
        return c;
    }
    return NULL;
}

void compra_ordena(compra *c)
{
    if (c != NULL) {
        parcela *next, *curr, *min;
        /* Algoritmo de ordenação por seleção - ordem crescente */
        if (c->tamanho != 0) {
            for (curr = c->raiz; curr != NULL; curr = curr->proximo) {
                min = curr;
                next = curr->proximo;
                while (next != NULL) {
                    if (next->quantidade < min->quantidade || (next->quantidade == min->quantidade && strcmp(next->ID, min->ID) < 0))
                        min = next;
                    next = next->proximo;
                }
                /* Ordenar a pilha */
                if (min != curr) troca_parcelas(curr, min);
            }
        }
    }
}

void compra_push(compra *c, parcela *p)
{
	if (c != NULL && p != NULL) {
        c->tamanho++;

        /* Inserir no topo da pilha */
        if (c->raiz == NULL) { // Se a pilha está vazia
            c->raiz = p;
            return;
        }

        p->proximo = c->raiz;
        c->raiz = p;

        compra_ordena(c);
    }
}

compra* cria_compra(fatura *f)
{
    if (f != NULL) {
        compra *c = compra_nova();
        if (c == NULL) return NULL;

        parcela *aux;
        if (f->n_parcelas != 0) {
            /* Inserir na pilha */
            for (aux = f->inicio; aux != NULL; aux = aux->proximo)
                compra_push(c, parcela_nova(aux->ID, aux->quantidade, aux->preco)); 
        }
        return c;
    }
    return NULL;
}

int compra_apaga(compra *c)
{
	if (c != NULL) {
        parcela *aux;
        while (c->raiz) {
            aux = c->raiz;
            c->raiz = c->raiz->proximo;
            free(aux);
        }
        free(c);
        c = NULL;
        return 0;
    }
	return -1;
}