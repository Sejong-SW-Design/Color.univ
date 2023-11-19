#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"
#include "manager.h"

extern Store myStore;

//스테이지별로 속도 조절이 필요할 것 같아서 만든 함수(이지호)
//매니저에서 가져가주세요!
int getNpcSleeTime(int stage)
{
    //각 맵별로 속도 조절 필요하면 더 해주세요!
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
    int stage = 3; // stage 자리 원하는 곳에 옮겨주세요 - 전루피
    getStage(gameMapHere, stage);

	drawGameBoard(gameMapHere); 

    //초기위치
    Pos playerInitPos = setPcInitPos(stage); 
    Player* player = new Player(playerInitPos);

    //npc sleep time
    int npcSleepTime = getNpcSleeTime(stage); //pc는 5ms당 한번 입력 

    //npc 위치
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

        //적 돌아당기게 하고싶으면 이거 주석 풀면됨
        enemies->EnemyMoveProcess(gameMapHere, *player);
    }
       
    /*drawResultScreen(gameOver, 0);
    drawResultScreen(gameClear, 1);*/

	return 0;
}