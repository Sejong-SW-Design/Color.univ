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

int main() {
	setConsoleSize();
	removeCursor();

	drawGameBoard(gameMap2); //gameMap1

    //�ʱ���ġ �����ּ���! (���Ӻ��� ����! ���ϱ� 2 �̵��� ���ص���)
    Pos playerInitPos = { 16,1 };
    Pos enemyInitPos = { 30, 5 }; 
    player = new Player(playerInitPos);
    enemy = new Enemy(enemyInitPos, 300);

    while (true)
    {
        for (int i = 0; i < 50; i++)
        {
            player->moveingProcess(gameMap1);
            if (player->checkGoalIn())
            {
                drawResultScreen(gameOver, 0);
                setCurrentCursorPos(100, 100);
                return 0;
            }

            Sleep(enemy->getSleepTime() / 50);
        }

        //�� ���ƴ��� �ϰ������ �̰� �ּ� Ǯ���
        //enemy->moveingProcess(player->getPosition(), gameMap1);
    }

    // drawResultScreen(gameOver, 0);
    // drawResultScreen(gameClear, 1);

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}