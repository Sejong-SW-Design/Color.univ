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
    Pos playerInitPos = { 1,10 }; //1,10 - 1  // 16,1 - 2 // 1,10 - 3
    Player* player = new Player(playerInitPos);

    //npc sleep time 설정해주세요!
    int npcSleepTime = 50;

    //npc 위치 설정해주세요!
    //Pos enemyInitPos = { 26, 5 }; //26,5 - 1  // 30,5 - 2 // 30, 5 - 3
    PatternNpc* enemy1 = new PatternNpc({ 6,18 }, { 4,18 }, { 7,18 }, npcSleepTime, NORMAL_NPC);
    PatternNpc* enemy2 = new PatternNpc({ 12,17 }, { 12,15 }, { 12,17 }, npcSleepTime, ALCOHOL_NPC);
    PatternNpc* enemy3 = new PatternNpc({ 19, 5 }, { 19, 4 }, { 19, 6 }, npcSleepTime, ALCOHOL_NPC);

    //골인 지점 설정해주세요!


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

        //적 돌아당기게 하고싶으면 이거 주석 풀면됨
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