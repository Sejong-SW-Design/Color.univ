#ifndef __MOVE_H__
#define __MOVE_H__

#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<string>
#include<set>
#include"util.h"
#include"gameBoard.h"

class Move
{
protected:
	Pos position; //맵 위치라고 생각
	int color;
	std::string shape;
public:
	Move(Position initPos, int color, std::string shape);
	bool shiftCharacter(int direction, int gameMap[22][37]);
	bool shiftCharacter(int direction, int gameMap[22][37], int alcoholNum, int speeFlag);
	void deleteCharacter(int gameMap[22][37]);
	void showCharacter();	
	void showBlinkCharacter(int backgroundColor);
	int detectCollision(int gameMap[22][37], Pos nextPosition);
	Pos getPosition();
	Pos getDrinkNextPos(int direction, Pos now, int alcoholNum);
	Pos updateAlcoholEffect(int direction, Pos position, int alcoholNum);
	void setDarkColor();
	void setOriginColor();

	static Pos getGBoardPos(Pos cursorPos);
	static Pos getCursorPos(Pos gameboardPos);
	static bool isWall(int sort);
	static string getNpcShape(int npcSort);
};

class Player : public Move
{
private:
	int alcoholNumber = -1; // -1이 정상
	int speedFlag = 0; //0이 정상
	int visibleDist = -1;
	int getMax(int a, int b);
	int getMin(int a, int b);
public:
	time_t alcoholStartTime = 0;
	time_t drawStartTime = 0; // 움직 O 버전
	time_t speedStartTime = 0;
	Player(Pos initPosition, int stage);
	void movingProcess(int gameMap[22][37]);
	void getItem(int gameMap[22][37]);
	bool checkGoalIn(int gameMap[22][37]);
	void setAlcoholNumber();
	void setNoAlcohol();
	void setSpeedFlag();
	void setNoSpeed();
	bool isVisiblePos(Pos pos);
	friend void blinkGameBoard(int gameMap[22][37], Player player, EnemiesManager enemies); // 뤂
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
	void movingProcess(int gameMap[22][37], Player* player);
	int getNpcSort();
};

class ChasingNpc : public Move
{
private:
	int getNextDirection(Pos playerPos, int gameMap[22][37]);
public:
	ChasingNpc(Pos initPosition);
	void movingProcess(int gameMap[22][37], Player player);
};

class ShootNpc : public Move
{
private:
	bool isDead;
	bool isFired;
	int npcSort;
	int npcDirection;
public:
	ShootNpc(Pos initPosition, int npcSort);
	void movingProcess(int gameMap[22][37], Player player);
	void updateFireFlag(int gameMap[22][37], Player player);
	int getNpcSort();
};

class EnemiesManager
{
private:
	vector<PatternNpc*>patternEnemies;
	vector<ChasingNpc*>chasingEnemies;
	vector<ShootNpc*>shootEnemies;
public:
	EnemiesManager(vector<PatternNpc*>p, vector<ChasingNpc*>c, vector<ShootNpc*>s, int gameMap[22][37]);
	void EnemyMoveProcess(int gameMap[22][37], Player* player);
	void updateShootNpcFlags(int gameMap[22][37], Player player);
	void updateVisible(int gameMap[22][37], Player player);
	void updateColor(int gameMap[22][37], Player player);
};


#endif