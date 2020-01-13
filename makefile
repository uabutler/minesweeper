CC=g++
FLAGS=-Wall --pedantic -std=c++11
OBJ=$(CC) $(FLAGS) -c
EXE=$(CC) $(FLAGS) -o

# Use the first option for mac, the second for POSIX

#LIB=-lcurses
LIB=-lncurses -lpthread

all: main

force: clean reset main

main: main.o mainMenu.o options.o common.o timer.o board.o boardPrinter.o game.o
	$(EXE) minesweeper main.o mainMenu.o options.o common.o timer.o board.o boardPrinter.o game.o $(LIB)

main.o: main.cpp main.h mainMenu.h common.h options.h game.h
	$(OBJ) main.cpp

mainMenu.o: mainMenu.cpp main.h menu.h common.h
	$(OBJ) mainMenu.cpp

options.o: options.cpp main.h menu.h common.h
	$(OBJ) options.cpp

common.o: common.cpp
	$(OBJ) common.cpp

timer.o: timer.cpp timer.h
	$(OBJ) timer.cpp

board.o: board.cpp board.h
	$(OBJ) board.cpp

boardPrinter.o: boardPrinter.cpp boardPrinter.h board.h
	$(OBJ) boardPrinter.cpp

game.o: game.cpp main.h common.h
	$(OBJ) game.cpp

clean: game.cpp main.h common.h
	rm -f *.o a.out minesweeper

reset:
	touch *
