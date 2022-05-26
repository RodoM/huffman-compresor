FLAGS = -Wall -Wextra -Werror -std=c99

programa: huffC.o funciones.o btree.o
	$(CC) -o $@ $^ $(FLAGS)

huffC.o: huffC.c funciones.h btree.h
	$(CC) -c $< $(FLAGS)

funciones.o: funciones.c funciones.h btree.h
	$(CC) -c $< $(FLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm programa

.PHONY = clean
