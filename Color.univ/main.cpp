#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"
#include "manager.h"

extern Store myStore;
extern double score[5];
extern int stage;
int gameMapHere[22][37];
int IsAlcoholTime = -1;
int IsSpeedTime = -1;
extern int life[3];
extern int checkKey;
extern int checkB;

int main() {
	setConsoleSize();
	removeCursor();

    drawTitle();
    drawPrologue();

    int gameCheck = 0;      // game over이면 1
    int blink = 0; 

    while (1) {
        int flag = initGame();
        gameCheck = 0;

        if (flag == 0) {
            if (stage == 1) {
                for (int i = 0; i < 3; ++i) life[i] = 1;
                for (int i = 0; i < 5; ++i) score[i] = 4.5;
            }

            // 초기위치
            Pos playerInitPos;
            Player* player = nullptr;

            //npc sleep time
            int npcSleepTime = 0; // pc는 5ms당 한번 입력 

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
                    player = new Player(playerInitPos, stage);

                    npcSleepTime = getNpcSleepTime(stage);

                    //calculateAvgScore();

                    getStage(gameMapHere, stage);

                    drawGameBoard(gameMapHere, stage);
                    if (stage == 4)
                    {
                        blink = 0; checkB = 0; // 깜빡이 초기화
                    }

                    eraseColor(0, 0, gameMapHere);

                    patternEnemies = setPatternNpcInitPos(stage, patternEnemies);
                    chasingEnemies = setChasingNpcInitPos(stage, chasingEnemies);
                    shootEnemies = setShootNpcInitPos(stage, shootEnemies);
                    enemies = new EnemiesManager(patternEnemies, chasingEnemies, shootEnemies, gameMapHere);

                    checkGoal = 0;
                }

                for (int i = 0; i < pcMoveCnt; i++)
                {
                    if (checkKey == 112) {
                        if (drawPauseScreen() == 0) {
                            if (stage == 4) drawDarkGameBoard(gameMapHere, *player); 
                            else drawGameBoard(gameMapHere, stage);                          
                            continue;
                        }
                        else {
                            system("cls");
                            drawResultScreen(gameOver, 0);

                            gameCheck = 1;
                            break;
                        }
                    }

                    player->movingProcess(gameMapHere);
                    drawCheckTime(player);

                    if (IsAlcoholTime == 0)
                    {
                        player->setNoAlcohol();
                    }

                    if (stage == 4)
                    {
                        if (blink == 0)
                        {
                            time(&(player->drawStartTime)); blink = 1;
                        }
                        if (checkB != 3) blinkGameBoard(gameMapHere, *player, *enemies);
                        if (checkB % 2 == 1) enemies->updateVisible(gameMapHere, *player);
                    }

                    if (IsSpeedTime == 0) {
                        player->setNoSpeed();
                    }

                    if (i % 5 == 0)
                    {
                        enemies->updateShootNpcFlags(gameMapHere, *player);
                    }

                    if (score[stage] == 0)
                    {
                        if (life[1] == 0) {
                            gameCheck = 1;
                            drawResultScreen(gameOver, 0);
                            drawGameResult(score, stage);
                            break;
                        }
                        else {
                            drawResultScreen(stageOver, 0);
                            score[stage] = 4.5;
                            drawGameBoard(gameMapHere, stage); 

                            enemies->updateColor(gameMapHere, *player);
                            
                            if (stage == 4)
                            {
                                blink = 0; checkB = 0; // 깜빡이 초기화
                            }
                            break;
                        }
                    }

                    if (player->checkGoalIn(gameMapHere))
                    {
                        if (stage == 4) {
                            drawResultScreen(gameClear, 1);
                            drawGameResult(score, stage); 
                            drawReport();

                            return 0;
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
                enemies->EnemyMoveProcess(gameMapHere, player);

                if (gameCheck == 1) break;
            }
            if (gameCheck == 1) continue;
        } 
        else if (flag == 1) {
            drawHowToPlay();
        }
        else if (flag == 2) {
            drawDevInfo();
        }
        else if (flag == 3) {
            system("cls");
            return 0;
        }
    }

    

	return 0;
}