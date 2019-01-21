# Copyright © 2019 Bart Massey
# [This program is licensed under the "MIT License"]
# Please see the file LICENSE in the source
# distribution of this software for license terms.

PREFIX = /usr/local
INCLUDE_DIR = $(PREFIX)/include
LIB_DIR = $(PREFIX)/lib

CC = gcc
CFLAGS = -Wall -O4

OBJS = toyprint.o toyrand.o toybench.o

toyprint: toyprint.o toyrand.o
	$(CC) $(CFLAGS) -o toyprint toyprint.o toyrand.o

toybench: toybench.o toyrand.o
	$(CC) $(CFLAGS) -o toybench toybench.o toyrand.o

$(OBJS): toyrand.h

NPOOL = 0

test: toyprint
	./toyprint | dieharder -a -g 200 -p $(NPOOL) | tee dieharder.log

clean:
	-rm -f toyprint toybench $(OBJS) libtoyrand.a

libtoyrand.a: toyrand.o
	ar cr libtoyrand.a toyrand.o

install: libtoyrand.a toyrand.h
	cp toyrand.h $(INCLUDE_DIR)
	cp libtoyrand.a $(LIB_DIR)
