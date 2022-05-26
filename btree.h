#ifndef __BTREE_H_
#define __BTREE_H_

typedef void (*FuncionVisitante)(char caracter, int frecuencia);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

struct _BTNodo {
  int caracter;
  int frecuencia;
  struct _BTNodo *left;
  struct _BTNodo *right;
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
 * Crea un nuevo arbol, con el caracter dado en el nodo raiz, y los subarboles dados
 * a izquierda y derecha.
 */
BTree btree_unir(int caracter, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

/**
 * Retorna la altura de un arbol.
 */
int btree_altura(BTree arbol);

/**
 * Crea y retorna una copia del arbol pasado como argumento.
 */
BTree btree_copiar(BTree arbol);    

#endif