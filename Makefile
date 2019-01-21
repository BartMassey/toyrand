# Copyright © 2019 Bart Massey
# [This program is licensed under the "MIT License"]
# Please see the file LICENSE in the source
# distribution of this software for license terms.

NPOOL = 16

CC = gcc
CFLAGS = -Wall -O4

OBJS = toyprint.o toyrand.o toybench.o

toyprint: toyprint.o toyrand.o
	$(CC) $(CFLAGS) -o toyprint toyprint.o toyrand.o

toybench: toybench.o toyrand.o
	$(CC) $(CFLAGS) -o toybench toybench.o toyrand.o

$(OBJS): toyrand.h

test: toyprint
	./toyprint | dieharder -a -g 200 -p $(NPOOL) | tee dieharder.log

clean:
	-rm -f toyprint toybench $(OBJS)
