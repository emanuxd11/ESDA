/*****************************************************************/
/*          Biblioteca vetor | ESDA | LEEC | 2021/22             */
/*****************************************************************/

#ifndef VETOR_H


/**
* registo para armazenar cada elemento (apenas uma string neste caso)
*/
typedef struct
{
  char *str;

} v_elemento;

/**
* este registo contem um vetor de elementos, um contador do tamanho e outro para a capacidade
*/
typedef struct
{
  /** numero de elementos do vetor */
  int tamanho;

  /** capacidade do vetor */
  int capacidade;

  /** array de elementos armazenados */
  v_elemento* elementos;

} vetor;

/**
*  cria um novo vetor com tamanho 0 e capacidade 0
*  retorno: apontador para o vetor criado
*  nota: se vetor nao foi criado retorna NULL
*/
vetor* vetor_novo();

/**
*  elimina um vetor, libertando toda a memoria ocupada
*  parametro: vec apontador para vetor
*  nota: se vec = NULL retorna sem fazer nada
*/
void vetor_apaga(vetor *vec);


/**
*  retorna o elemento armazenado na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: pos indice do elemento
*  retorno: apontador para a string na posicao correspondente
*  nota: se ocorrer algum erro retorna NULL (p.ex. se valor pos indicar uma posicao invalida)
*/
const char* vetor_elemento(vetor *vec, int pos);

/**
*  insere um elemento na posicao especificada
*  parametro: vec apontador para vetor
*  parametro: valor string a inserir
*  parametro: pos indice do elemento onde se pretende inserir a string, se pos=tamanho ou pos=-1 insere no fim do vetor
*  retorno: -1 se ocorrer algum erro (p.ex. se valor pos indicar uma posicao invalida) ou o valor de pos se bem sucedido
*  nota: se a capacidade nao for suficiente para guardar novo elemento, devera ser aumentada para 2x em relacao a capacidade anterior; inicialmente aumenta para capacidade 1
*/
int vetor_insere(vetor *vec, const char* valor, int pos);

/**
*  imprime os conteudos de um vetor
*  parametro: vec apontador para vetor
*  retorno: -1 se ocorrer um erro ou 0 se for bem sucedido
*/
int vetor_imprime(vetor *vec);


#define VETOR_H
#endif
