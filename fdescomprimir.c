#include <stdlib.h>
#include <stdio.h>
#include "btree.h"

BTree descomprimir_arbol(char* forma, int len_forma, char contenido, int* len_contenido) {
	if (forma[*len_forma] == 1){
		BTree nuevo_nodo = malloc(sizeof(struct _BTNodo));
		unsigned char c = contenido[*len_contenido];
		nuevo_nodo->valor = (int) c;
		nuevo_nodo->frecuencia = 0;
		nuevo_nodo->izq = NULL;
		nuevo_nodo->der = NULL;
		*len_forma += 1;
		*len_contenido += 1;
		return nuevo_nodo;
	}
	*len_forma += 1;
	BTree arbol_izquierdo = descomprimir_arbol(forma, len_forma, contenido, len_contenido);
	*len_forma += 1;
	BTree arbol_derecho = descomprimir_arbol(forma, len_forma, contenido, len_contenido);
	BTree arbol = btree_unir('\0', arbol_izquierdo, arbol_derecho);

	return arbol;
} 