#ifndef __ITEM_H__
#define __ITEM_H__

#include "gameBoard.h"
#include <Windows.h>

typedef struct store {
	int color1 = 0 , color2 = 0;
	int capacity;		// 저장소 용량
}Store;



void eraseColor(int posX, int posY, int gameMap[22][37]);

void getColor(int colorNum, int posX, int posY, int gameMap[22][37]);

// int checkStore();

void collaborateColor(int posX, int posY, int gameMap[22][37]);

void chageNumBTS(int color1, int color2);

void primeItemCollision(int posX, int posY, int gameMap[22][37]);

#endif __ITEM_H__