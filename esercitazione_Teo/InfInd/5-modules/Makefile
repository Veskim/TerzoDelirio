#variabili dichiarate
EXENAME = sfm.o
CSRCS = automata-1-solution.cpp 
CPPFLAGS = -Wall -g
LDFLAGS = -l stdc++

#di solito viene già utilizzato
CC = g++

# Target
CPP_EXENAME = sfm.o   # programma C++

# sources
CPP_SOURCES = sfm-cout.cpp automata-1-solution.cpp
# PROJECT_SOURCE_DIR = 4-circular_array/

# Make both files
all: $(CPP_EXENAME)

# rule for C++
$(CPP_EXENAME): $(CPP_SOURCES)
	$(CC) $(CFLAGS) -o $(CPP_EXENAME) $(CPP_SOURCES)

# clean
clean:
	rm -f $(CPP_EXENAME)

# Esegui programma C++
run: $(CPP_EXENAME)
	./$(CPP_EXENAME)