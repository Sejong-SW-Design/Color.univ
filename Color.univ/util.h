#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <Windows.h>


void setConsoleSize();

void removeCursor();

COORD getCurrentCursorPos();

void setCurrentCursorPos(int x, int y);

void setBackgroundColor(int backColor, int textcolor);

// void setBGM(int sort, int playFlag);


#endif
