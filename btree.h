#ifndef __BTREE_H_
#define __BTREE_H_

struct _BTNodo {
  int valor;
  int frecuencia;
  struct _BTNodo *izq;
  struct _BTNodo *der;
};

typedef struct _BTNodo *BTree;

/*
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/*
 * Crea un nuevo arbol, con el valor dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int valor, BTree izq, BTree der);

/*
* Devuelve la cantidad de nodos de un arbol.
*/
int btree_nnodos(BTree arbol);

/*
 * Retorna la altura de un arbol.
 */
int btree_altura(BTree arbol);

#endif
