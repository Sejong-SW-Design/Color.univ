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
    int stage = 3; // stage �ڸ� ���ϴ� ���� �Ű��ּ��� - ������
    getStage(gameMapHere, stage);

	drawGameBoard(gameMapHere); 

    //�ʱ���ġ
    Pos playerInitPos = setPcInitPos(stage); 
    Player* player = new Player(playerInitPos);

    //npc sleep time
    int npcSleepTime = 150; //pc�� 5ms�� �ѹ� �Է� : npc 100 sleep -> pc 20ȸ �̵� // npc 400 sleep -> pc 80ȸ �̵�

    //npc ��ġ
    vector<PatternNpc*> patternEnemies = setPatternNpcInitPos(stage, patternEnemies);
    vector<ChasingNpc*> chasingEnemies = setChasingNpcInitPos(stage, chasingEnemies);

    EnemiesManager* enemies = new EnemiesManager(patternEnemies, chasingEnemies);

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
        enemies->EnemyMoveProcess(gameMapHere, *player);
    }
       
    /*drawResultScreen(gameOver, 0);
    drawResultScreen(gameClear, 1);*/

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}