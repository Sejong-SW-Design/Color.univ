#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"
#include "manager.h"

extern Store myStore;

int main() {
	setConsoleSize();
	removeCursor();

    int gameMapHere[22][37];
    getStage(gameMapHere, 1);

	drawGameBoard(gameMapHere); //gameMap1

    //�ʱ���ġ �����ּ���! (���Ӻ��� ����! ���ϱ� 2 �̵��� ���ص���)
    Pos playerInitPos = { 1,10 }; //1,10 - 1  // 16,1 - 2 // 1,10 - 3
    Player* player = new Player(playerInitPos);

    //npc sleep time �������ּ���!
    int npcSleepTime = 50;

    //npc ��ġ �������ּ���!
    //Pos enemyInitPos = { 26, 5 }; //26,5 - 1  // 30,5 - 2 // 30, 5 - 3
    PatternNpc* enemy1 = new PatternNpc({ 6,18 }, { 4,18 }, { 7,18 }, npcSleepTime, NORMAL_NPC);
    PatternNpc* enemy2 = new PatternNpc({ 12,17 }, { 12,15 }, { 12,17 }, npcSleepTime, ALCOHOL_NPC);
    PatternNpc* enemy3 = new PatternNpc({ 19, 5 }, { 19, 4 }, { 19, 6 }, npcSleepTime, ALCOHOL_NPC);

    //���� ���� �������ּ���!


    while (true)
    {
        for (int i = 0; i < 20; i++)
        {
            player->movingProcess(gameMapHere); //gameMap1
            if (player->checkGoalIn())
            {
                drawResultScreen(gameClear, 1);
                return 0;
            }

            Sleep(npcSleepTime / 20);
        }

        //�� ���ƴ��� �ϰ������ �̰� �ּ� Ǯ���
        enemy1->movingProcess(gameMapHere, *player);
        enemy2->movingProcess(gameMapHere, *player);
        enemy3->movingProcess(gameMapHere, *player);
    }
       
    /*drawResultScreen(gameOver, 0);
    drawResultScreen(gameClear, 1);*/

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}