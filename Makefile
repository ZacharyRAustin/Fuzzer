CC = gcc
FLAGS = -Wall
DEPS = definitions.h FileManager.h fuzzer.h buffer.h options.h
OBJ = main.o FileManager.o fuzzer.o buffer.o options.o
TARGET = main.o FileManager.o fuzzer.o buffer.o options.o fuzzer *.xml output.txt output2.txt look.txt

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(FLAGS)

fuzzer: $(OBJ) 
	$(CC) -o $@ $^ $(FLAGS)

clean: 
	$(RM) $(TARGET)

test: clean fuzzer
	./testsuite.pl

add: test clean
	make clean
	git add .
	git status