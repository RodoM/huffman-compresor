#ifndef __FCOMPRIMIR_H_
#define __FCOMPRIMIR_H_

BTree *arr_ascii_chars();

void arr_ascii_chars_frec(char *res, int len, BTree * asciiChars);

BTree *arr_merge(BTree * a1, int l1, BTree * a2, int l2);

BTree *arr_mergesort(BTree * asciiChars, int n);

BTree huff_chars_tree(BTree * asciiChars);

void codificar_valores(BTree arbolGenerado, char *codificacion,
                       char *serializacion, int *cantidadHojas,
                       int *codificacionLen, char **arrCodificaciones);

char *codificar_archivo(char **arrCodificaciones, char *fileArr, int fileLen,
                        int maxLen);

void serializar_arbol(BTree arbolGenerado, char *codificado);

#endif
