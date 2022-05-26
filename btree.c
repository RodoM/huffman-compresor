#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

BTree btree_crear() {
  return NULL;
}

void btree_destruir(BTree nodo) {
  if (nodo != NULL) {
    btree_destruir(nodo->left);
    btree_destruir(nodo->right);
    free(nodo);
  }
}

// La primera vez que se llama, left y right son NULL.
BTree btree_unir(char caracter, BTree left, BTree right) {
  BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
  assert(nuevoNodo != NULL);
  nuevoNodo->caracter = caracter;
  nuevoNodo->frecuencia = left->frecuencia + right->frecuencia;
  nuevoNodo->left = left;
  nuevoNodo->right = right;
  return nuevoNodo;
}

void btree_inorder(BTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    btree_inorder(arbol->left, visit);
    visit(arbol->caracter, arbol->frecuencia);
    btree_inorder(arbol->right, visit);
  }
}

void btree_preorder(BTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    visit(arbol->caracter, arbol->frecuencia);
    btree_preorder(arbol->left, visit);
    btree_preorder(arbol->right, visit);
  }
}

void btree_postorder(BTree arbol, FuncionVisitante visit) {
  if (arbol != NULL) {
    btree_postorder(arbol->left, visit);
    btree_postorder(arbol->right, visit);
    visit(arbol->caracter, arbol->frecuencia);
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

BTree btree_copiar(BTree arbol) {
  if (arbol == NULL) { return NULL; }
  BTree arbolCopia = malloc(sizeof(struct _BTNodo));
  arbolCopia->caracter = arbol->caracter;
  arbolCopia->frecuencia = arbol->frecuencia;
  arbolCopia->left = btree_copiar(arbol->left);
  arbolCopia->right = btree_copiar(arbol->right);
  return arbolCopia;
}