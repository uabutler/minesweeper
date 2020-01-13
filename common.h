#ifndef COMMON_H
#define COMMON_H

// Makes a bell sound in the terminal to indicate and invalid input
void bell();

// True is the character corresponds to an up movement.
// Up arrow, 'k', and 'w'
bool isUp(int input);
// Down arrow, 'j', and 's'
bool isDown(int input);
// Right arrow, 'l', and 'd'
bool isRight(int input);
// Left arrow, 'h', and 'a'
bool isLeft(int input);

#endif // COMMON_H
