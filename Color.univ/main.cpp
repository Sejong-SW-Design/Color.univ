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

    stage = 3; // stage 자리 원하는 곳에 옮겨주세요 - 뤂

    //while 문
    getStage(gameMapHere, stage);

	drawGameBoard(gameMapHere,stage); 
    eraseColor(0, 0, gameMapHere); // 게임 시작할 때 색저장소 초기화

    //초기위치
    Pos playerInitPos = setPcInitPos(stage); 
    Player* player = new Player(playerInitPos);

    //npc sleep time
    int npcSleepTime = getNpcSleeTime(stage); //pc는 5ms당 한번 입력 

    //npc 위치
    vector<PatternNpc*> patternEnemies = setPatternNpcInitPos(stage, patternEnemies);
    vector<ChasingNpc*> chasingEnemies = setChasingNpcInitPos(stage, chasingEnemies);
    vector<ShootNpc*> shootEnemies = setShootNpcInitPos(stage, shootEnemies);

    EnemiesManager* enemies = new EnemiesManager(patternEnemies, chasingEnemies, shootEnemies);

    /* 원래
    int alcohol_time = 1000 - npcSleepTime; // while문에 들어가기 위해 조정
    auto lastUpdateTime = chrono::high_resolution_clock::now(); // 마지막 업데이트 시간을 지금으로.
    chrono::milliseconds alcoholUpdateTime(alcohol_time); // 알코올 업데이트 간격을 ms로 변환

    while (true)
    {
        auto currTime = chrono::high_resolution_clock::now(); // 현재 시간
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currTime - lastUpdateTime); // 현재 시간과 마지막 업데이트 시간의 차이

        if (elapsedTime >= alcoholUpdateTime) // 시간 되면
        {
            lastUpdateTime = currTime; // 갱신
            if (IsAlcoholTime != -1) // move에서 술 부딪히면 IsAlcoholTime 변하도록 설정함. 별로면 바꿔주세요..ㅎㅎ
            {
                updateAlcoholTime(IsAlcoholTime); 
                IsAlcoholTime--; // 전역
                if (IsAlcoholTime == 0)
                {
                    player->setNoAlcohol();
                }
            }
        }
*/

    // 바꾼거
    while (true)
    {
        if (IsAlcoholTime != -1) // 술 먹으면
        {
            drawCheckTime(); // 이거 추가함
        }
        int pcMoveCnt = npcSleepTime / 5;

        for (int i = 0; i < pcMoveCnt; i++)
        {
            player->movingProcess(gameMapHere); 

            if (IsAlcoholTime == 0) 
            {
                player->setNoAlcohol(); // 다시 돌아오게
            }
            
   
            if (i % 5 == 0) //너무 매번 반복하면 비효율적인것같아서 ㅎㅎ
            {
                enemies->updateShootNpcFlags(gameMapHere, *player);    
            }
            // game over - 뤂
            /*
            if (score[stage] == 0)
            {
                drawResultScreen(gameOver, 0);
                drawGameResult(score, stage);
                
                return 0;
            }
            */
            if (player->checkGoalIn(gameMapHere))
            {
                drawResultScreen(gameClear, 1);
                drawGameResult(score, stage); 
                stage++;
                //
                return 0;
            }

            Sleep(5);
        }

        //적 돌아당기게 하고싶으면 이거 주석 풀면됨
        enemies->EnemyMoveProcess(gameMapHere, player);
       
    }
       
    /*drawResultScreen(gameOver, 0);
    drawResultScreen(gameClear, 1);*/

	return 0;
}