#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "btree.h"
#include "funciones.h"

static void imprimir_entero(char caracter) {
  printf("%c ", caracter);
}

static inline void quit(const char *s) {
	perror(s);
	exit(1);
}

char * readfile(const char *path, int *len) {
	int sz = 1024;
	char *buf = malloc(sz);
	FILE *f = fopen(path, "rb");
	int c, i = 0;

	if (f == NULL)
		quit("readfile.fopen");

	while ((c = getc(f)) != EOF) {
		if (i == sz) {
			sz = sz * 2;
			buf = realloc(buf, sz);
		}
		buf[i++] = c;
	}

	fclose(f);

	*len = i;
	return buf;
}

int main() {

  int len = 0;
  char* res = readfile("/home/rodom/Escritorio/TP_EDyA_2022/asd", &len);
  // printf("%s, %d\n", res, len);

	BTree* ascii_chars = arr_ascii_chars();
	//Aumentamos las frecuencias.
	arr_ascii_chars_frec(res, len, ascii_chars);

  // printf("SIN ORDENAR\n");
	// for (int i = 0; i < 256; i++) {
  //   printf("ASCII: %d (%c, %d)\n", i, ascii_chars[i]->caracter, ascii_chars[i]->frecuencia);
  // }
  // printf("--------------------------------\n");
  // printf("ORDENADO\n");

	//Ordenamos el arr por frecuencias de mayor a menor.
	BTree* ascii_chars_ordenado = arr_mergesort(ascii_chars, 256);

  BTree arbolGenerado = huff_chars_tree(ascii_chars);
  // btree_recorrer(arbolGenerado, BTREE_RECORRIDO_IN, imprimir_entero);
  // puts("");
	// for (int i = 0; i < 256; i++) {
  //   printf("ASCII: %d (%c, %d)\n", i, ascii_chars_ordenado[i]->caracter, ascii_chars_ordenado[i]->frecuencia);
  // }

  return 0;
}