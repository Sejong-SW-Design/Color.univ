#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"

Player* player;
Enemy* enemy;
extern Store myStore;

int main() {
	setConsoleSize();
	removeCursor();

	// drawDevInfo();
	drawGameBoard(gameMap1);

    //초기위치 정해주세요! (게임보드 기준! 곱하기 2 이딴거 안해도됨)
    Pos playerInitPos = { 1,10 };
    Pos enemyInitPos = { 26, 5 }; 
    player = new Player(playerInitPos);
    enemy = new Enemy(enemyInitPos, 300);

    //게임 메인 루프 (이지호가 만듦)
    while (true)
    {
        for (int i = 0; i < 50; i++)
        {
            player->moveingProcess(gameMap1);
            Sleep(enemy->getSleepTime() / 50);
        }

        //적 돌아당기게 하고싶으면 이거 주석 풀면됨
        enemy->moveingProcess(player->getPosition(), gameMap1);
    }

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}