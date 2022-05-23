#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>

typedef struct {
  unsigned char caracter;
  int frecuencia;
} Tupla;

static inline void quit(const char *s)
{
	perror(s);
	exit(1);
}

char * readfile(const char *path, int *len)
{
	int sz = 1024;
	char *buf = malloc(sz);
	FILE *f = fopen(path, "rb");
	int c, i = 0;

	if (f == NULL)
		quit("readfile.fopen");

	while ((c = getc(f)) != EOF) {
		if (i == sz) {
			sz = sz * 2;
			buf = realloc(buf, sz);
		}
		buf[i++] = c;
	}

	fclose(f);

	*len = i;
	return buf;
}

Tupla * merge(Tupla *a1, int l1, Tupla *a2, int l2) {
	Tupla *r = malloc((l1+l2) * sizeof r[0]);
	int i, j, k;
	i = 0;
	j = 0;
	k = 0;

	while (i < l1 && j < l2) {
		if (a1[i].frecuencia < a2[j].frecuencia) {
			r[k] = a1[i];
			i++;
			k++;
			/* o mejor: r[k++] = a1[i++] */
		} else {
			r[k] = a2[j];
			j++;
			k++;
		}
	}

	while (i < l1) {
		r[k] = a1[i];
		i++;
		k++;
	}
	while (j < l2) {
		r[k] = a2[j];
		j++;
		k++;
	}

	return r;
}

/* Devuelve una copia de [a] */
Tupla * mergesort(Tupla *a, int n) {
	assert (n > 0);
	if (n < 2) {
		Tupla *r = malloc(n * sizeof r[0]);
		r[0] = a[0];
		return r;
	}

	int m = n/2;
	Tupla *ll = mergesort(a, m);
	Tupla *rr = mergesort(a+m, n-m);

	Tupla *mm = merge(ll, m, rr, n-m);

	free(ll);
	free(rr);

	return mm;
}

int main() {
  
  //Funcion que nos crea la array de tuplas con los 256 caracteres de ASCII.
  Tupla ascii_chars[256];
  for (int i = 0; i < 256; i++) {
    Tupla* nuevaTupla = malloc(sizeof(Tupla));
    nuevaTupla->caracter = (unsigned char) i;
    nuevaTupla->frecuencia = 0;
    ascii_chars[i] = *nuevaTupla;
  }

  // for (int i = 0; i < 256; i++) {
  //   printf("ASCII: %d (%c, %d)\n", i, ascii_chars[i].caracter, ascii_chars[i].frecuencia);
  // }

  int len = 0;
  char* res = readfile("/home/rodom/Escritorio/TP_EDyA_2022/asd", &len);
  printf("%s, %d\n", res, len);

  //Obtener la frecuencia de cada caracter en el archivo y actualizar el array.
  for (int i = 0; i < len; i++) {
    ascii_chars[(int) res[i]].frecuencia += 1;
  }

  //ordenar el array por frecuencia.
  Tupla* ascii_chars_ordenado = mergesort(ascii_chars, 256);
  for (int i = 0; i < 256; i++) {
    printf("ASCII: %d (%c, %d)\n", i, ascii_chars_ordenado[i].caracter, ascii_chars_ordenado[i].frecuencia);
  }

  return 0;
}