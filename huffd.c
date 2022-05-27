#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io.h"
// #include "fdescomprimir.h"

int main() {
  int codificacion_len = 0;
  char* codificacion = readfile("f.txt.hf", &codificacion_len);

  int codificacion_explosionada_len = 0;
  char* codificacion_explosionada = explode(codificacion, codificacion_len, &codificacion_explosionada_len);
  printf("codificacion: %s\n", codificacion_explosionada);

  int serializacion_len = 0;
	char* serializaciones = readfile("f.txt.tree", &serializacion_len);
	printf("serializaciones: %s\n", serializaciones);

  printf("\n-----------------Aca separo las cosas-----------------\n");

  char* arbol_serializado = malloc(sizeof(char)*511);
  strncpy(arbol_serializado, serializaciones, 511);
  arbol_serializado[511] = '\0';
  printf("arbol: %s\n", arbol_serializado);

  char* valores_serializados = malloc(sizeof(char)*255);
  strncpy(valores_serializados, &serializaciones[511], 255);
  // arbol_serializado[255] = '\0';
  printf("valores: %s\n", valores_serializados);
}