CC=g++
CFLAGS=-c -Wall -ansi -std=c++11 -Wno-unused-parameter -Wno-unused-function
SOURCES=src/*.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXEC=graphe.exe

all: $(SOURCES) $(EXEC)
	
$(EXEC): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXEC)
