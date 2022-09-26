#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "contentor.h"

/* alinea a) */
/**
 *  \brief cria um novo contentor
 *  \param dest destino do contentor
 *  \param val valor das mercadorias no contentor
 *  \return apontador para o contentor; NULL se erro
 */
contentor* contentor_novo(char* dest, float val)
{
	if(dest == NULL) return NULL;

	contentor *res = malloc(sizeof(contentor));
	if(res == NULL) return NULL;

	res->destino = (char*)malloc(sizeof(char) * (strlen(dest)+1));
	
	res->destino = dest;
	res->valor = val;

	return res;
}

/**
 *  \brief apaga contentor (liberta memoria correspondente)
 *  \param contr apontador para o contentor
 *  \remark se contr = NULL retorna sem fazer nada
 */
void contentor_apaga(contentor* contr)
{

	if (contr == NULL)
		return;	

	if (contr->destino != NULL)
	{
		free(contr->destino);
		contr->destino = NULL;
	}

	free(contr);
}

/**
 *  \brief imprime dados do contentor
 *  \param contr apontador para o contentor
 */
void contentor_imprime(contentor* contr)  {
	if (contr == NULL)
		printf("Contentor nulo\n");
	else
		printf("Destino: %s, valor da carga: %.2f K Euros\n", contr->destino, contr->valor);
}
