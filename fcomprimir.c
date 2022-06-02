#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

BTree *arr_ascii() {
  BTree *arrAscii = malloc(sizeof(BTree) * 256);
  for (int i = 0; i < 256; i++) {
    BTree nuevoArbol = malloc(sizeof(struct _BTNodo));
    nuevoArbol->valor = i;
    nuevoArbol->frecuencia = 0;
    nuevoArbol->izq = NULL;
    nuevoArbol->der = NULL;

    arrAscii[i] = nuevoArbol;
  }
  return arrAscii;
}

void arr_ascii_frec(char *res, int len, BTree * arrAscii) {
  for (int i = 0; i < len; i++) {
    unsigned char c = res[i];
    int index = (int) c;
    arrAscii[index]->frecuencia += 1;
  }
}

BTree *merge(BTree * a1, int l1, BTree * a2, int l2) {
  BTree *r = malloc((l1 + l2) * sizeof r[0]);
  int i, j, k;
  i = 0;
  j = 0;
  k = 0;

  while (i < l1 && j < l2) {
    if (a1[i]->frecuencia > a2[j]->frecuencia) {
      r[k] = a1[i];
      i++;
      k++;
    } else {
      r[k] = a2[j];
      j++;
      k++;
    }
  }

  while (i < l1) {
    r[k] = a1[i];
    i++;
    k++;
  }
  while (j < l2) {
    r[k] = a2[j];
    j++;
    k++;
  }

  return r;
}

BTree *mergesort(BTree * arrAscii, int n) {
  assert(n > 0);
  if (n < 2) {
    BTree *r = malloc(n * sizeof r[0]);
    r[0] = arrAscii[0];
    return r;
  }

  int m = n / 2;
  BTree *ll = mergesort(arrAscii, m);
  BTree *rr = mergesort(arrAscii + m, n - m);

  BTree *mm = merge(ll, m, rr, n - m);

  free(ll);
  free(rr);

  return mm;
}

void arr_insertar_ordenadamente(BTree * arrAsciiOrdenado, BTree nuevoArbol,
                                int len) {
  int p;
  for (int i = 0; i < len; i++) {
    if (nuevoArbol->frecuencia >= arrAsciiOrdenado[i]->frecuencia) {
      p = i;
      break;
    } else {
      p = i + 1;
    }
  }
  for (int i = len - 1; i > p; i--)
    arrAsciiOrdenado[i] = arrAsciiOrdenado[i - 1];

  arrAsciiOrdenado[p] = nuevoArbol;
}

BTree huffman_tree(BTree * arrAsciiOrdenado) {
  int len = 256;
  while (len > 1) {
    BTree nuevoArbol = btree_unir(-1, arrAsciiOrdenado[len - 1],
                                  arrAsciiOrdenado[len - 2]);
    len = len - 1;
    arr_insertar_ordenadamente(arrAsciiOrdenado, nuevoArbol, len);
  }
  return arrAsciiOrdenado[0];
}

void codificar_valores(BTree arbolGenerado, char *codificacion,
                       char *serializacion, int *cantidadHojas,
                       int *codificacionLen, char **arrCodificaciones) {
  if (arbolGenerado->izq != NULL && arbolGenerado->der != NULL) {
    codificacion[*codificacionLen] = '0';
    *codificacionLen += 1;
    codificar_valores(arbolGenerado->izq, codificacion, serializacion,
                      cantidadHojas, codificacionLen, arrCodificaciones);
    *codificacionLen -= 1;

    codificacion[*codificacionLen] = '1';
    *codificacionLen += 1;
    codificar_valores(arbolGenerado->der, codificacion, serializacion,
                      cantidadHojas, codificacionLen, arrCodificaciones);
    *codificacionLen -= 1;
  }

  else if (arbolGenerado->izq == NULL && arbolGenerado->der == NULL) {
    arrCodificaciones[(int) arbolGenerado->valor] =
        malloc((sizeof(char) * *codificacionLen) + 1);
    memcpy(arrCodificaciones[(int) arbolGenerado->valor], codificacion,
           *codificacionLen);
    arrCodificaciones[(int) arbolGenerado->valor][*codificacionLen] = '\0';

    serializacion[*cantidadHojas] = arbolGenerado->valor;
    *cantidadHojas += 1;
  }
}

char *codificar_archivo(char **arrCodificaciones, char *fileArr, int fileLen,
                        int maxLen, int *codificacionValorLen) {
  int sz = fileLen * maxLen;
  char *codificado = malloc(sizeof(char) * sz);
  codificado[0] = 0;
  for (int i = 0; i < fileLen; i++) {
    unsigned char c = fileArr[i];
    int cod = strlen(arrCodificaciones[(int) c]);
    memcpy(codificado + *codificacionValorLen, arrCodificaciones[(int) c], cod);
    *codificacionValorLen += cod;
  }
  return codificado;
}

void serializar_arbol(BTree arbolGenerado, char *codificado) {
  if (arbolGenerado->izq == NULL && arbolGenerado->der == NULL) {
    strcat(codificado, "1");
  } else if (arbolGenerado->izq != NULL && arbolGenerado->der != NULL) {
    strcat(codificado, "0");
    serializar_arbol(arbolGenerado->izq, codificado);
    serializar_arbol(arbolGenerado->der, codificado);
  }
}
