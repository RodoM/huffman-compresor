#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "btree.h"

BTree descomprimir_arbol(char* forma, int *len_forma, char *contenido,
												int* len_contenido) {
		if (forma[*len_forma] == '1'){
			BTree nuevo_nodo = malloc(sizeof(struct _BTNodo));
			unsigned char c = contenido[*len_contenido];
			nuevo_nodo->valor = (int) c;
			nuevo_nodo->frecuencia = 0;
			nuevo_nodo->izq = NULL;
			nuevo_nodo->der = NULL;
			//printf("%d\n", *len_contenido);
			*len_contenido += 1;
			return nuevo_nodo;
		}
		*len_forma += 1;
		BTree arbol_izquierdo = descomprimir_arbol(forma, len_forma, contenido,
																							len_contenido);
		*len_forma += 1;
		BTree arbol_derecho = descomprimir_arbol(forma, len_forma, contenido,
																						len_contenido);
		BTree arbol = btree_unir(-1, arbol_izquierdo, arbol_derecho);
		return arbol;
}

char* decodificar_archivo(BTree arbolReconstruido, int codificacionExplosionadaLen, char* codificacionExplosionada, int* indexDecodificacion) {
	int sz = 1024;
	char* decodificado = malloc(sizeof(char) * sz);
	int indexCodificacion = 0;
	BTree nodoApuntado = arbolReconstruido;
	while (indexCodificacion < codificacionExplosionadaLen) {
		if (nodoApuntado->izq != NULL && nodoApuntado->der != NULL) {
			if (codificacionExplosionada[indexCodificacion] == '0') {
				nodoApuntado = nodoApuntado->izq;
				indexCodificacion += 1;
			}
			else if (codificacionExplosionada[indexCodificacion] == '1' && nodoApuntado->der != NULL) {
				nodoApuntado = nodoApuntado->der;
				indexCodificacion += 1;
			}
		}
		if (nodoApuntado->izq == NULL && nodoApuntado->der == NULL) {
			if (*indexDecodificacion == sz) {
				sz = sz * 2;
				decodificado = realloc(decodificado, sizeof(char) * sz);
			}
			decodificado[*indexDecodificacion] = (char)nodoApuntado->valor;
			*indexDecodificacion += 1;
			nodoApuntado = arbolReconstruido;
		}
	}
	return decodificado;
}
