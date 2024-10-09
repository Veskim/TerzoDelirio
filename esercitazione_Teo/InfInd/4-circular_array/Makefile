# Compilatori
CC = gcc        # C
CXX = g++       # C++

# Flags 
CFLAGS = -Wall -g
CXXFLAGS = -Wall -g

# Target
C_EXENAME = c_array.o       # programma C
CPP_EXENAME = cpp_array.o   # programma C++

# sources
C_SOURCES = src/circular_array.c test/main.c
CPP_SOURCES = src/circular_array.cpp test/main.cpp

# Make both files
all: $(C_EXENAME) $(CPP_EXENAME)

# rule for C
$(C_EXENAME): $(C_SOURCES)
	$(CC) $(CFLAGS) -o $(C_EXENAME) $(C_SOURCES)

# rule for C++
$(CPP_EXENAME): $(CPP_SOURCES)
	$(CXX) $(CXXFLAGS) -o $(CPP_EXENAME) $(CPP_SOURCES)

# clean
clean:
	rm -f $(C_EXENAME) $(CPP_EXENAME)

# run C
run c: 
	./${C_EXENAME}

# run Cpp
run cpp: 
	./${CPP_EXENAME}  
