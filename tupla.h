#ifndef __TUPLA_H_
#define __TUPLA_H_

typedef struct {
  BTree arbol;
  int frecuencia;
} Tupla;

Tupla * merge(Tupla *a1, int l1, Tupla *a2, int l2);

Tupla * mergesort(Tupla *a, int n);

#endif