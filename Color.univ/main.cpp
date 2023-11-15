#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"
#include "manager.h"

Player* player;
Enemy* enemy;
extern Store myStore;

//게임매니저님 단계별로 맵 호출하는 기능 만들어주세요ㅎㅎㅎ

int main() {
	setConsoleSize();
	removeCursor();

	drawGameBoard(gameMap3); //gameMap1

    //초기위치 정해주세요! (게임보드 기준! 곱하기 2 이딴거 안해도됨)
    Pos playerInitPos = { 1,10 }; //1,10 - 1  // 16,1 - 2 
    Pos enemyInitPos = { 30, 5 }; //26,5 - 1  // 30,5 - 2
    player = new Player(playerInitPos);
    enemy = new Enemy(enemyInitPos, 300);

    while (true)
    {
        for (int i = 0; i < 50; i++)
        {
            player->moveingProcess(gameMap3); //gameMap1
            if (player->checkGoalIn())
            {
                drawResultScreen(gameOver, 0);
                setCurrentCursorPos(100, 100);
                return 0;
            }

            Sleep(enemy->getSleepTime() / 50);
        }

        //적 돌아당기게 하고싶으면 이거 주석 풀면됨
        //enemy->moveingProcess(player->getPosition(), gameMap1);
    }

    // drawResultScreen(gameOver, 0);
    // drawResultScreen(gameClear, 1);

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}