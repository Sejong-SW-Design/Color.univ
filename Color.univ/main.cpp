#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"
#include "manager.h"

extern Store myStore;

//������������ �ӵ� ������ �ʿ��� �� ���Ƽ� ���� �Լ�(����ȣ)
//�Ŵ������� �������ּ���!
int getNpcSleeTime(int stage)
{
    //�� �ʺ��� �ӵ� ���� �ʿ��ϸ� �� ���ּ���!
    switch (stage)
    {
    case 1: return 150;
    case 2: return 150;
    case 3: return 300;
    case 4: return 150;
    }
    return 150;
}

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
    int npcSleepTime = getNpcSleeTime(stage); //pc�� 5ms�� �ѹ� �Է� 

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

	return 0;
}