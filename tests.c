#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"
#include "fcomprimir.h"
#include "fdescomprimir.h"

void test_arr_ascii_frec() {
  char cadenaDePrueba[6] = "testeo";
  BTree *arrAscii = arr_ascii();
  arr_ascii_frec(cadenaDePrueba, 6, arrAscii);
  assert(arrAscii[101]->frecuencia == 2);       // 'e'
  assert(arrAscii[111]->frecuencia == 1);       // 'o'
  assert(arrAscii[115]->frecuencia == 1);       // 's'
  assert(arrAscii[116]->frecuencia == 2);       // 't'
  assert(arrAscii[0]->frecuencia == 0);

  free(arrAscii);
}

void test_mergesort() {
  BTree *arboles = malloc(sizeof(BTree) * 2);
  BTree primero = malloc(sizeof(struct _BTNodo));
  BTree segundo = malloc(sizeof(struct _BTNodo));
  primero->der = NULL;
  primero->izq = NULL;
  segundo->der = NULL;
  segundo->izq = NULL;
  primero->valor = 0;
  primero->frecuencia = 4;
  segundo->valor = 1;
  segundo->frecuencia = 6;
  arboles[0] = primero;
  arboles[1] = segundo;
  assert(mergesort(arboles, 2)[0]->valor == 1);
  assert(mergesort(arboles, 2)[1]->valor == 0);
  primero->frecuencia = 7;
  assert(mergesort(arboles, 2)[0]->valor == 0);
  assert(mergesort(arboles, 2)[1]->valor == 1);

  free(arboles);
  free(primero);
  free(segundo);
}

void test_codificar_valores() {
  BTree hoja1 = malloc(sizeof(struct _BTNodo));
  BTree hoja2 = malloc(sizeof(struct _BTNodo));
  BTree hoja3 = malloc(sizeof(struct _BTNodo));
  BTree hoja4 = malloc(sizeof(struct _BTNodo));
  hoja1->der = hoja1->izq = hoja2->der = hoja2->izq = NULL;
  hoja3->der = hoja3->izq = hoja4->der = hoja4->izq = NULL;
  hoja1->valor = 0;
  hoja1->frecuencia = 2;
  hoja2->valor = 1;
  hoja2->frecuencia = 5;
  hoja3->valor = 2;
  hoja3->frecuencia = 1;
  hoja4->valor = 3;
  hoja4->frecuencia = 0;
  BTree izq = btree_unir(-1, hoja4, hoja3);
  BTree der = btree_unir(-1, hoja1, hoja2);
  BTree arbol = btree_unir(-1, izq, der);

  char **codificaciones = malloc(sizeof(char *) * 4);
  char *codif = malloc(sizeof(char) * 3);
  char *valoresSerializados = malloc(sizeof(char) * 5);
  valoresSerializados[0] = 0;
  int codificacionLen = 0;
  int cantHojas = 0;

  codificar_valores(arbol, codif, valoresSerializados, &cantHojas,
                    &codificacionLen, codificaciones);
  assert(strcmp(codificaciones[0], "10") == 0);
  assert(strcmp(codificaciones[3], "00") == 0);
  assert(strcmp(valoresSerializados, "3201"));
  assert(cantHojas == 4);

  free(hoja1);
  free(hoja2);
  free(hoja3);
  free(hoja4);
  for (int i = 0; i < 4; i++)
    free(codificaciones[i]);
  free(codificaciones);
  free(codif);
  free(valoresSerializados);
}

void test_codificar_archivo() {
  char *texto = malloc(sizeof(char) * 4);
  memcpy(texto, "Hola", 4);
  char **codificaciones = malloc(sizeof(char *) * 256);
  codificaciones[72] = malloc(sizeof(char) * 2);
  codificaciones[72] = "00";
  codificaciones[111] = malloc(sizeof(char) * 2);
  codificaciones[111] = "01";
  codificaciones[108] = malloc(sizeof(char) * 2);
  codificaciones[108] = "10";
  codificaciones[97] = malloc(sizeof(char) * 2);
  codificaciones[97] = "11";

  int len = 0;

  char *codificado = codificar_archivo(codificaciones, texto, 4, 8, &len);
  assert(strcmp(codificado, "00011011") == 0);
  assert(len == 8);

  free(texto);
  free(codificaciones);
  free(codificado);
}

void test_serializar_arbol() {
  BTree hoja1 = malloc(sizeof(struct _BTNodo));
  BTree hoja2 = malloc(sizeof(struct _BTNodo));
  BTree hoja3 = malloc(sizeof(struct _BTNodo));
  BTree hoja4 = malloc(sizeof(struct _BTNodo));
  hoja1->der = hoja1->izq = hoja2->der = hoja2->izq = NULL;
  hoja3->der = hoja3->izq = hoja4->der = hoja4->izq = NULL;
  hoja1->valor = 0;
  hoja1->frecuencia = 2;
  hoja2->valor = 1;
  hoja2->frecuencia = 5;
  hoja3->valor = 2;
  hoja3->frecuencia = 1;
  hoja4->valor = 3;
  hoja4->frecuencia = 0;
  BTree izq = btree_unir(-1, hoja4, hoja3);
  BTree der = btree_unir(-1, hoja1, hoja2);
  BTree arbol = btree_unir(-1, izq, der);

  char *codificado = malloc(sizeof(char) * 8);
  codificado[0] = 0;

  serializar_arbol(arbol, codificado);
  assert(strcmp(codificado, "0011011") == 0);

  free(hoja1);
  free(hoja2);
  free(hoja3);
  free(hoja4);
  free(codificado);
}

int btree_comp(BTree arbol1, BTree arbol2) {
  int res = 0;
  if (arbol1 == NULL && arbol2 == NULL)
    return 0;
  if (arbol1 != NULL && arbol2 == NULL)
    return 1;
  if (arbol1 == NULL && arbol2 != NULL)
    return 1;
  if (arbol1 == NULL && arbol2 == NULL) {
    if (arbol1->valor != arbol2->valor)
      return 1;
    res += btree_comp(arbol1->izq, arbol2->izq);
    res += btree_comp(arbol1->der, arbol2->der);
  }
  if (res > 1)
    return 1;
  return res;
}

void test_descomprimir_arbol() {
  char *forma = malloc(sizeof(char) * 7);
  memcpy(forma, "0011011", 7);
  char *valores = malloc(sizeof(char) * 4);
  memcpy(valores, "3201", 4);
  int lenforma = 0;
  int lenvalores = 0;

  BTree arbol = descomprimir_arbol(forma, &lenforma, valores, &lenvalores);

  BTree hoja1 = malloc(sizeof(struct _BTNodo));
  BTree hoja2 = malloc(sizeof(struct _BTNodo));
  BTree hoja3 = malloc(sizeof(struct _BTNodo));
  BTree hoja4 = malloc(sizeof(struct _BTNodo));
  hoja1->der = hoja1->izq = hoja2->der = hoja2->izq = NULL;
  hoja3->der = hoja3->izq = hoja4->der = hoja4->izq = NULL;
  hoja1->valor = 0;
  hoja1->frecuencia = 2;
  hoja2->valor = 1;
  hoja2->frecuencia = 5;
  hoja3->valor = 2;
  hoja3->frecuencia = 1;
  hoja4->valor = 3;
  hoja4->frecuencia = 0;
  BTree izq = btree_unir(-1, hoja4, hoja3);
  BTree der = btree_unir(-1, hoja1, hoja2);
  BTree arbol_prearmado = btree_unir(-1, izq, der);

  assert(btree_comp(arbol, arbol_prearmado) == 0);
  assert(lenforma == 6);
  assert(lenvalores == 4);

  free(forma);
  free(valores);
  free(hoja1);
  free(hoja2);
  free(hoja3);
  free(hoja4);
}

void test_decodificar_archivo() {
  BTree hoja1 = malloc(sizeof(struct _BTNodo));
  BTree hoja2 = malloc(sizeof(struct _BTNodo));
  BTree hoja3 = malloc(sizeof(struct _BTNodo));
  BTree hoja4 = malloc(sizeof(struct _BTNodo));
  hoja1->der = hoja1->izq = hoja2->der = hoja2->izq = NULL;
  hoja3->der = hoja3->izq = hoja4->der = hoja4->izq = NULL;
  hoja1->valor = 108;
  hoja1->frecuencia = 0;
  hoja2->valor = 97;
  hoja2->frecuencia = 0;
  hoja3->valor = 111;
  hoja3->frecuencia = 0;
  hoja4->valor = 72;
  hoja4->frecuencia = 0;
  BTree izq = btree_unir(-1, hoja4, hoja3);
  BTree der = btree_unir(-1, hoja1, hoja2);
  BTree arbol = btree_unir(-1, izq, der);


  char *codificacion = malloc(sizeof(char) * 8);
  memcpy(codificacion, "00011011", 8);
  int decodlen = 0;
  char *textoDecodificado =
      decodificar_archivo(arbol, 8, codificacion, &decodlen);
  textoDecodificado[decodlen] = '\0';
  char *texto = malloc(sizeof(char) * 5);
  memcpy(texto, "Hola", 5);

  assert(strcmp(textoDecodificado, texto) == 0);
  assert(decodlen == 4);

  free(hoja1);
  free(hoja2);
  free(hoja3);
  free(hoja4);
  free(codificacion);
  free(textoDecodificado);
  free(texto);
}

int main() {

  test_arr_ascii_frec();

  test_mergesort();

  test_codificar_valores();

  test_codificar_archivo();

  test_serializar_arbol();

  test_descomprimir_arbol();

  test_decodificar_archivo();

  return 0;
}
