#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct {
  __attribute__((unused)) char caracter;
  int frecuencia;
} Tupla;

int main() {
  Tupla tupla;
  tupla.frecuencia = 2;

  printf("Caracter: %s, Frecuencia: %d\n", tupla.caracter, tupla.frecuencia);

  return 0;
}