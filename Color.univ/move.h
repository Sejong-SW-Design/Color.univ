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
//
//static int changeD = 0;

class Move
{
protected:
	Pos position; //�� ��ġ��� ����
	int color;
	std::string shape;
public:
	Move(Position initPos, int color, std::string shape);
	bool shiftCharacter(int direction, int gameMap[22][37]);
	bool shiftCharacter(int direction, int gameMap[22][37], int alcoholNum);
	void deleteCharacter(int gameMap[22][37]);
	void showCharacter();	
	void showBlinkCharacter(int backgroundColor);
	int detectCollision(int gameMap[22][37], Pos nextPosition);
	Pos getPosition();
	Pos getDrinkNextPos(int direction, Pos now, int alcoholNum);
	Pos updateAlcoholEffect(int direction, Pos position, int alcoholNum);
	//void movingProcess(int gameMap[22][37], Player player) = 0;
	void setDarkColor()
	{
		color = 0;
		showCharacter();
	}
	void setOriginColor()
	{
		color = 12;
		showCharacter();
	}

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
	static string getNpcShape(int npcSort)
	{
		switch (npcSort)
		{
		case NORMAL_NPC:
			return "��";
		case ALCOHOL_NPC:
			return "��";
		case CHASING_NPC:
			return "��";
		case SHOOT_NPC_LEFT:
			return "��";
		case SHOOT_NPC_RIGHT:
			return "��";
		case SHOOT_NPC_UP:
			return "��";
		case SHOOT_NPC_DOWN:
			return "��";
		}
		return "";
	}
};

class Player : public Move
{
private:
	int alcoholNumber = -1; // -1�� ����
	//int speedFlag = 0; //0�� ����
	int visibleDist = -1;
	int getMax(int a, int b) { return a > b ? a : b; }
	int getMin(int a, int b) { return a < b ? a : b; }
public:
	time_t alcoholStartTime = 0;
	time_t drawStartTime = 0; // ���� O ����
	time_t speedStartTime = 0;
	Player(Pos initPosition, int stage);
	void movingProcess(int gameMap[22][37]);
	void getItem(int gameMap[22][37]);
	bool checkGoalIn(int gameMap[22][37]);
	void setAlcoholNumber();
	void setNoAlcohol();
	bool isVisiblePos(Pos pos) {
		//�ϴ� �簢�� �ݰ����� �ص�. ���̾� �ݰ����� �ٲٰ� ������ ���⸸ ����
		int dx = position.x - pos.x;
		int dy = position.y - pos.y;
		dx = dx < 0 ? -dx : dx;
		dy = dy < 0 ? -dy : dy;
		if (dx <= visibleDist && dy <= visibleDist)
			return true;
		return false;
	}
	friend void blinkGameBoard(int gameMap[22][37], Player player, EnemiesManager enemies); // ��
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
	int getNpcSort() { return npcSort; }
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
	int getNpcSort() { return npcSort; }
};

class EnemiesManager
{
private:
	vector<PatternNpc*>patternEnemies;
	vector<ChasingNpc*>chasingEnemies;
	vector<ShootNpc*>shootEnemies;
public:
	EnemiesManager(vector<PatternNpc*>p, vector<ChasingNpc*>c, vector<ShootNpc*>s, int gameMap[22][37])
	{
		patternEnemies = p;
		chasingEnemies = c;
		shootEnemies = s;

		for (auto iter = patternEnemies.begin(); iter != patternEnemies.end(); iter++)
		{
			Pos pos = (*iter)->getPosition();
			gameMap[pos.y][pos.x] = (*iter)->getNpcSort();
		}
		for (auto iter = chasingEnemies.begin(); iter != chasingEnemies.end(); iter++)
		{
			Pos pos = (*iter)->getPosition();
			gameMap[pos.y][pos.x] = CHASING_NPC;
		}
		for (auto iter = shootEnemies.begin(); iter != shootEnemies.end(); iter++)
		{
			Pos pos = (*iter)->getPosition();
			gameMap[pos.y][pos.x] = (*iter)->getNpcSort();
		}
	}
	void EnemyMoveProcess(int gameMap[22][37], Player *player)
	{
		for (auto iter = patternEnemies.begin(); iter != patternEnemies.end(); iter++)
			(*iter)->movingProcess(gameMap, player);
		for (auto iter = chasingEnemies.begin(); iter != chasingEnemies.end(); iter++)
			(*iter)->movingProcess(gameMap, *player);
		for (auto iter = shootEnemies.begin(); iter != shootEnemies.end(); iter++)
			(*iter)->movingProcess(gameMap, *player);
	}
	void updateShootNpcFlags(int gameMap[22][37], Player player)
	{
		for (auto iter = shootEnemies.begin(); iter != shootEnemies.end(); iter++)
			(*iter)->updateFireFlag(gameMap, player);
	}
	void updateVisible(int gameMap[22][37], Player player)
	{
		for (auto iter = patternEnemies.begin(); iter != patternEnemies.end(); iter++)
		{
			if (player.isVisiblePos((*iter)->getPosition()))
				(*iter)->setOriginColor();
			else
				(*iter)->setDarkColor();
		}
		for (auto iter = chasingEnemies.begin(); iter != chasingEnemies.end(); iter++)
		{
			if (player.isVisiblePos((*iter)->getPosition()))
				(*iter)->setOriginColor();
			else
				(*iter)->setDarkColor();
		}
	}

	void updateColor(int gameMap[22][37], Player player) // ��
	{
		for (auto iter = patternEnemies.begin(); iter != patternEnemies.end(); iter++)
		{
			(*iter)->setOriginColor();
		}
		for (auto iter = chasingEnemies.begin(); iter != chasingEnemies.end(); iter++)
		{
			(*iter)->setOriginColor();
		}
	}
};


#endif