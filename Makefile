# Copyright © 2019 Bart Massey
# [This program is licensed under the "MIT License"]
# Please see the file LICENSE in the source
# distribution of this software for license terms.

PREFIX = /usr/local
INCLUDE_DIR = $(PREFIX)/include
LIB_DIR = $(PREFIX)/lib

CC = gcc
CDEBUG = -O4
# At least one of these must be currently defined to
# use toyrand_make_pool(), so that it has a source
# of random bits.
DEFINES = -DRDRAND -DURANDOM
CFLAGS = -Wall $(CDEBUG) $(DEFINES)

OBJS = toyprint.o toyrand.o toybench.o

toyprint: toyprint.o toyrand.o
	$(CC) $(CFLAGS) -o toyprint toyprint.o toyrand.o

toybench: toybench.o toyrand.o
	$(CC) $(CFLAGS) -o toybench toybench.o toyrand.o

$(OBJS): toyrand.h

toyrand.o: rdrand.h

testrdrand: testrdrand.c rdrand.h
	$(CC) $(CFLAGS) -o testrdrand testrdrand.c

NPOOL = 0

test: toyprint
	./toyprint | dieharder -a -g 200 -p $(NPOOL) | tee dieharder.log

clean:
	-rm -f toyprint toybench testrdrand $(OBJS) libtoyrand.a

libtoyrand.a: toyrand.o
	ar cr libtoyrand.a toyrand.o

install: libtoyrand.a toyrand.h
	cp toyrand.h $(INCLUDE_DIR)
	cp libtoyrand.a $(LIB_DIR)
