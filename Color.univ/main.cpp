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
    Pos playerInitPos = setPcInitPos(1); //stage
    Player* player = new Player(playerInitPos);

    //npc sleep time �������ּ���!
    int npcSleepTime = 150; //npc 100 sleep -> pc 20ȸ �̵� // npc 400 sleep -> pc 80ȸ �̵�

    //npc ��ġ �������ּ���!
    vector<PatternNpc*>patternEnemies;
    patternEnemies.push_back(new PatternNpc({ 6,18 }, { 4,18 }, { 7,18 }, NORMAL_NPC));
    patternEnemies.push_back(new PatternNpc({ 12,17 }, { 12,15 }, { 12,17 }, ALCOHOL_NPC));
    patternEnemies.push_back(new PatternNpc({ 19, 5 }, { 19, 4 }, { 19, 6 }, ALCOHOL_NPC));

    vector<ChasingNpc*> chasingEnemies;
    chasingEnemies.push_back(new ChasingNpc({ 26, 5 }));

    while (true)
    {
        int pcMoveCnt = npcSleepTime / 5;
        for (int i = 0; i < pcMoveCnt; i++)
        {
            player->movingProcess(gameMapHere); //gameMap1
            if (player->checkGoalIn(gameMapHere))
            {
                drawResultScreen(gameClear, 1);
                return 0;
            }

            Sleep(5);
        }

        //�� ���ƴ��� �ϰ������ �̰� �ּ� Ǯ���
        EnemiesManager::enemyMoveProcess(patternEnemies, gameMapHere, *player);
        EnemiesManager::enemyMoveProcess(chasingEnemies, gameMapHere, *player);
    }
       
    /*drawResultScreen(gameOver, 0);
    drawResultScreen(gameClear, 1);*/

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}