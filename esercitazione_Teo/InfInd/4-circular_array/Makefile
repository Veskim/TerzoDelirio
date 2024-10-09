# Compilatori
CC = gcc        # Compilatore per C
CXX = g++       # Compilatore per C++

# Flags di compilazione
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g

# Target
C_TARGET = c_array.o       # Eseguibile per il programma C
CPP_TARGET = cpp_array.o   # Eseguibile per il programma C++

# File sorgenti
C_SOURCES = src/circular_array.c test/main.c
CPP_SOURCES = src/circular_array.cpp test/main.cpp

# Regole per creare entrambi i programmi
all: $(C_TARGET) $(CPP_TARGET)

# rule for C
$(C_TARGET): $(C_SOURCES)
	$(CC) $(CFLAGS) -o $(C_TARGET) $(C_SOURCES)

# rule for C++
$(CPP_TARGET): $(CPP_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(CPP_TARGET) $(CPP_SOURCES)

# clean
clean:
	rm -f $(C_TARGET) $(CPP_TARGET)
