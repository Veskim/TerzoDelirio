EXENAME=unittests
CFLAGS=-Wall -I ../../inc -I ../
LDFLAGS=-l stdc++
CSRCS=../../src/fsm-with-array.c \
      ../../src/hal-linux.c \
      unittests.c

all:
	gcc ${CSRCS} ${CFLAGS} -o ${EXENAME} ${LDFLAGS}

clean:
	rm -rf ${EXENAME} *.o

run:
	./${EXENAME}