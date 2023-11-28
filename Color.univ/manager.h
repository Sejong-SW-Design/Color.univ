#pragma once

#ifndef __MANAGER_H__
#define __MANAGER_H_

#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include <Windows.h>
#include <conio.h>
#include "item.h"

using namespace std;

#define LEFT 75 
#define RIGHT 77
#define UP 72   
#define DOWN 80 
#define SPACEBAR 32

int keyControl();

int drawPauseScreen();

void setScore(int stage, double s);
//
//void drawStartScreen();
//

int initGame();

int drawMenu();

void drawPrologue();

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

int getNpcSleeTime(int stage);

void calculateAvgScore();

#endif