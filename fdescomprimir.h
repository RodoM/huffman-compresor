#ifndef __FDESCOMPRIMIR_H_
#define __FDESCOMPRIMIR_H_

BTree descomprimir_arbol(char* forma,int* len_forma, char *contenido,
                        int* len_contenido);

char* decodificar_archivo(BTree arbolReconstruido, int codificacionLen,
                          char* codificacion, int* decodificacion_len);

#endif
