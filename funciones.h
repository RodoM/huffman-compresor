#ifndef __FUNCIONES_H_
#define __FUNCIONES_H_

BTree* arr_ascii_chars();

void arr_ascii_chars_frec(char* res, int len, BTree* ascii_chars);

BTree* arr_merge(BTree *a1, int l1, BTree *a2, int l2);

BTree* arr_mergesort(BTree *a, int n);

BTree huff_chars_tree (BTree* ascii_chars);

void codificar_caracteres(BTree arbolGenerado, char* codificacion, int* len_codificacion, int* len_max, char** arr_codificaciones);

#endif