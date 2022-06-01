#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "btree.h"
#include "fcomprimir.h"
#include "fdescomprimir.h"
#include "io.h"

void imprimir(int valor, int frecuencia) {
  printf("%d, %d\n", valor, frecuencia);
}

int main(int argc, char **argv) {

  if (!strcmp(argv[1], "C")) {
    assert(argc == 3);
    int len = 0;
    char *res = readfile(argv[2], &len);

    BTree *asciiChars = arr_ascii_chars();

    arr_ascii_chars_frec(res, len, asciiChars);

    BTree *asciiCharsOrdenado = arr_mergesort(asciiChars, 256);

    BTree arbolGenerado = huff_chars_tree(asciiCharsOrdenado);

    char **codificaciones = malloc(sizeof(char *) * 256);

    char *codificacion = malloc(sizeof(char) * btree_altura(arbolGenerado));

    char *valoresSerializados = malloc(sizeof(char) * 257);
    valoresSerializados[0] = 0;
    int lenCodificacion = 0;
    int cantHojas = 0;
    codificar_valores(arbolGenerado, codificacion, valoresSerializados,
                      &cantHojas, &lenCodificacion, codificaciones);

    free(codificacion);

    valoresSerializados[256] = '\0';

    int cantNodos = btree_nnodos(arbolGenerado);

    char *cadenaCodificada =
        codificar_archivo(codificaciones, res, len,
                          btree_altura(arbolGenerado));

    for (int i = 0; i < 256; i++)
      free(codificaciones[i]);

    free(codificaciones);

    free(res);

    int codificacionImplosionadaLen = 0;
    char *codificacionImplosionada =
        implode(cadenaCodificada, (int) strlen(cadenaCodificada),
                &codificacionImplosionadaLen);

    free(cadenaCodificada);
    char *nombreArchivo = malloc((sizeof(char) * strlen(argv[2])) + 2);
    nombreArchivo = strcat(argv[2], ".hf");
    writefile(nombreArchivo, codificacionImplosionada,
              codificacionImplosionadaLen);

    // free(nombreArchivo);
    free(codificacionImplosionada);

    char *arbolSerializado = malloc(sizeof(int) * cantNodos);
    arbolSerializado[0] = 0;
    serializar_arbol(arbolGenerado, arbolSerializado);

    btree_destruir(arbolGenerado);
    free(asciiChars);
    free(asciiCharsOrdenado);

    int serializacionLen = 256 + cantNodos;
    char *serializacion = malloc(sizeof(char) * serializacionLen);
    serializacion[0] = 0;
    memcpy(serializacion, arbolSerializado, 511 * sizeof(char));
    memcpy(serializacion + 511, valoresSerializados, 256 * sizeof(char));

    free(valoresSerializados);
    free(arbolSerializado);

    char *nombreArchivoTree = malloc((sizeof(char) * strlen(argv[2])) + 2);
    nombreArchivoTree = strcat(argv[2], ".tree");
    writefile(nombreArchivoTree, serializacion, serializacionLen);

    free(serializacion);
  }

  else if (!strcmp(argv[1], "D")) {
    assert(argc == 4);
    int codificacionLen = 0;
    char *codificacion = readfile(argv[2], &codificacionLen);
    int codificacionExplosionadaLen = 0;
    char *codificacionExplosionada =
        explode(codificacion, codificacionLen, &codificacionExplosionadaLen);

    free(codificacion);

    int serializacionLen = 0;
    char *serializaciones = readfile(argv[3], &serializacionLen);

    char *arbolSerializado = malloc(sizeof(char) * 512);
    strncpy(arbolSerializado, serializaciones, 511);

    char *valoresSerializados = malloc(sizeof(char) * 257);
    memcpy(valoresSerializados, &(serializaciones[511]), 256 * sizeof(char));
    valoresSerializados[256] = '\0';

    free(serializaciones);

    int formaLen = 0;
    int contenidoLen = 0;
    BTree arbolReconstruido =
        descomprimir_arbol(arbolSerializado, &formaLen, valoresSerializados,
                           &contenidoLen);

    free(arbolSerializado);
    free(valoresSerializados);
    int decodificacion_len = 0;
    char *decodificacion =
        decodificar_archivo(arbolReconstruido, codificacionExplosionadaLen,
                            codificacionExplosionada, &decodificacion_len);
    free(codificacionExplosionada);
    btree_destruir(arbolReconstruido);

    writefile("f.txt.dec", decodificacion, decodificacion_len);

    free(decodificacion);
  }

  return 0;
}
