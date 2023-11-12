#include"Move.h"
#include"item.h"

void Move::shiftCharacter(int direction, int gameMap[22][37])
{
    deleteCharacter();

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


    //������ ���� �Լ��� ȣ���ϱ�
    //(����ȣ) ��� �������� �ѹ� ������ gameboard���� ������� �ϹǷ� removeItem���ȣ��
    if (nextSort >= BLUE_BTN && nextSort <= DARKBLUE_BTN)
    {
        removeItem(nextSort, next.x, next.y, gameMap);
        getColor(nextSort, next.x, next.y, gameMap); 
    }
    if (nextSort == EMERGENCY_EXIT)
    {
        //randomEmergencyExit(next.x,next.y,gameMap); -> �갡 ��ȯ�ϴ� int �迭 ������ ��ǥ �̵�
    }
    if (nextSort == PRIME)
    {
        //�����Դϴ�.
        removeItem(nextSort,next.x,next.y,gameMap);
    }
    if (nextSort == ERASER)
    {
        removeItem(nextSort, next.x, next.y, gameMap);
        eraseColor();
    }

    showCharacter();
}

void Move::deleteCharacter()
{
    Pos cursorPosition = getCursorPos(position);
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
    printf("  ");
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
    :Move(initPosition, 15, "��")
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
            collaborateColor(position.x,position.y,gameMap); //�̰� �³�..? -����
            // Player ��ġ�� ������ �־�ΰ� �;����
            break;
        }
    }
}

Enemy::Enemy(Pos initPosition, int sleepTime)
    :Move(initPosition, 12, "��")
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