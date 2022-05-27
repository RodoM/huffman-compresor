#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "funciones.h"
#include "io.h"

int main() {
	
	int len = 0;
	char* res = readfile("asd", &len);

	BTree* ascii_chars = arr_ascii_chars();
	
	arr_ascii_chars_frec(res, len, ascii_chars);

	BTree* ascii_chars_ordenado = arr_mergesort(ascii_chars, 256);

	BTree arbolGenerado = huff_chars_tree(ascii_chars_ordenado); 
	//falta btree destruir por cada arbol.

	char** arr_codificaciones = malloc(sizeof(char*)*256);
	char* codificacion = malloc(sizeof(char) * btree_altura(arbolGenerado));
	char* valores_serializacion = malloc(sizeof(char)*256);
	valores_serializacion[0] = 0;
	int len_codificacion = 0;

	codificar_valores(arbolGenerado, codificacion, valores_serializacion, &len_codificacion, arr_codificaciones);
	
	// for (int i = 0; i < 256; i++)
	// 	printf("%d: %c, %s\n", i, i, arr_codificaciones[i]);

	int cant_nodos_arbol = btree_nnodos(arbolGenerado);
	char* arbol_serializado = malloc(sizeof(int)*cant_nodos_arbol);
	serializar_arbol(arbolGenerado, arbol_serializado);
	printf("arbol codificado: %s\n", arbol_serializado);

	printf("\nvalores serializados: %s\n", valores_serializacion);
	// for (int i = 0; i < strlen(valores_serializacion); i++) {
	// 	printf("%02x", valores_serializacion[i]);
	// }

	// printf("nodos arbol: %d, nodos arbol codificado: %d\n", cant_nodos_arbol, (int)strlen(arbol_serializado));

	char* cadena_codificada = codificar_archivo(arr_codificaciones, res, len);
	printf("cadena codificada: %s\n", cadena_codificada);

	int codificacion_implosionada_len = 0;
	char* codificacion_implosionada = implode(cadena_codificada, (int)strlen(cadena_codificada), &codificacion_implosionada_len);
	printf("implosion: %s\n", codificacion_implosionada);

	writefile("f.txt.hf", codificacion_implosionada, codificacion_implosionada_len);

	//char* que contenga el arbol y los valores, ambos serializados.
	writefile("f.txt.tree", arbol_serializado, cant_nodos_arbol);

	// int codificacion_explosionada_len = 0;
	// char* codificacion_explosionada = explode(codificacion_implosionada, codificacion_implosionada_len, &codificacion_explosionada_len);
	// printf("explosion: %s\n", codificacion_explosionada);



  return 0;
}