#variabili dichiarate
EXENAME = 03-grammatica.o
EXENAME2 = 03-2-grammatica.o
EXENAME3 = 03-3-grammatica.o
CSRCS = grammatica-3.cpp 
CSRCS2 = grammatica-32.cpp 
CSRCS3 = grammatica-33.cpp 
CFLAGS = -Wall
LDFLAGS = -l stdc++
BASEDIR = /TerzoDelirio

#di solito viene già utilizzato
CC = gcc

#only mandatory target, called "all"
# importante: ricordarsi di usare i tab e non gli spazi dopo ogni target
all:
	${CC} ${CSRCS} ${CFLAGS} -o ${EXENAME} ${LDFLAGS}
	${CC} ${CSRCS2} ${CFLAGS} -o ${EXENAME2} ${LDFLAGS}
	${CC} ${CSRCS3} ${CFLAGS} -o ${EXENAME3} ${LDFLAGS}

#pulisco da file ed .exe
clean:
	rm -f *.o ${EXENAME} 
	rm -f *.o ${EXENAME2}
	rm -f *.o ${EXENAME3}

run: 
	./${EXENAME} 
	./${EXENAME2} 
	./${EXENAME3} 