#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <queue>
#include <vector>
#include "util.h"
#include "manager.h"
#include "item.h"


#define GBOARD_ORIGIN_X 6
#define GBOARD_ORIGIN_Y 4

#define GBOARD_WIDTH 37
#define GBOARD_HEIGHT 22

typedef struct Position
{
    int x, y;
    bool operator== (const Position other) {
        return this->x == other.x && this->y == other.y;
    }
}Pos;

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

    DARKBLUE_WALL,//8
    DARKGREEN_WALL,//9
    DARKSKYBLUE_WALL,//10
    DARKRED_WALL,//11
    PINK_WALL,//12
    DARKYELLOW_WALL,//13
    DARKGRAY_WALL,//14
    SKYBLUE_WALL,//15


    //btn
    BLUE_BTN,//16
    RED_BTN,//17
    YELLOW_BTN,//18
    PURPLE_BTN,//19
    GREEN_BTN,//20
    ORANGE_BTN,//21

    DARKBLUE_BTN,//22
    DARKGREEN_BTN,//23
    DARKSKYBLUE_BTN,//24
    DARKRED_BTN,//25
    PINK_BTN,//26
    DARKYELLOW_BTN,//27
    DARKGRAY_BTN,//28
    SKYBLUE_BTN,//29

    //item
    EMERGENCY_EXIT,//30
    PRIME,//31
    ERASER,//32
    HIDDEN,//33
    STOP,//34


    //PC NPC
    ALCOHOL_NPC,//35
    NORMAL_NPC,//36

    // goal
    GOAL//37
};


using namespace std;

void drawOnePoint(int gameMap[22][37], int i, int j, int backGround);
void drawOnePoint(int gameMap[22][37], int i, int j);

void drawGameBoard(int gameMap[22][37]);

void drawGameEdge();

bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37]);

void drawStore();

void updateStore(int color1,int color2); // 새로 생성

void drawInfo(double score[], int grade); // score[0]은 평균

void drawBossLife();

void drawAttackdot();

void removeAttackDot();

void removeAttackTouedWall();

void removeBossLife();

pair<int, int> randomEmergencyExit(int posX, int posY, int gameMap[22][37]);

void drawGameResult();

void removeGameResult();

Pos setPcInitPos(int stage); // PC 위치 초기화 설정


#endif
