#ifndef MAIN_H
#define MAIN_H

#include <curses.h>
#include <iostream>

using namespace std;

enum state {gamemenu, load, options, game, quit};

extern enum state STATE;

typedef struct GAME_OPTIONS
{
  unsigned height;
  unsigned width;
  unsigned bombs;
} OPTIONS;

#endif // MAIN_H
