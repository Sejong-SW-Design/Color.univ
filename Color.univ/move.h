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
	bool operator== (const Position other) {
		return this->x == other.x && this->y == other.y;
	}
}Pos;

class Move
{
protected:
	Pos position; //맵 위치라고 생각
	int color = 15;
	std::string shape;
public:
	Move(Position initPos, int color, std::string shape);
	bool shiftCharacter(int direction, int gameMap[22][37]);
	void deleteCharacter(int gameMap[22][37]);
	void showCharacter();
	int detectCollision(int gameMap[22][37], Pos nextPosition);
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
	void movingProcess(int gameMap[22][37]);
	void getItem(int gameMap[22][37]);
	bool checkGoalIn();
};

class PatternNpc : public Move
{
private:
	Pos startPoint;
	Pos endPoint;
	int direction;
	int npcSort;
public:
	PatternNpc(Pos initPosition, Pos startPoint, Pos endPoint,
		int sleepTime, int npcSort)
		:Move(initPosition, 12, NORMAL_NPC ? "▲" : "§")
	{
		this->startPoint = startPoint;
		this->endPoint = endPoint;
		this->npcSort = npcSort;
		
		//게임 레벨 디자인할 때 초기 방향 설정이 필요하면 인자로 받자
		//지금은 임의 설정 상태
		if (startPoint.x != endPoint.x)
			direction = RIGHT;
		else
			direction = DOWN;
	}
	void movingProcess(int gameMap[22][37], Player player)
	{
		Pos prev = position;

		setNextDirection();
		
		//shiftCharacter
		// 1 deleteCharacter
		Pos cursor = getCursorPos(position);
		setCurrentCursorPos(cursor.x, cursor.y);
		printf("  ");
		gameMap[position.y][position.x] = BLANK;

		// 2 direction
		switch (direction)
		{
		case LEFT:
			position.x -= 1; break;
		case RIGHT:
			position.x += 1; break;
		case UP:
			position.y -= 1; break;
		case DOWN:
			position.y += 1; break;
		}

		// 3 showCharacter
		cursor = getCursorPos(position);
		setCurrentCursorPos(cursor.x, cursor.y);
		switch (npcSort)
		{
		case NORMAL_NPC:
			setBackgroundColor(0, 12); printf("▲"); break;
		case ALCOHOL_NPC:
			setBackgroundColor(0, 12); printf("§"); break;
		}
		gameMap[position.y][position.x] = npcSort;
		

		//여기서 pc와 충돌 확인 해줘야함!
		if (position == player.getPosition())
		{
			setScore(1, -1.5); 
		}

		player.showCharacter();
	}
	void setNextDirection()
	{
		if (position == startPoint || position == endPoint)
			direction = getOppositeDirection(direction);
	}
	int getOppositeDirection(int direction) {
		switch(direction)
		{
		case RIGHT: return LEFT;
		case LEFT: return RIGHT;
		case UP: return DOWN;
		case DOWN: return UP;
		}
	}
};


//추적으로 수정할것임!!
class Enemy : public Move //chasing
{
private:
	int sleepTime;
public:
	Enemy(Pos initPosition, int sleepTime, string shape);
	void movingProcess(int gameMap[22][37], Pos playerPos);
	int getSleepTime();
	int getNextDirection(Pos playerPos, int gameMap[22][37]);
};

#endif