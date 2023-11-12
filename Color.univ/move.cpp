#include"Move.h"
#include"item.h"
#include "gameBoard.h"
#include "manager.h"

extern double score[5];
int isExit = 0; // 전 단계에서 비상구로 이동했는지 확인하는 변수
int* exitSort; // 비상구 랜덤으로 생성된 좌표

// isExit랑 exitSort 전역으로 해놨는데 좀 그러면 바꿔주세용!!

void Move::shiftCharacter(int direction, int gameMap[22][37])
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

    int nextSort = detectCollision(gameMap, next);
  
    if (!isWall(nextSort))
        position = next;

    showCharacter();

    if (nextSort >= BLUE_BTN && nextSort <= DARKBLUE_BTN)
    {
        getColor(nextSort, next.x, next.y, gameMap); 
    }
    if (nextSort == EMERGENCY_EXIT)
    {
        isExit = 1; // 비상구로 이동 -> PC, NPC 둘다 해당 : 비상구가 화면에서 지워지면 안됨!

        //PC일때만
        //
        deleteCharacter(gameMap);
        exitSort = randomEmergencyExit(next.x, next.y, gameMap);
        position.x = exitSort[1];
        position.y = exitSort[0];
        
        Pos curPos = getCursorPos(next);
        setCurrentCursorPos(curPos.x, curPos.y); // 여기도 이상한 듯,, 좌표를 어디다가 해야되는겨
        setBackgroundColor(0, 2); printf("▥");     
        showCharacter();
    }
    if (nextSort == PRIME)      // 족보
    {
        primeItemCollision(next.x, next.y, gameMap);
    }
    if (nextSort == ERASER)
    {
        eraseColor(next.x, next.y, gameMap);
    }
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
        setBackgroundColor(0, 9); printf("⊙"); break;
    case RED_BTN:
        setBackgroundColor(0, 12); printf("⊙"); break;
    case YELLOW_BTN:
        setBackgroundColor(0, 14); printf("⊙"); break;
    case CYAN_BTN:
        setBackgroundColor(0, 3); printf("⊙"); break;
    case DARKBLUE_BTN:
        setBackgroundColor(0, 1); printf("⊙"); break;
    case EMERGENCY_EXIT:
        setBackgroundColor(0, 2); printf("▥"); break;
    case PRIME:
        setBackgroundColor(0, 6); printf("★"); break;
    case ERASER:
        setBackgroundColor(0, 15); printf("ⓔ"); break;
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
    :Move(initPosition, 15, "◈")
{
    showCharacter();
}

void Player::moveingProcess(int gameMap[22][37])
{
    if (_kbhit() != 0)
    {    
        int key = _getch();
        switch (key)
        {
        case LEFT:
            shiftCharacter(LEFT, gameMap);
            break;
        case RIGHT:
            shiftCharacter(RIGHT, gameMap);
            break;
        case UP:
            shiftCharacter(UP, gameMap);
            break;
        case DOWN:
            shiftCharacter(DOWN, gameMap);
            break;
        case SPACEBAR:
            collaborateColor(position.x, position.y, gameMap); 
            break;
        }
        /*
        if (isExit == 1) // 비상구가 화면에서 사라지면 안됨! -지원
        {
            // 여기가 이상해.. 왜 알맞은 비상구 위치로 안 나올까
            
            setCurrentCursorPos(exitSort[1] + GBOARD_ORIGIN_X, exitSort[0] + GBOARD_ORIGIN_Y); // 위치가 왜!!!!
            setBackgroundColor(0, 2); printf("▥");

            isExit = 0;
            
        }
        */
    }
    
}

Enemy::Enemy(Pos initPosition, int sleepTime)
    :Move(initPosition, 12, "▲")
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