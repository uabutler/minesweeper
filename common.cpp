#include <iostream>
#include <vector>
#include <algorithm>
#include <ncurses.h>

using namespace std;

void bell()
{
  cout << "\a";
}

bool isUp(int input)
{
  vector<int> valid = {KEY_UP, 'k', 'w'};
  return count(valid.begin(), valid.end(), input);
}

bool isDown(int input)
{
  vector<int> valid = {KEY_DOWN, 'j', 's'};
  return count(valid.begin(), valid.end(), input);
}

bool isRight(int input)
{
  vector<int> valid = {KEY_RIGHT, 'l', 'd'};
  return count(valid.begin(), valid.end(), input);
}

bool isLeft(int input)
{
  vector<int> valid = {KEY_LEFT, 'h', 'a'};
  return count(valid.begin(), valid.end(), input);
}
