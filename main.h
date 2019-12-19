#ifndef MAIN_H
#define MAIN_H

#include <curses.h>
#include <iostream>

using namespace std;

typedef enum state {gamemenu, leaderboard, options, game, quit} state;

extern state STATE;

typedef struct OPTIONS
{
  unsigned height;
  unsigned width;
  unsigned bombs;
} OPTIONS;

#endif // MAIN_H
