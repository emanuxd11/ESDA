#include <stdio.h>
#include "bst.h"
#include "avl.h"

int main()
{
  // ALINEA a)
  arvore_bst *bst = bst_nova();

  bst_insere(bst, "G");
  bst_insere(bst, "C");
  bst_insere(bst, "A");
  bst_insere(bst, "F");
  bst_insere(bst, "L");
  bst_insere(bst, "J");
  bst_insere(bst, "V");
  bst_insere(bst, "M");
  bst_insere(bst, "N");
  bst_insere(bst, "O");

  // ALINEA b)
  printf("Altura da arvore: %d (deve ser 5)\n", bst_altura(bst->raiz));
 
  // ALINEA c)
  printf("Nos da arvore: ");
  bst_imprime(bst);
  
  // ALINEA d)
  /*
    As funções bst_preordem_impl e avl_preordem_impl são exatamente iguais.
    Já no caso das funções bst_altura e avl_altura, são encontradas diferenças. 
    Numa árvore BST, a altura é dada pela profundidade do maior ramo, mas, numa árvore AVL,
    em cada nó podemos encontrar guardada a sua altura. Isto acontece porque uma AVL tem
    um fator de equilíbrio correspondente à diferença entre a altura da sub-árvore direita e a 
    altura da sub-árvore esquerda. Este fator de equilíbro pode ser -1, 0 ou 1. -1 significa que
    a árvore está mais "inclinada" para a esquerda, 0 significa que está equilibrada e 1
    significa que está mais "inclinada" para a direita.
  */ 

  // ALINEA e)
  arvore_avl *avl = avl_nova();
  
  avl_insere(avl, "G");
  avl_insere(avl, "C");
  avl_insere(avl, "A");
  avl_insere(avl, "F");
  avl_insere(avl, "L");
  avl_insere(avl, "J");
  avl_insere(avl, "V");
  avl_insere(avl, "M");
  avl_insere(avl, "N");
  avl_insere(avl, "O");

  // ALINEA f)
  printf("Altura da arvore AVL: %d. Sera igual a altura da arvore BST(%d)? "
  "Nao, pois esta arvore e equilibrada\n", avl_altura(avl->raiz), bst_altura(bst->raiz));

  // ALINEA g)
  avl_remove(avl, "N");

  // ALINEA h)  
  avl_remove(avl, "V");

  return 0;
}