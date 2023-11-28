#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"
#include "manager.h"

extern Store myStore;
extern double score[5];
extern int stage; // 추가해써요 - 뤂
int gameMapHere[22][37];
int IsAlcoholTime = -1;
extern int life[3];


int main() {
	setConsoleSize();
	removeCursor();


    while (1) {
        int flag = initGame();
        if (flag == 0) {
            stage = 1;

            //초기위치
            Pos playerInitPos;;
            Player* player = nullptr;

            //npc sleep time
            int npcSleepTime = 0; //pc는 5ms당 한번 입력 

            //npc 위치
            vector<PatternNpc*> patternEnemies;
            vector<ChasingNpc*> chasingEnemies;
            vector<ShootNpc*> shootEnemies;

            EnemiesManager* enemies = nullptr;

            int checkGoal = 1;

            while (true)
            {
                int pcMoveCnt = npcSleepTime / 5;

                if (checkGoal == 1) {
                    playerInitPos = setPcInitPos(stage);
                    player = new Player(playerInitPos);

                    npcSleepTime = getNpcSleeTime(stage);

                    calculateAvgScore();

                    getStage(gameMapHere, stage);
                    drawGameBoard(gameMapHere, stage);
                    eraseColor(0, 0, gameMapHere);

                    patternEnemies = setPatternNpcInitPos(stage, patternEnemies);
                    chasingEnemies = setChasingNpcInitPos(stage, chasingEnemies);
                    shootEnemies = setShootNpcInitPos(stage, shootEnemies);
                    enemies = new EnemiesManager(patternEnemies, chasingEnemies, shootEnemies);


                    checkGoal = 0;
                }

                for (int i = 0; i < pcMoveCnt; i++)
                {
                    player->movingProcess(gameMapHere);
                    drawCheckTime(player);

                    if (IsAlcoholTime == 0)
                    {
                        player->setNoAlcohol(); // 다시 돌아오게
                    }


                    if (i % 5 == 0) //너무 매번 반복하면 비효율적인것같아서 ㅎㅎ
                    {
                        enemies->updateShootNpcFlags(gameMapHere, *player);
                    }

                    if (score[stage] == 0)
                    {
                        if (life[0] == 0) {
                            drawResultScreen(gameOver, 0);
                            drawGameResult(score, stage);
                            return -1;
                        }
                        else {
                            drawResultScreen(stageOver, 0);
                            score[stage] = 4.5;
                            checkGoal = 1;
                            break;
                        }
                    }

                    if (player->checkGoalIn(gameMapHere))
                    {
                        if (stage == 4) {
                            drawResultScreen(gameClear, 0);
                            return -1;
                        }
                        else {
                            drawResultScreen(stageClear, 1);
                            drawGameResult(score, stage);

                            checkGoal = 1;
                            stage++;

                            break;
                        }
                    }

                    Sleep(5);
                }

                //적 돌아당기게 하고싶으면 이거 주석 풀면됨
                enemies->EnemyMoveProcess(gameMapHere, player);

            }
        }
    }

    

	return 0;
}