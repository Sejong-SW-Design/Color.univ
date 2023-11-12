#include"Move.h"
#include"item.h"
#include "gameBoard.h"
#include "manager.h"

extern double score[5];

bool Move::shiftCharacter(int direction, int gameMap[22][37])
{
    deleteCharacter(gameMap);

    Pos next = position;
    
    switch (direction)
    {
    case LEFT:
        next.x = next.x - 1 >= 0 ? next.x - 1 : next.x; break;
    case RIGHT:
        next.x = next.x + 1 <= GBOARD_WIDTH ? next.x + 1 : next.x; break;
    case UP:
        next.y = next.y - 1 >= 0 ? next.y - 1 : next.y; break;
    case DOWN:
        next.y = next.y + 1 <= GBOARD_HEIGHT ? next.y + 1 : next.y; break;
    }

    int nextSort = detectCollision(gameMap, next);
  
    bool shifted = false;

    if (!isWall(nextSort))
    {
        position = next;
        shifted = true;
    }
    showCharacter();

    return true;
}

void Move::deleteCharacter(int gameMap[22][37])
{
    Pos cursorPosition = getCursorPos(position);
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);

    switch (gameMap[position.y][position.x])
    {
    case BLANK:
        printf("  "); break;
    case BLUE_BTN:
        setBackgroundColor(0, 9); printf("¢Á"); break;
    case RED_BTN:
        setBackgroundColor(0, 12); printf("¢Á"); break;
    case YELLOW_BTN:
        setBackgroundColor(0, 14); printf("¢Á"); break;
    case CYAN_BTN:
        setBackgroundColor(0, 3); printf("¢Á"); break;
    case DARKBLUE_BTN:
        setBackgroundColor(0, 1); printf("¢Á"); break;
    case EMERGENCY_EXIT:
        setBackgroundColor(0, 2); printf("¢È"); break;
    case PRIME:
        setBackgroundColor(0, 6); printf("¡Ú"); break;
    case ERASER:
        setBackgroundColor(0, 15); printf("¨Ñ"); break;
    }
}

void Move::showCharacter()
{
    Pos cursorPosition = getCursorPos(position);
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
    setBackgroundColor(0, color);
    printf("%s", shape.c_str());
}

Pos Move::getPosition()
{
    return position;
}

Player::Player(Pos initPosition)
    :Move(initPosition, 15, "¢Â")
{
    showCharacter();
}

void Player::moveingProcess(int gameMap[22][37])
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
        getItem(gameMap);
    }
}


void Player::getItem(int gameMap[22][37])
{
    int itemSort = gameMap[position.y][position.x];

    if (itemSort >= BLUE_BTN && itemSort <= DARKBLUE_BTN)
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
        setBackgroundColor(0, 2); printf("¢È");
        showCharacter();
    }
    if (itemSort == PRIME)      // Á·º¸
    {
        primeItemCollision(position.x, position.y, gameMap);
    }
    if (itemSort == ERASER)
    {
        eraseColor(position.x, position.y, gameMap);
    }
}

Enemy::Enemy(Pos initPosition, int sleepTime)
    :Move(initPosition, 12, "¡ã")
{
    this->sleepTime = sleepTime;
    showCharacter();
}

int Enemy::getSleepTime()
{
    return sleepTime;
}

void Enemy::moveingProcess(Pos playerPos, int gameMap[22][37])
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