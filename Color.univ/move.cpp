#include"Move.h"
#include"item.h"
#include "gameBoard.h"
#include "manager.h"

extern double score[5];
extern int stage;
extern int IsAlcoholTime; 
extern int IsSpeedTime;
extern double keyInterval;
extern int checkB; 

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
		next = getDrinkNextPos(direction, position, alcoholNum);
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
	if (!isWall(gameMap[next.y][next.x]))
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

Pos Move::getPosition()
{
	return position;
}

void Move::setDarkColor()
{
	color = 0;
	showCharacter();
}

void Move::setOriginColor()
{
	color = 12;
	showCharacter();
}

Pos Move::getGBoardPos(Pos cursorPos)
{
	Pos gameboardPos = { (cursorPos.x - GBOARD_ORIGIN_X) / 2,
		cursorPos.y - GBOARD_ORIGIN_Y };
	return gameboardPos;
}

Pos Move::getCursorPos(Pos gameboardPos)
{
	Pos cursorPos = { 2 * gameboardPos.x + GBOARD_ORIGIN_X,
		gameboardPos.y + GBOARD_ORIGIN_Y };
	return cursorPos;
}

bool Move::isWall(int sort)
{
	return sort >= NORMAL_WALL && sort <= SKYBLUE_WALL;
}

string Move::getNpcShape(int npcSort)
{
	switch (npcSort)
	{
	case NORMAL_NPC:
		return "▩";
	case ALCOHOL_NPC:
		return "§";
	case CHASING_NPC:
		return "ψ";
	case SHOOT_NPC_LEFT:
		return "◀";
	case SHOOT_NPC_RIGHT:
		return "▶";
	case SHOOT_NPC_UP:
		return "▲";
	case SHOOT_NPC_DOWN:
		return "▼";
	}
	return "";
}

Player::Player(Pos initPosition, int stage)
	:Move(initPosition, 15, "◈")
{}

int Player::getMax(int a, int b) { return a > b ? a : b; }
int Player::getMin(int a, int b) { return a < b ? a : b; }

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
	if (checkB % 2 == 1) visibleDist = 4; // 홀수면
	else if (checkB % 2 == 0) visibleDist = -1; // 짝수면

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
		if (visibleDist != -1) drawDarkGameBoard(gameMap, *this); 
		break;
	}

	if (!shifted)
		return;


	//아이템 확인
	getItem(gameMap);

	//npc와 충돌 확인
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

bool Player::isVisiblePos(Pos pos) {
	int dx = position.x - pos.x;
	int dy = position.y - pos.y;
	dx = dx < 0 ? -dx : dx;
	dy = dy < 0 ? -dy : dy;
	if (dx <= visibleDist && dy <= visibleDist)
		return true;
	return false;
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

		if (gameMap[y][x] != BLANK)
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

int PatternNpc::getNpcSort() { return npcSort; }
int ShootNpc::getNpcSort() { return npcSort; }

EnemiesManager::EnemiesManager(vector<PatternNpc*>p, vector<ChasingNpc*>c, vector<ShootNpc*>s, int gameMap[22][37])
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

void EnemiesManager::EnemyMoveProcess(int gameMap[22][37], Player* player)
{
	for (auto iter = patternEnemies.begin(); iter != patternEnemies.end(); iter++)
		(*iter)->movingProcess(gameMap, player);
	for (auto iter = chasingEnemies.begin(); iter != chasingEnemies.end(); iter++)
		(*iter)->movingProcess(gameMap, *player);
	for (auto iter = shootEnemies.begin(); iter != shootEnemies.end(); iter++)
		(*iter)->movingProcess(gameMap, *player);
}
void EnemiesManager::updateShootNpcFlags(int gameMap[22][37], Player player)
{
	for (auto iter = shootEnemies.begin(); iter != shootEnemies.end(); iter++)
		(*iter)->updateFireFlag(gameMap, player);
}
void EnemiesManager::updateVisible(int gameMap[22][37], Player player)
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

void EnemiesManager::updateColor(int gameMap[22][37], Player player) // 뤂
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