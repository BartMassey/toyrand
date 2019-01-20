CC = gcc
CFLAGS = -Wall -O4

OBJS = zprint.o zrng.o zbench.o

zprint: zprint.o zrng.o
	$(CC) $(CFLAGS) -o zprint zprint.o zrng.o

zbench: zbench.o zrng.o
	$(CC) $(CFLAGS) -o zbench zbench.o zrng.o

$(OBJS): zrng.h

test: zprint
	./zprint | dieharder -a -g 200

clean:
	-rm -f zprint zbench $(OBJS)
