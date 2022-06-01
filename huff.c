#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "btree.h"
#include "fcomprimir.h"
#include "fdescomprimir.h"
#include "io.h"

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
    int codificacionLen = 0;
    int cantHojas = 0;
    codificar_valores(arbolGenerado, codificacion, valoresSerializados,
                      &cantHojas, &codificacionLen, codificaciones);

    free(codificacion);

    valoresSerializados[256] = '\0';

    int cantidadNodos = btree_nnodos(arbolGenerado);

    int codificacionValorLen = 0;
    char *cadenaCodificada =
        codificar_archivo(codificaciones, res, len,
                          btree_altura(arbolGenerado), &codificacionValorLen);

    for (int i = 0; i < 256; i++)
      free(codificaciones[i]);

    free(codificaciones);

    free(res);

    int codificacionImplosionadaLen = 0;
    char *codificacionImplosionada =
        implode(cadenaCodificada, codificacionValorLen,
                &codificacionImplosionadaLen);

    free(cadenaCodificada);

    int nombreArchivoLen = strlen(argv[2]);
    char *nombreArchivoC = malloc((sizeof(char) * nombreArchivoLen) + 4);
    memcpy(nombreArchivoC, argv[2], nombreArchivoLen);
    memcpy(nombreArchivoC + nombreArchivoLen, ".hf", 3);
    nombreArchivoC[nombreArchivoLen + 3] = '\0';
    writefile(nombreArchivoC, codificacionImplosionada,
              codificacionImplosionadaLen);

    free(nombreArchivoC);
    free(codificacionImplosionada);

    char *arbolSerializado = malloc(sizeof(int) * cantidadNodos);
    arbolSerializado[0] = 0;
    serializar_arbol(arbolGenerado, arbolSerializado);

    btree_destruir(arbolGenerado);
    free(asciiChars);
    free(asciiCharsOrdenado);

    int serializacionLen = 256 + cantidadNodos;
    char *serializacion = malloc(sizeof(char) * serializacionLen);
    serializacion[0] = 0;
    memcpy(serializacion, arbolSerializado, 511 * sizeof(char));
    memcpy(serializacion + 511, valoresSerializados, 256 * sizeof(char));

    free(valoresSerializados);
    free(arbolSerializado);

    char *nombreArchivoT = malloc((sizeof(char) * strlen(argv[2])) + 6);
    memcpy(nombreArchivoT, argv[2], nombreArchivoLen);
    memcpy(nombreArchivoT + nombreArchivoLen, ".tree", 5);
    nombreArchivoT[nombreArchivoLen + 5] = '\0';
    writefile(nombreArchivoT, serializacion, serializacionLen);

    free(nombreArchivoT);
    free(serializacion);
  }

  else if (!strcmp(argv[1], "D")) {
    assert(argc == 3);
    int codificacionLen = 0;
    char *codificacion = readfile(argv[2], &codificacionLen);
    int codificacionExplosionadaLen = 0;
    char *codificacionExplosionada =
        explode(codificacion, codificacionLen, &codificacionExplosionadaLen);

    free(codificacion);

    int serializacionLen = 0;
    int nombreArchivoLen = strlen(argv[2]);
    char* nombreArchivoT = malloc((sizeof(char) * nombreArchivoLen) + 3);
    memcpy(nombreArchivoT, argv[2], nombreArchivoLen - 2);
    memcpy(nombreArchivoT + nombreArchivoLen - 2, "tree", 4);
    nombreArchivoT[nombreArchivoLen + 2] = '\0';
    char *serializaciones = readfile(nombreArchivoT, &serializacionLen);

    free(nombreArchivoT);

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
    int decodificacionLen = 0;
    char *decodificacion =
        decodificar_archivo(arbolReconstruido, codificacionExplosionadaLen,
                            codificacionExplosionada, &decodificacionLen);
    free(codificacionExplosionada);
    btree_destruir(arbolReconstruido);

    char* nombreArchivoD = malloc((sizeof(char)*nombreArchivoLen) + 2);
    memcpy(nombreArchivoD, argv[2], nombreArchivoLen - 2);
    memcpy((nombreArchivoD + nombreArchivoLen) - 2, "dec", 3);
    nombreArchivoD[nombreArchivoLen + 1] = '\0';

    writefile(nombreArchivoD, decodificacion, decodificacionLen);

    free(nombreArchivoD);
    free(decodificacion);
  }

  return 0;
}
