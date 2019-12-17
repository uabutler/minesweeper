CC=g++
FLAGS=-Wall --pedantic -std=c++11
OBJ=$(CC) $(FLAGS) -c
EXE=$(CC) $(FLAGS) -lncurses -o

all: main

force: clean reset main

main: main.o menu.o common.o
	$(EXE) minesweeper main.o menu.o common.o

main.o: main.cpp main.h menu.h common.h
	$(OBJ) main.cpp

menu.o: menu.cpp menu.h common.h
	$(OBJ) menu.cpp

common.o: common.cpp
	$(OBJ) common.cpp

clean:
	rm -f *.o a.out minesweeper

reset:
	touch *
