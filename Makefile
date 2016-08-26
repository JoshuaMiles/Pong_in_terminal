CC = gcc
INCLUDE = -I ~/uni/cab202/pongInClion 
LIBS = -L ~/uni/cab202/pongInClion/library
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
