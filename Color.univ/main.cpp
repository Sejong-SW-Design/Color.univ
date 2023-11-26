#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include "map.h"
#include"move.h"
#include"item.h"
#include "manager.h"

extern Store myStore;
extern double score[5];
extern int stage; // �߰��ؽ�� - ��
int gameMapHere[22][37];
int IsAlcoholTime = -1;

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

    stage = 3; // stage �ڸ� ���ϴ� ���� �Ű��ּ��� - ��

    //while ��
    getStage(gameMapHere, stage);

	drawGameBoard(gameMapHere,stage); 
    eraseColor(0, 0, gameMapHere); // ���� ������ �� ������� �ʱ�ȭ

    //�ʱ���ġ
    Pos playerInitPos = setPcInitPos(stage); 
    Player* player = new Player(playerInitPos);

    //npc sleep time
    int npcSleepTime = getNpcSleeTime(stage); //pc�� 5ms�� �ѹ� �Է� 

    //npc ��ġ
    vector<PatternNpc*> patternEnemies = setPatternNpcInitPos(stage, patternEnemies);
    vector<ChasingNpc*> chasingEnemies = setChasingNpcInitPos(stage, chasingEnemies);
    vector<ShootNpc*> shootEnemies = setShootNpcInitPos(stage, shootEnemies);

    EnemiesManager* enemies = new EnemiesManager(patternEnemies, chasingEnemies, shootEnemies);

    /* ����
    int alcohol_time = 1000 - npcSleepTime; // while���� ���� ���� ����
    auto lastUpdateTime = chrono::high_resolution_clock::now(); // ������ ������Ʈ �ð��� ��������.
    chrono::milliseconds alcoholUpdateTime(alcohol_time); // ���ڿ� ������Ʈ ������ ms�� ��ȯ

    while (true)
    {
        auto currTime = chrono::high_resolution_clock::now(); // ���� �ð�
        auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currTime - lastUpdateTime); // ���� �ð��� ������ ������Ʈ �ð��� ����

        if (elapsedTime >= alcoholUpdateTime) // �ð� �Ǹ�
        {
            lastUpdateTime = currTime; // ����
            if (IsAlcoholTime != -1) // move���� �� �ε����� IsAlcoholTime ���ϵ��� ������. ���θ� �ٲ��ּ���..����
            {
                updateAlcoholTime(IsAlcoholTime); 
                IsAlcoholTime--; // ����
                if (IsAlcoholTime == 0)
                {
                    player->setNoAlcohol();
                }
            }
        }
*/

    // �ٲ۰�
    while (true)
    {
        if (IsAlcoholTime != -1) // �� ������
        {
            drawCheckTime(); // �̰� �߰���
        }
        int pcMoveCnt = npcSleepTime / 5;

        for (int i = 0; i < pcMoveCnt; i++)
        {
            player->movingProcess(gameMapHere); 

            if (IsAlcoholTime == 0) 
            {
                player->setNoAlcohol(); // �ٽ� ���ƿ���
            }
            
   
            if (i % 5 == 0) //�ʹ� �Ź� �ݺ��ϸ� ��ȿ�����ΰͰ��Ƽ� ����
            {
                enemies->updateShootNpcFlags(gameMapHere, *player);    
            }
            // game over - ��
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

        //�� ���ƴ��� �ϰ������ �̰� �ּ� Ǯ���
        enemies->EnemyMoveProcess(gameMapHere, player);
       
    }
       
    /*drawResultScreen(gameOver, 0);
    drawResultScreen(gameClear, 1);*/

	return 0;
}