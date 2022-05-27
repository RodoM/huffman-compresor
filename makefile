FLAGS = -Wall -Wextra -Werror -std=c99

huffC: huffc.o fcomprimir.o btree.o io.o
	$(CC) -o $@ $^ $(FLAGS)

huffC.o: huffc.c fcomprimir.h btree.h io.h
	$(CC) -c $< $(FLAGS)

fcomprimir.o: fcomprimir.c fcomprimir.h btree.h
	$(CC) -c $< $(FLAGS)

btree.o: btree.c btree.h
	$(CC) -c $< $(FLAGS)

io.o: io.c io.h
	$(CC) -c $< $(FLAGS)

clean:
	rm *.o
	rm huffC

.PHONY = clean


# huffD: huffd.o fdescomprimir.o io.o	
# 	$(CC) -o $@ $^ $(FLAGS)

# huffD.o: huffd.c fdescomprimir.h io.huffC
# 	$(CC) -c $< $(FLAGS)

# fdescomprimir.o: fdescomprimir.c fdescomprimir.h
# 	$(CC) -c $< $(FLAGS)	

# rm huffD