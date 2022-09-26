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
                        componente_remove(a, a->componentes[vet_pos[i]]->nome);
                    } else {
                        //caso contrário, a quantidade em stock é apenas decrementada
                        a->componentes[vet_pos[i]]->quantidade -= quantidade;
                    }

                    res->n_parcelas++;
                    break;
                }
            }

            //se i=tam, a instrução de break nunca foi executada,
            //pelo que se pode concluir que não há nenhum elemento
            //que satisfaça a quantidade necessária
            if(i == tam) {
                //escolher a partir do mais barato até satisfazer a quantidade
                int quantEmFalta = quantidade;
                for(i = 0; i < tam && quantEmFalta > 0; i++) {
                    if(a->componentes[vet_pos[i]]->quantidade >= quantEmFalta) {
                        
                    } 
                }
            }

        } else if(tipo[0] == 'I') {

        } else if(tipo[0] == 'N') {

        } else {
            return NULL;
        }
    }

    return res;
}