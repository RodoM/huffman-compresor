#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "btree.h"
#include "funciones.h"
#include "io.h"

static inline void quit(const char *s) {
	perror(s);
	exit(1);
}

int main() {

	int len = 0;
	char* res = readfile("asd", &len);

	BTree* ascii_chars = arr_ascii_chars();
	
	//Aumentamos las frecuencias.
	arr_ascii_chars_frec(res, len, ascii_chars);

	//Ordenamos el arr por frecuencias de mayor a menor.
	BTree* ascii_chars_ordenado = arr_mergesort(ascii_chars, 256);

	BTree arbolGenerado = huff_chars_tree(ascii_chars_ordenado); 
	//btree destruir por cada arbol.
	// btree_recorrer(arbolGenerado, BTREE_RECORRIDO_IN, imprimir_caracter);
	// puts("");
		// for (int i = 0; i < 256; i++) {
	//   printf("ASCII: %d (%c, %d)\n", i, ascii_chars_ordenado[i]->caracter, ascii_chars_ordenado[i]->frecuencia);
	// }

	char** arr_codificaciones = malloc(sizeof(char*)*256);
	char* codificacion = malloc(sizeof(char) * btree_altura(arbolGenerado));
	int len_codificacion = 0;

	codificar_caracteres(arbolGenerado, codificacion, &len_codificacion, arr_codificaciones);
	
	for (int i = 0; i < 256; i++)
		printf("%d - %c, %s\n", i, i, arr_codificaciones[i]);

	char* cadena_codificada = codificar_archivo(arr_codificaciones, res, len);
	printf("cadena codificada: %s\n", cadena_codificada);

  return 0;
}