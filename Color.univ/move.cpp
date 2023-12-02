#include"Move.h"
#include"item.h"
#include "gameBoard.h"
#include "manager.h"

extern double score[5];
extern int stage;
extern int IsAlcoholTime; //뤂
extern double keyInterval;

Move::Move(Position initPos, int color, std::string shape)
{
	position = initPos;
	this->color = color;
	this->shape = shape;
	showCharacter();
}

bool Move::shiftCharacter(int direction, int gameMap[22][37])
{
	return shiftCharacter(direction, gameMap, -1);
}

bool Move::shiftCharacter(int direction, int gameMap[22][37], int alcoholNum)
{
	deleteCharacter(gameMap);

	Pos next = position;
	
	if (alcoholNum != -1)
	{
		
		//next = getDrinkNextPos(direction, position, alcoholNum);
		next = updateAlcoholEffect(direction, position, alcoholNum);
	}
	else
	{
		switch (direction)
		{
		case LEFT:
			next.x -= 1; break;
		case RIGHT:
			next.x += 1; break;
		case UP:
			next.y -= 1; break;
		case DOWN:
			next.y += 1; break;
		}
	}

	//게임보드 밖을 벗어나지 않도록
	if (next.x < 0 || next.x >= GBOARD_WIDTH || next.y < 0 || next.y >= GBOARD_HEIGHT)
	{
		next = position;
		return false;
	}

	bool shifted = false;

	//벽이 아니면 움직일 수 있다
	if (!isWall(detectCollision(gameMap, next)))
	{
		position = next;
		shifted = true;
	}
	showCharacter();

	return shifted;
}

void Move::deleteCharacter(int gameMap[22][37])
{
	drawOnePoint(gameMap, position.y, position.x);
}

void Move::showCharacter()
{
	Pos cursorPosition = getCursorPos(position);
	setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
	setBackgroundColor(0, color);
	printf("%s", shape.c_str());
}

void Move::showBlinkCharacter(int backgroundColor)
{
	Pos cursorPosition = getCursorPos(position);
	setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
	setBackgroundColor(backgroundColor, color);
	printf("%s", shape.c_str());
}

int Move::detectCollision(int gameMap[22][37], Pos nextPosition)
{
	return gameMap[nextPosition.y][nextPosition.x];
}

Pos Move::getPosition()
{
	return position;
}

Player::Player(Pos initPosition, int stage)
	:Move(initPosition, 15, "◈")
{
	if (stage == 4)
		visibleDist = 3;
}

void Player::setNoAlcohol()
{
	alcoholNumber = -1;
}

void Player::movingProcess(int gameMap[22][37])
{
	int key = keyControl();
	Pos prev = position;

	bool shifted = false;
	switch (key)
	{
	case LEFT:
		shifted = shiftCharacter(LEFT, gameMap, alcoholNumber);
		break;
	case RIGHT:
		shifted = shiftCharacter(RIGHT, gameMap, alcoholNumber);
		break;
	case UP:
		shifted = shiftCharacter(UP, gameMap, alcoholNumber);
		break;
	case DOWN:
		shifted = shiftCharacter(DOWN, gameMap, alcoholNumber);
		break;
	case SPACEBAR:
		collaborateColor(position.x, position.y, gameMap, visibleDist != -1);
		break;
	}

	if (!shifted)
		return;


	//아이템 확인
	getItem(gameMap);

	//npc와 충돌 확인
	if (gameMap[position.y][position.x] == NORMAL_NPC)
	{
		setScore(stage, -1.5);
		drawInfoMinus(score, stage); 
	}
	if (gameMap[position.y][position.x] == ALCOHOL_NPC)
	{
		//changeD++;
		IsAlcoholTime = 10;
		setAlcoholNumber();
		drawAlcoholTime(IsAlcoholTime);
	}
	/*
	// 여기 고침
	if (IsAlcoholTime != -1) // item에서 IsAlcoholTime 줄어든다.
	{
		updateAlcoholTime(IsAlcoholTime);
	}
	*/

	//visible 위치 조정
	if (visibleDist != -1)
	{
		set<pair<int, int>>darkPos;
		for (int i = getMax(0, prev.y - visibleDist); i <= getMin(21, prev.y + visibleDist); i++)
			for (int j = getMax(0, prev.x - visibleDist); j <= getMin(36, prev.x + visibleDist); j++)
				darkPos.insert({ i, j });

		for (int i = getMax(0, position.y - visibleDist); i <= getMin(21, position.y + visibleDist); i++)
			for (int j = getMax(0, position.x - visibleDist); j <= getMin(36, position.x + visibleDist); j++)
			{
				drawOnePoint(gameMap, i, j, 0, getColor(gameMap[i][j]));
				darkPos.erase({ i, j });
			}

		for (pair<int, int>pos : darkPos)
			drawOnePoint(gameMap, pos.first, pos.second, 0, 0);

		this->showCharacter();
	}
}

void Player::getItem(int gameMap[22][37])
{
	int itemSort = gameMap[position.y][position.x];

	if (itemSort >= BLUE_BTN && itemSort <= SKYBLUE_BTN)
	{
		getColor(itemSort, position.x, position.y, gameMap, visibleDist != -1);
	}
	if (itemSort == EMERGENCY_EXIT)
	{
		deleteCharacter(gameMap);
		pair<int, int> exitSort = randomEmergencyExit(position.x, position.y, gameMap);
		Pos prevPos = position;
		position.x = exitSort.second;
		position.y = exitSort.first;

		Pos curPos = getCursorPos(prevPos);
		setCurrentCursorPos(curPos.x, curPos.y);
		setBackgroundColor(0, 2); printf("▥");
		showBlinkCharacter(14); Sleep(50);
		showCharacter();
	}
	if (itemSort == PRIME)      // 족보
	{
		primeItemCollision(position.x, position.y, gameMap);
		drawInfoPlus(score, stage);
	}
	if (itemSort == ERASER)
	{
		eraseColor(position.x, position.y, gameMap);
	}
	
	if (itemSort == SPEED)
	{
		gameMap[position.y][position.x] = 0;
		keyInterval = updateSpeedEffect();
		
	}
	if (itemSort == LIFE)
	{
		gameMap[position.y][position.x] = 0;
		plusLife();
	}
}

bool Player::checkGoalIn(int gameMap[22][37])
{
	int sort = gameMap[position.y][position.x];

	if (sort == GOAL) return true;
	return false;
}

void Player::setAlcoholNumber()
{
	srand((unsigned int)time(NULL));
	int prev = alcoholNumber;
	while (prev == alcoholNumber)
	{
		alcoholNumber = rand() % 3;
	}
	time(&alcoholStartTime);
}

PatternNpc::PatternNpc(Pos initPosition, Pos startPoint, Pos endPoint, int npcSort)
	:Move(initPosition, 12, getNpcShape(npcSort))
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

void PatternNpc::movingProcess(int gameMap[22][37], Player* player)
{
	//1. set direction
	setNextDirection();

	//2. shift character 
	gameMap[position.y][position.x] = BLANK;
	shiftCharacter(this->direction, gameMap);
	gameMap[position.y][position.x] = npcSort;

	//3. check collision
	if (position == player->getPosition())
	{
		if (npcSort == ALCOHOL_NPC)
		{
			IsAlcoholTime = 10;
			player->setAlcoholNumber();
			drawAlcoholTime(IsAlcoholTime); 
		}
		if (npcSort == NORMAL_NPC)
		{
			setScore(stage, -1.5);
			drawInfoMinus(score, stage);
		}
	}

	player->showCharacter(); //플레이어를 지워버리지 않도록
}

void PatternNpc::setNextDirection()
{
	if (position == startPoint || position == endPoint)
		direction = getOppositeDirection(direction);
}

int PatternNpc::getOppositeDirection(int direction) {
	switch (direction)
	{
	case RIGHT: return LEFT;
	case LEFT: return RIGHT;
	case UP: return DOWN;
	case DOWN: return UP;
	}
	return 0;
}

ChasingNpc::ChasingNpc(Pos initPosition)
	: Move(initPosition, 12, getNpcShape(CHASING_NPC)) 
{
	;
}

void ChasingNpc::movingProcess(int gameMap[22][37], Player player)
{
	//1. set direction
	int result = getNextDirection(player.getPosition(), gameMap);
	if (result == -1)
		return;

	//2. shift character
	gameMap[position.y][position.x] = BLANK;
	shiftCharacter(result, gameMap);
	gameMap[position.y][position.x] = CHASING_NPC;
	player.showCharacter();

	//3. check collision
	if (position == player.getPosition())
	{
		setScore(stage, -1.5);
		drawInfoMinus(score, stage);
	}

	player.showCharacter(); //플레이어를 지워버리지 않도록
}

int ChasingNpc::getNextDirection(Pos playerPos, int gameMap[22][37])
{
	int filter[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
	int ret[4] = { DOWN, RIGHT, UP, LEFT };
	int minDist = -1; int direction = -1;

	for (int i = 0; i < 4; i++)
	{
		int x = this->position.x + filter[i][0];
		int y = this->position.y + filter[i][1];

		if (detectCollision(gameMap, { x,y }) != BLANK)
			continue;

		int dist = (x - playerPos.x) * (x - playerPos.x)
			+ (y - playerPos.y) * (y - playerPos.y);
		if (minDist == -1 || minDist > dist)
		{
			minDist = dist;
			direction = i;
		}
	}

	if (direction == -1)
		return -1;
	return ret[direction];
}

ShootNpc::ShootNpc(Pos initPosition, int npcSort)
	:Move(initPosition, 12, getNpcShape(npcSort))
{
	this->isDead = false;
	this->isFired = false; //임시
	this->npcSort = npcSort;

	int ret[4] = { LEFT, RIGHT, UP, DOWN };
	this->npcDirection = ret[npcSort - SHOOT_NPC_LEFT];
}

void ShootNpc::movingProcess(int gameMap[22][37], Player player)
{
	if (isDead)
		return;

	if (!isFired)
		showCharacter();

	if (isFired)
	{
		//shift character
		gameMap[position.y][position.x] = BLANK;
		bool moved = shiftCharacter(npcDirection, gameMap);

		//check collision
		if (position == player.getPosition()) //플레이어랑 부딪친 경우
		{
			setScore(stage, -1.5);
			drawInfoMinus(score, stage);
			isDead = true; deleteCharacter(gameMap);
		}
		else if (!moved || gameMap[position.y][position.x] != BLANK)  //벽이나 blank가 아닌 것에 부딪친 경우
		{
			isDead = true; deleteCharacter(gameMap);
		}
		else
		{
			gameMap[position.y][position.x] = npcSort;
		}
		player.showCharacter(); //플레이어를 지워버리지 않도록
	}
}

void ShootNpc::updateFireFlag(int gameMap[22][37], Player player)
{
	if (isDead || isFired)
		return;
	//해당 방향에 플레이어가 있는지 확인한다.
	int dx[4] = { -1,1,0,0 };
	int dy[4] = { 0,0, -1,1 };
	int idx = npcSort - SHOOT_NPC_LEFT;
	Pos radar = { position.x + dx[idx], position.y + dy[idx] };
	while (gameMap[radar.y][radar.x] == BLANK)
	{
		if (radar == player.getPosition())
		{
			isFired = true; break;
		}
		radar.x += dx[idx];
		radar.y += dy[idx];
	}
}