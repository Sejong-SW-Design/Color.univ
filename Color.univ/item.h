#ifndef __ITEM_H__
#define __ITEM_H__

#include "gameBoard.h"
#include <Windows.h>

typedef struct store
{
	int color1 = 0 , color2 = 0;
}Store;



void eraseColor();

void getColor(int colorNum, int posX, int posY, int gameMap[22][37]);

int checkStore();

void collaborateColor(int posX, int posY, int gameMap[22][37]);


#endif __ITEM_H__