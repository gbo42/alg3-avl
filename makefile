CFLAGS = -Wall 
LDFLAGS =

busca: busca.o avl.o

busca.o: busca.c
avl.o: avl.c avl.h

clean:
	rm -f *.o

purge: clean
	rm -f busca
