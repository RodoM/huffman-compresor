#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "fcomprimir.h"
#include "fdescomprimir.h"
#include "io.h"

int main(int argc, char **argv) {

  if (!strcmp(argv[1], "C")) {
    assert(argc == 3);

    int len = 0;
    char *res = readfile(argv[2], &len);
    
    //Inicio de la creacion del arbol.
    BTree *asciiChars = arr_ascii_chars();
    arr_ascii_chars_frec(res, len, asciiChars);
    BTree *asciiCharsOrdenado = arr_mergesort(asciiChars, 256);
    BTree arbolGenerado = huff_chars_tree(asciiCharsOrdenado);

    //Codificacion de los caracteres y serializacion de los valores de las
    //hojas.
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

    //Codificacion del archivo de entrada.
    int codificacionValorLen = 0;
    char *cadenaCodificada = codificar_archivo(codificaciones, res, len,
                                               btree_altura(arbolGenerado),
                                               &codificacionValorLen);
    for (int i = 0; i < 256; i++)
      free(codificaciones[i]);
    free(codificaciones);

    free(res);

    //Implosion de la cadena codificada.
    int codificacionImplosionadaLen = 0;
    char *codificacionImplosionada =
        implode(cadenaCodificada, codificacionValorLen,
                &codificacionImplosionadaLen);
    free(cadenaCodificada);

    //Creacion del archivo .hf.
    int nombreArchivoLen = strlen(argv[2]);
    char *nombreArchivoC = malloc((sizeof(char) * nombreArchivoLen) + 4);
    memcpy(nombreArchivoC, argv[2], nombreArchivoLen);
    memcpy(nombreArchivoC + nombreArchivoLen, ".hf", 3);
    nombreArchivoC[nombreArchivoLen + 3] = '\0';
    writefile(nombreArchivoC, codificacionImplosionada,
              codificacionImplosionadaLen);
    free(nombreArchivoC);
    free(codificacionImplosionada);

    //Serializacion de la forma del arbol.
    int cantidadNodos = btree_nnodos(arbolGenerado);
    char *arbolSerializado = malloc(sizeof(int) * cantidadNodos);
    arbolSerializado[0] = 0;
    serializar_arbol(arbolGenerado, arbolSerializado);
    //Destruccion del arbol.
    btree_destruir(arbolGenerado);
    free(asciiChars);
    free(asciiCharsOrdenado);

    //Concatenacion de las serializaciones.
    int serializacionLen = 256 + cantidadNodos;
    char *serializacion = malloc(sizeof(char) * serializacionLen);
    serializacion[0] = 0;
    memcpy(serializacion, arbolSerializado, 511 * sizeof(char));
    memcpy(serializacion + 511, valoresSerializados, 256 * sizeof(char));
    free(valoresSerializados);
    free(arbolSerializado);

    //Creacion del archivo .tree.
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

    //Lectura del archivo .hf.
    int codificacionLen = 0;
    char *codificacion = readfile(argv[2], &codificacionLen);

    //Explosion del archivo.
    int codificacionExplosionadaLen = 0;
    char *codificacionExplosionada =
        explode(codificacion, codificacionLen, &codificacionExplosionadaLen);
    free(codificacion);

    //Lectura del archivo .tree.
    int serializacionLen = 0;
    int nombreArchivoLen = strlen(argv[2]);
    char *nombreArchivoT = malloc((sizeof(char) * nombreArchivoLen) + 3);
    memcpy(nombreArchivoT, argv[2], nombreArchivoLen - 2);
    memcpy(nombreArchivoT + nombreArchivoLen - 2, "tree", 4);
    nombreArchivoT[nombreArchivoLen + 2] = '\0';
    char *serializaciones = readfile(nombreArchivoT, &serializacionLen);
    free(nombreArchivoT);

    //Obtencion de la serializacion de la forma del arbol.
    char *arbolSerializado = malloc(sizeof(char) * 512);
    strncpy(arbolSerializado, serializaciones, 511);

    //Obtencion de la serializacion de los valores de las hojas.
    char *valoresSerializados = malloc(sizeof(char) * 257);
    memcpy(valoresSerializados, &(serializaciones[511]), 256 * sizeof(char));
    valoresSerializados[256] = '\0';
    free(serializaciones);

    //Reconstruccion del arbol.
    int formaLen = 0;
    int contenidoLen = 0;
    BTree arbolReconstruido =
        descomprimir_arbol(arbolSerializado, &formaLen, valoresSerializados,
                           &contenidoLen);
    free(arbolSerializado);
    free(valoresSerializados);

    //Decodificacion del archivo.
    int decodificacionLen = 0;
    char *decodificacion =
        decodificar_archivo(arbolReconstruido, codificacionExplosionadaLen,
                            codificacionExplosionada, &decodificacionLen);
    free(codificacionExplosionada);
    btree_destruir(arbolReconstruido);

    //Creacion del archivo .dec.
    char *nombreArchivoD = malloc((sizeof(char) * nombreArchivoLen) + 2);
    memcpy(nombreArchivoD, argv[2], nombreArchivoLen - 2);
    memcpy((nombreArchivoD + nombreArchivoLen) - 2, "dec", 3);
    nombreArchivoD[nombreArchivoLen + 1] = '\0';
    writefile(nombreArchivoD, decodificacion, decodificacionLen);
    free(nombreArchivoD);
    free(decodificacion);
  }

  return 0;
}
