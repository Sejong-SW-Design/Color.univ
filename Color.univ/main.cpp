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

    //�ʱ���ġ �����ּ���! (���Ӻ��� ����! ���ϱ� 2 �̵��� ���ص���)
    Pos playerInitPos = { 1,10 };
    Pos enemyInitPos = { 26, 5 }; 
    player = new Player(playerInitPos);
    enemy = new Enemy(enemyInitPos, 300);

    //���� ���� ���� (����ȣ�� ����)
    while (true)
    {
        for (int i = 0; i < 50; i++)
        {
            player->moveingProcess(gameMap1);
            Sleep(enemy->getSleepTime() / 50);
        }

        //�� ���ƴ��� �ϰ������ �̰� �ּ� Ǯ���
        enemy->moveingProcess(player->getPosition(), gameMap1);
    }

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}