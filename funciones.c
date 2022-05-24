#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

BTree* arr_ascii_chars() {
  BTree* ascii_chars = malloc(sizeof(BTree) * 256);
  for (int i = 0; i < 256; i++) {
    BTree nuevoArbol = malloc(sizeof(struct _BTNodo));
    nuevoArbol->caracter = (char) i;
    nuevoArbol->frecuencia = 0;
    nuevoArbol->left = NULL;
    nuevoArbol->right = NULL;

    ascii_chars[i] = nuevoArbol;
  }
  return ascii_chars;
}

void arr_ascii_chars_frec(char* res, int len, BTree* ascii_chars) {
  for (int i = 0; i < len; i++) {
    ascii_chars[(int) res[i]]->frecuencia += 1;
  }
}

BTree* arr_merge(BTree *a1, int l1, BTree *a2, int l2) {
  BTree *r = malloc((l1+l2) * sizeof r[0]);
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

/* Devuelve una copia de [a] */
BTree* arr_mergesort(BTree *a, int n) {
	assert (n > 0);
	if (n < 2) {
		BTree *r = malloc(n * sizeof r[0]);
		r[0] = a[0];
		return r;
	}

	int m = n/2;
	BTree *ll = arr_mergesort(a, m);
	BTree *rr = arr_mergesort(a+m, n-m);

	BTree *mm = arr_merge(ll, m, rr, n-m);

	free(ll);
	free(rr);

	return mm;
}

//Funcion que llame a btree_unir con el nodo "vacio" y los 2 primeros arboles del arr
//Insertar el nuevo arbol de manera ordenada. Repetir hasta que el arr sea de largo 1 el
//cual sera el arbol construido.

//Representamos la union de arboles como ():
// [7,6,5,4,3,2,1,0] -> [7,6,5,4,3,2,(1),1,0] -> [7,6,5,4,3,2,(1)] -> [7,6,5,4,(3),3,2,(1)] -> [7,6,5,4,(3),3]
// -> [7,(6),6,5,4,(3),3] -> [7,(6),6,5,4] -> [(9),7,(6),6,5,4] -> [(9),7,(6),6] -> [(12),(9),7,(6),6] -> [(12),(9),7]
// -> [(12),(9),7] -> [(16),(12),(9),7] -> [(16),(12)] -> [(28),(16),(12)] -> [(28)] -> (28)

void arr_insertar_ordenadamente(BTree* ascii_chars, BTree nuevoArbol, int len) {
  for (int i = len - 1; i >= 0; i--) {
    if (nuevoArbol->frecuencia >= ascii_chars[i]->frecuencia) {
      for (int j = len - 1; j != i; j--) {
        ascii_chars[j] = ascii_chars[j-1];
      }
      ascii_chars[i] = nuevoArbol;
    }
  }
}

BTree huff_chars_tree (BTree* ascii_chars) {
  int len = 256;
  while (len > 1) {
    BTree nuevoArbol = btree_unir('\0', ascii_chars[len - 1], ascii_chars[len - 2]);
    printf("Frecuencia: %d\n", nuevoArbol->frecuencia);
    len = len - 1;
    arr_insertar_ordenadamente(ascii_chars, nuevoArbol, len);
  }
  return ascii_chars[0];
}