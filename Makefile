CC = gcc
CFLAGS = -Wall -O4

zprint: zprint.o zrng.o
	$(CC) $(CFLAGS) -o zprint zprint.o zrng.o

zprint.o zrng.o: zrng.h

test: zprint
	./zprint | dieharder -a -g 200

clean:
	-rm -f zprint zprint.o zrng.o
