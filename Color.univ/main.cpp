
#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map1.h"

int main() {
	setConsoleSize();
	removeCursor();

	// drawDevInfo();
	drawGameBoard(gameMap1);


	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}