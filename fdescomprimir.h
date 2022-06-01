#ifndef __FDESCOMPRIMIR_H_
#define __FDESCOMPRIMIR_H_

/*
* Reconstruye el arbol segun el archivo .tree
*/
BTree descomprimir_arbol(char *forma, int *formaLen, char *contenido,
                         int *contenidoLen);

/*
* Encargada de recorrer el arbol reconstruido junto a la codificacion e ir
* obteniendo la decodificacion de los valores.
*/
char *decodificar_archivo(BTree arbolReconstruido, int codificacionLen,
                          char *codificacion, int *decodificacionLen);

#endif
