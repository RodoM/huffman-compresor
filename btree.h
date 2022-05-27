#ifndef __BTREE_H_
#define __BTREE_H_

typedef void (*FuncionVisitante)(char valor, int frecuencia);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

struct _BTNodo {
  int valor;
  int frecuencia;
  struct _BTNodo *izq;
  struct _BTNodo *der;
};

typedef struct _BTNodo *BTree;

/**
 * Devuelve un arbol vacío.
 */
BTree btree_crear();

/**
 * Destruccion del árbol.
 */
void btree_destruir(BTree nodo);

/**
 * Crea un nuevo arbol, con el valor dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int valor, BTree izq, BTree der);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

/**
* Devuelve la cantidad de nodos de un arbol.
*/
int btree_nnodos(BTree arbol);

/**
 * Retorna la altura de un arbol.
 */
int btree_altura(BTree arbol);

/**
 * Crea y retorna una copia del arbol pasado como argumento.
 */
BTree btree_copiar(BTree arbol);    

#endif