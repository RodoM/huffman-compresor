#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct {
  __attribute__((unused)) char valor;
  int frecuencia;
} Tupla;

int main() {
  Tupla tupla;
  tupla.frecuencia = 2;

  printf("valor: %s, Frecuencia: %d\n", tupla.valor, tupla.frecuencia);

  return 0;
}