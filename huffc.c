#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "fcomprimir.h"
#include "io.h"

int main() {
	
	//liberar luego de codificar_archivo()
	int len = 0;
	char* res = readfile("asd", &len);

	//liberar luego de ascii_chars_ordenado
	BTree* ascii_chars = arr_ascii_chars();
	
	arr_ascii_chars_frec(res, len, ascii_chars);

	//liberar luego de arbolGenerado
	BTree* ascii_chars_ordenado = arr_mergesort(ascii_chars, 256);

	//Liberar luego de arbol_serializado()
	BTree arbolGenerado = huff_chars_tree(ascii_chars_ordenado); 

	//liberar luego de codificar_archivo()
	char** arr_codificaciones = malloc(sizeof(char*)*256);

	//liberar luego de codificar_valores()
	char* codificacion = malloc(sizeof(char) * btree_altura(arbolGenerado));

	//Liberar al final de la ejecucion del programa
	char* valores_serializacion = malloc(sizeof(char)*256);
	valores_serializacion[0] = 0;
	int len_codificacion = 0;

	codificar_valores(arbolGenerado, codificacion, valores_serializacion, &len_codificacion, arr_codificaciones);

	int cant_nodos_arbol = btree_nnodos(arbolGenerado);

	//Liberar luego de implode
	char* cadena_codificada = codificar_archivo(arr_codificaciones, res, len);

	int codificacion_implosionada_len = 0;
	//Liberar luego del writefile de f.txt.hf
	char* codificacion_implosionada = implode(cadena_codificada, (int)strlen(cadena_codificada), &codificacion_implosionada_len);

	writefile("f.txt.hf", codificacion_implosionada, codificacion_implosionada_len);

	//Liberar al final de la ejecucion del programa
	char* arbol_serializado = malloc(sizeof(int)*cant_nodos_arbol);
	arbol_serializado[0] = 0;
	serializar_arbol(arbolGenerado, arbol_serializado);

	//Liberar al final de la ejecucion del programa
	int serializacion_len = 256 + cant_nodos_arbol;
	char* serializacion = malloc(sizeof(char)*serializacion_len);
	serializacion[0] = 0;
	strcat(serializacion, arbol_serializado);
	strcat(serializacion, valores_serializacion);
	writefile("f.txt.tree", serializacion, serializacion_len);

  return 0;
}