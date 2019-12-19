CC=g++
FLAGS=-Wall --pedantic -std=c++11
OBJ=$(CC) $(FLAGS) -c
EXE=$(CC) $(FLAGS) -lncurses -o

all: main

force: clean reset main

main: main.o mainMenu.o common.o options.o
	$(EXE) minesweeper main.o mainMenu.o common.o options.o

main.o: main.cpp main.h mainMenu.h common.h options.h
	$(OBJ) main.cpp

mainMenu.o: mainMenu.cpp menu.h common.h
	$(OBJ) mainMenu.cpp

options.o: options.cpp main.h menu.h
	$(OBJ) options.cpp

common.o: common.cpp
	$(OBJ) common.cpp

clean:
	rm -f *.o a.out minesweeper

reset:
	touch *
