#ifndef __FDESCOMPRIMIR_H_
#define __FDESCOMPRIMIR_H_

/*
*
*/
BTree descomprimir_arbol(char *forma, int *formaLen, char *contenido,
                         int *contenidoLen);

/*
*
*/
char *decodificar_archivo(BTree arbolReconstruido, int codificacionLen,
                          char *codificacion, int *decodificacionLen);

#endif
