#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "btree.h"

BTree descomprimir_arbol(char* forma, int *formaLen, char *contenido, int* contenidoLen) {
		if (forma[*formaLen] == '1'){
			BTree nuevoNodo = malloc(sizeof(struct _BTNodo));
			unsigned char c = contenido[*contenidoLen];
			nuevoNodo->valor = (int) c;
			nuevoNodo->frecuencia = 0;
			nuevoNodo->izq = NULL;
			nuevoNodo->der = NULL;
			*contenidoLen += 1;
			return nuevoNodo;
		}
		*formaLen += 1;
		BTree arbolIzq = descomprimir_arbol(forma, formaLen, contenido, contenidoLen);
		*formaLen += 1;
		BTree arbolDer = descomprimir_arbol(forma, formaLen, contenido, contenidoLen);
		BTree arbol = btree_unir(-1, arbolIzq, arbolDer);
		return arbol;
}

char* decodificar_archivo(BTree arbolReconstruido, int codificacionLen, char* codificacionExplosionada, int* decodificacionLen) {
	int sz = 1024;
	char* decodificado = malloc(sizeof(char) * sz);
	int indexCodificacion = 0;
	BTree nodoApuntado = arbolReconstruido;
	while (indexCodificacion < codificacionLen) {
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
			if (*decodificacionLen == sz) {
				sz = sz * 2;
				decodificado = realloc(decodificado, sizeof(char) * sz);
			}
			decodificado[*decodificacionLen] = (char)nodoApuntado->valor;
			*decodificacionLen += 1;
			nodoApuntado = arbolReconstruido;
		}
	}
	return decodificado;
}
