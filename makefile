FLAGS = -Wall -Wextra -Werror -std=c99

huffC: huffc.o funciones.o btree.o io.o
	$(CC) -o $@ $^ $(FLAGS)

huffC.o: huffc.c funciones.h btree.h io.h
	$(CC) -c $< $(FLAGS)

funciones.o: funciones.c funciones.h btree.h
	$(CC) -c $< $(FLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(FLAGS)

io.o: io.c io.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm huffC

.PHONY = clean
