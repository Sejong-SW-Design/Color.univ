#include"Move.h"
#include"item.h"
#include "gameBoard.h"
#include "manager.h"

extern double score[5];

Move::Move(Position initPos, int color, std::string shape)
{
    position = initPos;
    this->color = color;
    this->shape = shape;
    showCharacter();
}

bool Move::shiftCharacter(int direction, int gameMap[22][37])
{
    deleteCharacter(gameMap);

    Pos next = position;
    
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

    //게임보드 밖을 벗어나지 않도록
    if (next.x < 0 || next.x >= GBOARD_WIDTH || next.y < 0 || next.y >= GBOARD_HEIGHT)
        next = position;

    int nextSort = detectCollision(gameMap, next);
  
    bool shifted = false;

    //벽이 아니면 움직일 수 있다
    if (!isWall(nextSort))
    {
        position = next;
        shifted = true;
    }
    showCharacter();

    return shifted;
}

void Move::deleteCharacter(int gameMap[22][37])
{
    Pos cursorPosition = getCursorPos(position);
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);

    switch (gameMap[position.y][position.x])
    {
    case BLANK: 
        printf("  "); break;
    case NORMAL_NPC: 
        setBackgroundColor(0, 12); printf("▲"); break;
    case ALCOHOL_NPC:
        setBackgroundColor(0, 12); printf("§"); break;
    case BLUE_BTN:
        setBackgroundColor(0, 9); printf("⊙"); break;
    case RED_BTN:
        setBackgroundColor(0, 12); printf("⊙"); break;
    case YELLOW_BTN:
        setBackgroundColor(0, 14); printf("⊙"); break;
    case PURPLE_BTN:
        setBackgroundColor(0, 5); printf("⊙");  break;
    case GREEN_BTN:
        setBackgroundColor(0, 10); printf("⊙"); break;
    case ORANGE_BTN:
        setBackgroundColor(0, 6); printf("⊙");  break;
    case DARKBLUE_BTN:
        setBackgroundColor(0, 1); printf("⊙"); break;
    case DARKGREEN_BTN:
        setBackgroundColor(0, 2); printf("⊙");  break;
    case DARKSKYBLUE_BTN:
        setBackgroundColor(0, 3); printf("⊙");  break;
    case DARKRED_BTN:
        setBackgroundColor(0, 4); printf("⊙");  break;
    case PINK_BTN:
        setBackgroundColor(0,13); printf("⊙");  break;
    case DARKYELLOW_BTN:
        setBackgroundColor(0, 6); printf("⊙");  break;
    case DARKGRAY_BTN:
        setBackgroundColor(0, 8); printf("⊙");  break;
    case SKYBLUE_BTN:
        setBackgroundColor(0, 11); printf("⊙");  break;
    case EMERGENCY_EXIT:
        setBackgroundColor(0, 2); printf("▥"); break;
    case PRIME:
        setBackgroundColor(0, 6); printf("★"); break;
    case ERASER:
        setBackgroundColor(0, 15); printf("ⓔ"); break;
    case HIDDEN:
        // 교수님의 사랑
    case STOP:
        setBackgroundColor(0, 7); printf("※"); break;
    }
}

void Move::showCharacter()
{
    Pos cursorPosition = getCursorPos(position);
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
    setBackgroundColor(0, color);
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

Player::Player(Pos initPosition)
    :Move(initPosition, 15, "◈")
{
    ;
}

void Player::movingProcess(int gameMap[22][37])
{
    if (_kbhit() != 0)
    {
        bool shifted = false;
        int key = _getch();
        switch (key)
        {
        case LEFT:
            shifted = shiftCharacter(LEFT, gameMap);
            break;
        case RIGHT:
            shifted = shiftCharacter(RIGHT, gameMap);
            break;
        case UP:
            shifted = shiftCharacter(UP, gameMap);
            break;
        case DOWN:
            shifted = shiftCharacter(DOWN, gameMap);
            break;
        case SPACEBAR:
            collaborateColor(position.x, position.y, gameMap); 
            break;
        }

        if (!shifted)
            return;

        //아이템 확인
        getItem(gameMap);

        //npc와 충돌 확인
        if (gameMap[position.y][position.x] == ALCOHOL_NPC
            || gameMap[position.y][position.x] == NORMAL_NPC)
        {
            setScore(1, -1.5);
        }
    }
}

void Player::getItem(int gameMap[22][37])
{
    int itemSort = gameMap[position.y][position.x];

    if (itemSort >= BLUE_BTN && itemSort <= SKYBLUE_BTN)
    {
        getColor(itemSort, position.x, position.y, gameMap);
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
        showCharacter();
    }
    if (itemSort == PRIME)      // 족보
    {
        primeItemCollision(position.x, position.y, gameMap);
    }
    if (itemSort == ERASER)
    {
        eraseColor(position.x, position.y, gameMap);
    }
}

bool Player::checkGoalIn()
{
    if (GBOARD_WIDTH - position.x <= 1 &&
        (position.y >= 8 && position.y <= 14))
        return true;
    return false;
}

Enemy::Enemy(Pos initPosition, int sleepTime, string shape)
    :Move(initPosition, 12, shape)
{
    this->sleepTime = sleepTime;
    showCharacter();
}

int Enemy::getSleepTime()
{
    return sleepTime;
}

void Enemy::movingProcess(int gameMap[22][37], Pos playerPos)
{
    int result = getNextDirection(playerPos, gameMap);
    if (result == -1)
        return;
    shiftCharacter(result, gameMap);
}

int Enemy::getNextDirection(Pos playerPos, int gameMap[22][37])
{
    int filter[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
    int ret[4] = { DOWN, RIGHT, UP, LEFT };
    int minDist = -1; int direction = -1;

    for (int i = 0; i < 4; i++)
    {
        int x = this->position.x + filter[i][0];
        int y = this->position.y + filter[i][1];

        if (isWall(detectCollision(gameMap, {x,y})))
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