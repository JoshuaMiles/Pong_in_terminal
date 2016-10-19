CC = gcc
INCLUDE = -I ./library
LIBS = -L ./library
FLAGS = -lzdk -lncurses -lm
OBJ = main.o

run: new
	./main

new: clean cab202

all: cab202 

cab202: $(OBJ)
	$(CC) $(INCLUDE) $(LIBS) $(FLAGS) $(OBJ) -o main  

main.o: main.c
	$(CC) -c main.c

clean:
	rm -rf *.o
	rm -rf main 
