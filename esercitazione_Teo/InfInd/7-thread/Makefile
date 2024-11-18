EXENAME = thread.o
CFLAGS = -Wall -I inc
LDFLAGS = -l stdc++

CSRCS = main.c

all:
	gcc ${CSRCS} ${CFLAGS} -o ${EXENAME} ${LDFLAGS}

clean:
	rm -rf ${EXENAME} *.o

run:
	./${EXENAME}