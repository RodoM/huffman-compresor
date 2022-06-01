#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->izq);
    btree_destruir(nodo->der);
    free(nodo);
  }
}

// La primera vez que se llama, izq y der son NULL.
BTree btree_unir(int valor, BTree izq, BTree der) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->valor = valor;
  nuevoNodo->frecuencia = izq->frecuencia + der->frecuencia;
  nuevoNodo->izq = izq;
  nuevoNodo->der = der;
  return nuevoNodo;
}

int btree_nnodos(BTree arbol) {
  int cantNodos = 1;
  if (arbol == NULL) {
    return 0;
  } else {
    cantNodos += btree_nnodos(arbol->izq);
    cantNodos += btree_nnodos(arbol->der);
    return cantNodos;
  }
}

int btree_altura(BTree arbol) {
  if (arbol == NULL) {
    return -1;
  } else {
    int izq = btree_altura(arbol->izq);
    int der = btree_altura(arbol->der);
    if (izq > der) { return izq + 1; }
    else { return der + 1; }
  }
}