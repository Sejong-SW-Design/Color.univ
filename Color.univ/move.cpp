#include"Move.h"
#include"item.h"
#include "gameBoard.h"
#include "manager.h"

extern double score[5];
extern int stage;
extern int IsAlcoholTime; 
extern int IsSpeedTime;
extern double keyInterval;
extern int checkB; // ��

Move::Move(Position initPos, int color, std::string shape)
{
	position = initPos;
	this->color = color;
	this->shape = shape;
	showCharacter();
}

bool Move::shiftCharacter(int direction, int gameMap[22][37])
{
	return shiftCharacter(direction, gameMap, -1, 0);
}

bool Move::shiftCharacter(int direction, int gameMap[22][37], int alcoholNum, int speedFlag)
{
	deleteCharacter(gameMap);

	Pos next = position;

	if (speedFlag == 0) {
		keyInterval = 0.15;
	}
	else {
		keyInterval = 0.05;
	}

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

	//���Ӻ��� ���� ����� �ʵ���
	if (next.x < 0 || next.x >= GBOARD_WIDTH || next.y < 0 || next.y >= GBOARD_HEIGHT)
	{
		next = position;
		return false;
	}

	bool shifted = false;

	//���� �ƴϸ� ������ �� �ִ�
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
	:Move(initPosition, 15, "��")
{
//	if (stage == 4)
//		visibleDist = 4;
	// ���� ���� ȭ�� ������ �� ��� -1�� �ٲ��� �ؼ�!!
	// �ؿ� �����س��� - ��
}

void Player::setNoAlcohol()
{
	alcoholNumber = -1;
}
void Player::setNoSpeed()
{
	speedFlag = 0;
}

void Player::movingProcess(int gameMap[22][37])
{
	if (checkB % 2 == 1) visibleDist = 4; // Ȧ����
	else if (checkB % 2 == 0) visibleDist = -1; // ¦����

	int key = keyControl();
	Pos prev = position;

	bool shifted = false;
	switch (key)
	{
	case LEFT:
		shifted = shiftCharacter(LEFT, gameMap, alcoholNumber,speedFlag);
		break;
	case RIGHT:
		shifted = shiftCharacter(RIGHT, gameMap, alcoholNumber, speedFlag);
		break;
	case UP:
		shifted = shiftCharacter(UP, gameMap, alcoholNumber, speedFlag);
		break;
	case DOWN:
		shifted = shiftCharacter(DOWN, gameMap, alcoholNumber, speedFlag);
		break;
	case SPACEBAR:
		collaborateColor(position.x, position.y, gameMap, visibleDist != -1);
		break;
	}

	if (!shifted)
		return;


	//������ Ȯ��
	getItem(gameMap);

	//npc�� �浹 Ȯ��
	switch (gameMap[position.y][position.x])
	{
	case NORMAL_NPC:
	case CHASING_NPC:
	case SHOOT_NPC_LEFT:case SHOOT_NPC_RIGHT:case SHOOT_NPC_UP:case SHOOT_NPC_DOWN:
		setScore(stage, -1.5);
		drawInfoMinus(score, stage);
		break;
	case ALCOHOL_NPC:
		IsAlcoholTime = 10;
		setAlcoholNumber();
		drawAlcoholTime(IsAlcoholTime);
		break;
	}

	//visible ��ġ ����
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
		setBackgroundColor(0, 2); printf("��");
		showBlinkCharacter(14); Sleep(50);
		showCharacter();
	}
	if (itemSort == PRIME)      // ����
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
		IsSpeedTime = 5;
		setSpeedFlag();
		//keyInterval = 0.15;
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

void Player::setSpeedFlag()
{
	speedFlag = 1;
	time(&speedStartTime);
}

PatternNpc::PatternNpc(Pos initPosition, Pos startPoint, Pos endPoint, int npcSort)
	:Move(initPosition, 12, getNpcShape(npcSort))
{
	this->startPoint = startPoint;
	this->endPoint = endPoint;
	this->npcSort = npcSort;

	//���� ���� �������� �� �ʱ� ���� ������ �ʿ��ϸ� ���ڷ� ����
	//������ ���� ���� ����
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

	player->showCharacter(); //�÷��̾ ���������� �ʵ���
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

	player.showCharacter(); //�÷��̾ ���������� �ʵ���
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
	this->isFired = false; //�ӽ�
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
		if (position == player.getPosition()) //�÷��̾�� �ε�ģ ���
		{
			setScore(stage, -1.5);
			drawInfoMinus(score, stage);
			isDead = true; deleteCharacter(gameMap);
		}
		else if (!moved || gameMap[position.y][position.x] != BLANK)  //���̳� blank�� �ƴ� �Ϳ� �ε�ģ ���
		{
			isDead = true; deleteCharacter(gameMap);
		}
		else
		{
			gameMap[position.y][position.x] = npcSort;
		}
		player.showCharacter(); //�÷��̾ ���������� �ʵ���
	}
}

void ShootNpc::updateFireFlag(int gameMap[22][37], Player player)
{
	if (isDead || isFired)
		return;
	//�ش� ���⿡ �÷��̾ �ִ��� Ȯ���Ѵ�.
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