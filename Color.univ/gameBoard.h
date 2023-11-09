#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#define GBOARD_ORIGIN_X 6
#define GBOARD_ORIGIN_Y 4

#define GBOARD_WIDTH 36
#define GBOARD_HEIGHT 21

using namespace std;

void drawGameBoard(int arr[][37]);

void updateGameBoard(int colorSort);

void removeWall();

void removeItem();

void drawStore();

void drawInfo(double score[], int grade); // score[0]Àº Æò±Õ

void drawBossLife();

void drawAttackdot(int dotNum);

void removeAttackDot();

void removeAttackTouchedWall();

void removeBossLife();

int randomEmergencyExit();

void drawGameResult();

void removeGameResult();

#endif

