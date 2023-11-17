#pragma once

#ifndef __MANAGER_H__
#define __MANAGER_H_

#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include <Windows.h>
#include <conio.h>

using namespace std;

#define LEFT 75 
#define RIGHT 77
#define UP 72   
#define DOWN 80 
#define SPACEBAR 32

int keyControl();

void drawPauseScreen();

void setScore(int gradeidx, double s);
//
//void drawStartScreen();
//
//void drawMenu();
//
void drawDevInfo();
//
//void drawStageIntroInfo();
//
//void drawStageEnding();
//
void drawResultScreen(int gameResult[22][37], int check);
//
//void drawGameInstruction();
//
//void drawIntro();
//
//void drawReturnToMain();

void getStage(int gameMap[22][37], int stage);


#endif