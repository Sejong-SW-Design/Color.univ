#ifndef __MOVE_H__
#define __MOVE_H__

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<string>
#include"util.h"
#include"gameBoard.h"

#define LEFT 75 
#define RIGHT 77
#define UP 72   
#define DOWN 80 
#define SPACEBAR 32

typedef struct Position
{
	int x, y;
}Pos;

class Move
{
protected:
	Pos position; //맵 위치라고 생각
	int color = 15;
	std::string shape;
public:
	Move(Position initPos, int color, std::string shape)
	{
		position = initPos;
		this->color = color;
		this->shape = shape;
	}

	bool shiftCharacter(int direction, int gameMap[22][37]);
	void deleteCharacter(int gameMap[22][37]);
	void showCharacter();

	int detectCollision(int gameMap[22][37], Pos nextPosition)
	{
		return gameMap[nextPosition.y][nextPosition.x];
	}

	Pos getPosition();

	static Pos getGBoardPos(Pos cursorPos)
	{
		Pos gameboardPos = { (cursorPos.x - GBOARD_ORIGIN_X) / 2,
			cursorPos.y - GBOARD_ORIGIN_Y };
		return gameboardPos;
	}
	static Pos getCursorPos(Pos gameboardPos)
	{
		Pos cursorPos = { 2 * gameboardPos.x + GBOARD_ORIGIN_X,
			gameboardPos.y + GBOARD_ORIGIN_Y };
		return cursorPos;
	}
	static bool isWall(int sort)
	{
		return sort >= NORMAL_WALL && sort <= SKYBLUE_WALL;
	}
};

class Player : public Move
{
private:
public:
	Player(Pos initPosition);
	void moveingProcess(int gameMap[22][37]);
	void getItem(int gameMap[22][37]);
	bool checkGoalIn();
};

class Enemy : public Move
{
private:
	int sleepTime;
public:
	Enemy(Pos initPosition, int speed);
	void moveingProcess(Pos playerPos, int gameMap[22][37]);
	int getSleepTime();
	int getNextDirection(Pos playerPos, int gameMap[22][37]);
};


#endif