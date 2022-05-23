#include <stdlib.h>
#include <stdio.h>
#include "tupla.h"
#include "btree.h"

Tupla* tupla_ascii_chars(Tupla tupla) {
  Tupla ascii_chars[256];
  for (int i = 0; i < 256; i++) {
    Tupla* nuevaTupla = malloc(sizeof(Tupla));

    BTree nuevoArbol = btree_crear();
    nuevoArbol = btree_unir((unsigned char) i, NULL, NULL);

    nuevaTupla->arbol = nuevoArbol;
    nuevaTupla->frecuencia = 0;
    ascii_chars[i] = *nuevaTupla;
  }
  return ascii_chars;
}

Tupla* tupla_merge(Tupla *a1, int l1, Tupla *a2, int l2) {
	Tupla *r = malloc((l1+l2) * sizeof r[0]);
	int i, j, k;
	i = 0;
	j = 0;
	k = 0;

	while (i < l1 && j < l2) {
		if (a1[i].frecuencia < a2[j].frecuencia) {
			r[k] = a1[i];
			i++;
			k++;
			/* o mejor: r[k++] = a1[i++] */
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
Tupla* tupla_mergesort(Tupla *a, int n) {
	assert (n > 0);
	if (n < 2) {
		Tupla *r = malloc(n * sizeof r[0]);
		r[0] = a[0];
		return r;
	}

	int m = n/2;
	Tupla *ll = mergesort(a, m);
	Tupla *rr = mergesort(a+m, n-m);

	Tupla *mm = merge(ll, m, rr, n-m);

	free(ll);
	free(rr);

	return mm;
}

//Funcion que combine las tuplas con la menor frecuencia y acorte el array original
/*
 * (a,0) (b,0) (c,1) (d,2) (e,2) (f,3)
 * (a,b,0) (c,1) (d,2) (e,2) (f,3)
 * (a,b,c,1) (d,2) (e,2) (f,3)
 * (e,2) (a,b,c,d,3) (f,3)
 * (f,3) (a,b,c,d,e,5)
 * (a,b,c,d,e,f,8)  <-- 'f' la hoja mas arriba
 */
