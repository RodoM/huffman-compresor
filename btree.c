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

void btree_inorder(BTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    btree_inorder(arbol->izq, visit);
    visit(arbol->valor, arbol->frecuencia);
    btree_inorder(arbol->der, visit);
  }
}

void btree_preorder(BTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    visit(arbol->valor, arbol->frecuencia);
    btree_preorder(arbol->izq, visit);
    btree_preorder(arbol->der, visit);
  }
}

void btree_postorder(BTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    btree_postorder(arbol->izq, visit);
    btree_postorder(arbol->der, visit);
    visit(arbol->valor, arbol->frecuencia);
  }
}

void btree_recorrer(BTree arbol, BTreeOrdenDeRecorrido orden,
                    FuncionVisitante visit) {
  if (orden == BTREE_RECORRIDO_IN) {
    printf("Recorrido inorder:\n");
    btree_inorder(arbol, visit);
  }
  else if (orden == BTREE_RECORRIDO_PRE) {
    printf("Recorrido preorder:\n");
    btree_preorder(arbol, visit);
  }
  else if (orden == BTREE_RECORRIDO_POST){
    printf("Recorrido postorder:\n");
    btree_postorder(arbol, visit);
  }
  else {
    printf("No existe el tipo de recorrido especificado\n");
  }
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

BTree btree_copiar(BTree arbol) {
  if (arbol == NULL) { return NULL; }
  BTree arbolCopia = malloc(sizeof(struct _BTNodo));
  arbolCopia->valor = arbol->valor;
  arbolCopia->frecuencia = arbol->frecuencia;
  arbolCopia->izq = btree_copiar(arbol->izq);
  arbolCopia->der = btree_copiar(arbol->der);
  return arbolCopia;
}