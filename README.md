# TP-EDyA-2022

## Integrantes
- Carruba, Matias
- Meroi, Rodolfo

## Objetivo
La idea del trabajo practico es implementar un compresor de datos utilizando el algoritmo de Huffman. El mismo va a funcionar para cualquier tipo de archivo y es sin perdida, es decir, desde el archivo comprimido podemos reconstruir exactamente el original (a diferencia de la compresion con perdida, por ejemplo el formato JPG para imagenes, que puede perder algunos detalles).

## Compilar y ejecutar el programa
### Compilar los archivos
```
make
```
### Compresion
```
./huff C tuArchivo
```
### Descompresion
```
./huff D tuArchivo.hf
```

## Testing
### Compilar los archivos
```
gcc -o tests tests.c btree.o fcomprimir.o fdescomprimir.o
```
### Ejecutar los tests
```
./tests
```
