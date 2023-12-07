#pragma once

#ifndef __MANAGER_H__
#define __MANAGER_H_

#include <iostream>
#include "util.h"
#include "gameBoard.h"
#include <Windows.h>
#include <conio.h>
#include "item.h"
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

#define LEFT 75 
#define RIGHT 77
#define UP 72   
#define DOWN 80 
#define SPACEBAR 32

enum BGM
{
	INTRO_BGM, PLAY_BGM, GAME_OVER, GAME_CLEAR, RESULT_BGM
};

void BGMplayer(int sort, bool turn_on);

int keyControl();

int drawPauseScreen();

void setScore(int stage, double s);

int initGame();

int drawMenu();

void drawPrologue();

void drawDevInfo();

void drawHowToPlay();

void drawResultScreen(int gameResult[22][37], int check);

void getStage(int gameMap[22][37], int stage);

int getNpcSleepTime(int stage);

void calculateAvgScore();

void drawReport();

void drawTitle();

#endif