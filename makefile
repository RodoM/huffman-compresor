FLAGS = -g -Wall -Wextra -Werror -std=c99

huff: huff.o fcomprimir.o fdescomprimir.o btree.o io.o
	$(CC) -o $@ $^ $(FLAGS)

huff.o: huff.c fcomprimir.h fdescomprimir.h btree.h io.h
	$(CC) -c $< $(FLAGS)

fcomprimir.o: fcomprimir.c fcomprimir.h btree.h
	$(CC) -c $< $(FLAGS)

fdescomprimir.o: fdescomprimir.c fdescomprimir.h btree.h
	$(CC) -c $< $(FLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(FLAGS)

io.o: io.c io.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm huff

.PHONY = clean
