FLAGS = -Wall -Wextra -Werror -std=c99

programa: huffC.o io.o funciones.o btree.o
	$(CC) -o $@ $^ $(FLAGS)

huffC.o: huffC.c io.h funciones.h btree.h
	$(CC) -c $< $(FLAGS)

io.o: io.c io.h
	$(CC) -c $< $(FLAGS)

funciones.o: funciones.c funciones.h btree.h
	$(CC) -c $< $(FLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY = clean
