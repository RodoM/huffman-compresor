#ifndef __BTREE_H_
#define __BTREE_H_

typedef void (*FuncionVisitante)(char caracter, int frecuencia);
typedef int (*FuncionMaximo)(int a, int b);
typedef void (*FuncionVisitanteExtra) (int caracter, void *extra);

typedef enum {
  BTREE_RECORRIDO_IN,
  BTREE_RECORRIDO_PRE,
  BTREE_RECORRIDO_POST
} BTreeOrdenDeRecorrido;

struct _BTNodo {
  char caracter;
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
BTree btree_unir(char caracter, BTree left, BTree right);

/**
 * Recorrido del arbol, utilizando la funcion pasada.
 */
void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden, FuncionVisitante visit);

/**
 * Crea y retorna una copia del arbol pasado como argumento.
 */
BTree btree_copiar(BTree arbol);    

#endif