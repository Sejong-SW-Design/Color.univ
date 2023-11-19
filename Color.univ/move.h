#ifndef __MOVE_H__
#define __MOVE_H__

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<string>
#include"util.h"
#include"gameBoard.h"
//
//static int changeD = 0;

class Move
{
protected:
	Pos position; //맵 위치라고 생각
	int color;
	std::string shape;
public:
	Move(Position initPos, int color, std::string shape);
	bool shiftCharacter(int direction, int gameMap[22][37]);
	bool shiftCharacter(int direction, int gameMap[22][37], int alcoholNum);
	void deleteCharacter(int gameMap[22][37]);
	void showCharacter();
	int detectCollision(int gameMap[22][37], Pos nextPosition);
	Pos getPosition();
	Pos getDrinkNextPos(int direction, Pos now, int alcoholNum);
	//void movingProcess(int gameMap[22][37], Player player) = 0;

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
	int alcoholNumber = -1; // -1이 정상
public:
	Player(Pos initPosition);
	void movingProcess(int gameMap[22][37]);
	void getItem(int gameMap[22][37]);
	bool checkGoalIn(int gameMap[22][37]);
	void setAlcoholNumber();
};

class PatternNpc : public Move
{
private:
	Pos startPoint;
	Pos endPoint;
	int direction;
	int npcSort;
	void setNextDirection();
	int getOppositeDirection(int direction);
public:
	PatternNpc(Pos initPosition, Pos startPoint, Pos endPoint, int npcSort);
	void movingProcess(int gameMap[22][37], Player player);
};

class ChasingNpc : public Move
{
private:
	int getNextDirection(Pos playerPos, int gameMap[22][37]);
public:
	ChasingNpc(Pos initPosition);
	void movingProcess(int gameMap[22][37], Player player);
};

class EnemiesManager
{
private:
	vector<PatternNpc*>patternEnemies;
	vector<ChasingNpc*> chasingEnemies;
public:
	EnemiesManager(vector<PatternNpc*>p, vector<ChasingNpc*>c)
	{
		patternEnemies = p;
		chasingEnemies = c;
	}
	void EnemyMoveProcess(int gameMap[22][37], Player player)
	{
		for (auto iter = patternEnemies.begin(); iter != patternEnemies.end(); iter++)
			(*iter)->movingProcess(gameMap, player);
		for (auto iter = chasingEnemies.begin(); iter != chasingEnemies.end(); iter++)
			(*iter)->movingProcess(gameMap, player);
	}
};


#endif