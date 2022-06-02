#include <assert.h>
#include <stdlib.h>
#include "btree.h"
#include "fcomprimir.h"
#include "fdescomprimir.h"

#include <stdio.h>

int main() {
  char cadenaDePrueba[6] = "testeo";
  BTree *arrAscii = arr_ascii();
  arr_ascii_frec(cadenaDePrueba, 6, arrAscii);
  assert(arrAscii[101]->frecuencia == 2); // 'e'
  assert(arrAscii[111]->frecuencia == 1); // 'o'
  assert(arrAscii[115]->frecuencia == 1); // 's'
  assert(arrAscii[116]->frecuencia == 2); // 't'

  BTree *arrAsciiOrdenado = mergesort(arrAscii, 256);
  BTree arbolGenerado = huffman_tree(arrAsciiOrdenado);

  char **codificaciones = malloc(sizeof(char *) * 256);
  char *codificacion = malloc(sizeof(char) * btree_altura(arbolGenerado));
  char *valoresSerializados = malloc(sizeof(char) * 257);
  valoresSerializados[0] = 0;
  int codificacionLen = 0;
  int cantHojas = 0;
  codificar_valores(arbolGenerado, codificacion, valoresSerializados,
                    &cantHojas, &codificacionLen, codificaciones);
  free(codificacion);
  valoresSerializados[256] = '\0';

  // printf("%s\n", )

  return 0;
}