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

    //초기위치 정해주세요! (게임보드 기준! 곱하기 2 이딴거 안해도됨)
    Pos playerInitPos = setPcInitPos(1); //stage
    Player* player = new Player(playerInitPos);

    //npc sleep time 설정해주세요!
    int npcSleepTime = 150; //pc는 5ms당 한번 입력 : npc 100 sleep -> pc 20회 이동 // npc 400 sleep -> pc 80회 이동

    //npc 위치 설정해주세요!
    vector<PatternNpc*> patternEnemies = setPatternNpcInitPos(1, patternEnemies);
    vector<ChasingNpc*> chasingEnemies = setChasingNpcInitPos(1, chasingEnemies);

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

	//after game over
	setCurrentCursorPos(100, 100);
	return 0;
}