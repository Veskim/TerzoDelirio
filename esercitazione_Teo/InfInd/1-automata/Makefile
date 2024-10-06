#variabili dichiarate
EXENAME = 01-automata.o
CSRCS = automata-1-solution.cpp 
CFLAGS = -Wall
LDFLAGS = -l stdc++

#di solito viene già utilizzato
CC = gcc

#only mandatory target, called "all"
# importante: ricordarsi di usare i tab e non gli spazi dopo ogni target
all:
	${CC} ${CSRCS} ${CFLAGS} -o ${EXENAME} ${LDFLAGS}

#pulisco da file ed .exe
clean:
	rm -f *.o ${EXENAME} 

run: 
	./${EXENAME} 