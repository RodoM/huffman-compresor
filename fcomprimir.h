#ifndef __FCOMPRIMIR_H_
#define __FCOMPRIMIR_H_

/*
* Retorna un array de btrees ordenado segun ascii, cada uno de ellos es un 
* caracter ascii.
*/
BTree *arr_ascii_chars();

/*
* Aumenta las frecuencias de los arboles cuyo valor se encuentra en el buffer
* creado por el archivo de entrada.
*/
void arr_ascii_chars_frec(char *res, int len, BTree * asciiChars);

/*
* Funcion auxiliar para mergesort que se encarga de tomar dos arrays y devuelve
* uno con sus elementos ordenados.
*/
BTree *arr_merge(BTree * a1, int l1, BTree * a2, int l2);

/*
* Ordena el array de arboles por frecuencia de mayor a menor.
*/
BTree *arr_mergesort(BTree * asciiChars, int n);

/*
* Crea el arbol siguiendo el algoritmo de Huffman.
*/
BTree huff_chars_tree(BTree * asciiChars);

/*
* Obtiene la codificacion de cada valor de los caracteres ascii.
* A su vez devuelve la serializacion de los valores de las hojas.
*/
void codificar_valores(BTree arbolGenerado, char *codificacion,
                       char *serializacion, int *cantidadHojas,
                       int *codificacionLen, char **arrCodificaciones);

/*
* Se encarga de leer el buffer y escribe en un nuevo array su codificacion
* segun el arbol.
*/
char *codificar_archivo(char **arrCodificaciones, char *fileArr, int fileLen,
                        int maxLen, int *codificacionValorLen);

/*
* Obtiene la serializacion de la forma del arbol.
*/
void serializar_arbol(BTree arbolGenerado, char *codificado);

#endif
