EXENAME=unittest
CFLAGS=-Wall -I inc
LDFLAGS=-l stdc++
CSRCS=src/fsm-with-array.c \
      src/hal-linux.c \
      src/main.c

all:
	gcc ${CSRCS} ${CFLAGS} -o ${EXENAME} ${LDFLAGS}

clean:
	rm -rf ${EXENAME} *.o

run:
	./${EXENAME}