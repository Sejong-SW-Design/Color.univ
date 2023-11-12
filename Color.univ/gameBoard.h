#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <queue>
#include "util.h"
#include "item.h"

#define GBOARD_ORIGIN_X 6
#define GBOARD_ORIGIN_Y 4

#define GBOARD_WIDTH 36
#define GBOARD_HEIGHT 21


/*
검정 0 어두운 파랑 1 어두운 초록 2 어두운 하늘 3
어두운 빨강 4 어두운 보라 5 어두운 노랑 6
회색 7 어두운 회색 8 파랑 9 초록 10
하늘 11 빨강 12 보라 13 노랑 14 흰색 15
*/

enum GAME_BOARD
{
    BLANK, //0
    NORMAL_WALL,//1 

    BLUE_WALL,//2
    RED_WALL,//3
    YELLOW_WALL,//4

    PURPLE_WALL,//5
    GREEN_WALL,//6
    ORANGE_WALL,//7
    //2차 혼합 (노+파=초, 초+파=청록) -> 보류
    CYAN_WALL,//8	//청록색
    DARKBLUE_WALL,//9

    //item
    EMERGENCY_EXIT,//10
    PRIME,//11
    ERASER,//12

    //btn
    BLUE_BTN,//13
    RED_BTN,//14
    YELLOW_BTN,//15
    PURPLE_BTN,//16
    GREEN_BTN,//17
    ORANGE_BTN,//18
    CYAN_BTN,//19
    DARKBLUE_BTN,//20

};

using namespace std;

void drawGameBoard(int gameMap[22][37]);

void updateGameBoard(int gameMap[22][37]);

bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37]);

void drawStore();

void updateStore(int color1,int color2); // 새로 생성

void drawInfo(double score[], int grade); // score[0]은 평균

void drawBossLife();

void drawAttackdot(int dotNum);

void removeAttackDot();

void removeAttackTouchedWall();

void removeBossLife();

int* randomEmergencyExit(int posX, int posY, int gameMap[22][37]); // -> 반환값 배열로 바꿈, ppt 수정해야함

void drawGameResult();

void removeGameResult();


#endif

