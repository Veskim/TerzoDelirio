# Compilatori
CC = gcc        # C
CXX = g++       # C++

# Flags 
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g

# Directory di inclusione degli header
INC_DIR = inc/

# Target
C_EXENAME = c_array.o       # programma C
CPP_EXENAME = cpp_array.o   # programma C++

# sources
C_SOURCES = src/circular_array.c test/main.c
CPP_SOURCES = src/circular_array.cpp test/main.cpp
# PROJECT_SOURCE_DIR = 4-circular_array/

# Make both files
all: $(C_EXENAME) $(CPP_EXENAME)

# rule for C
$(C_EXENAME): $(C_SOURCES)
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(C_EXENAME) $(C_SOURCES)

# rule for C++
$(CPP_EXENAME): $(CPP_SOURCES)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $(CPP_EXENAME) $(CPP_SOURCES)

# clean
clean:
	rm -f $(C_EXENAME) $(CPP_EXENAME)

# Esegui programma C
run_c: $(C_EXENAME)
	./$(C_EXENAME)

# Esegui programma C++
run_cpp: $(CPP_EXENAME)
	./$(CPP_EXENAME)