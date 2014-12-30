CC = gcc
FLAGS = -Wall
DEPS = definitions.h FileManager.h
OBJ = main.o FileManager.o
TARGET = main.o FileManager.o fuzzer *.xml output.txt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

fuzzer: $(OBJ) 
	$(CC) -o $@ $^ $(FLAGS)

clean: 
	$(RM) $(TARGET)

test: clean fuzzer
	./testsuite.pl