#include "gameBoard.h"
#include "move.h"

int Exit[5][2]; // ��� ���� ���� �迭
int Exit_n = 0; // ��� ��

extern double score[5];

void drawGameBoard(int gameMap[22][37])
{
    drawInfo(score, 1);
    drawStore();

    // if(grade==4)
    drawBossLife();

    for (int i = 0; i < 22; i++)
    {
        setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y+i); // ��ġ
        for (int j = 0; j < 37; j++)
        {
            switch (gameMap[i][j])
            {
            case NORMAL_WALL:
                setBackgroundColor(0, 7); printf("��"); break;
            case BLANK:
                printf("  "); break;
            case BLUE_WALL:
                setBackgroundColor(0, 9); printf("��"); break;
            case RED_WALL:
                setBackgroundColor(0, 12); printf("��");  break;
            case YELLOW_WALL:
                setBackgroundColor(0, 14); printf("��");  break;
            case PURPLE_WALL:
                setBackgroundColor(0, 13); printf("��");  break;
            case GREEN_WALL:
                setBackgroundColor(0, 10); printf("��"); break;
            case ORANGE_WALL:
                setBackgroundColor(0, 6); printf("��");  break;
            case CYAN_WALL:
                setBackgroundColor(0, 3); printf("��");  break;
            case DARKBLUE_WALL:
                setBackgroundColor(0, 1); printf("��");  break;
            case BLUE_BTN:
                setBackgroundColor(0, 9); printf("��"); break;
            case RED_BTN:
                setBackgroundColor(0, 12); printf("��"); break;
            case YELLOW_BTN:
                setBackgroundColor(0, 14); printf("��"); break;
            case CYAN_BTN:
                setBackgroundColor(0, 3); printf("��"); break;
            case DARKBLUE_BTN:
                setBackgroundColor(0, 1); printf("��"); break;
            case EMERGENCY_EXIT:
                setBackgroundColor(0, 2); printf("��"); 
                Exit[Exit_n][0] = i; Exit[Exit_n][1] = j;
                Exit_n++;
                break;
            case PRIME:
                setBackgroundColor(0, 6); printf("��"); break;
            case ERASER:
                setBackgroundColor(0, 15); printf("��"); break;
            }
        }
        
        printf("\n");
        
    }
}

void updateGameBoard(int gameMap[22][37]) // ���Ӻ���, ���� ���� ������Ʈ  -> �̿�
{
    drawInfo(score, 1);

    for (int i = 0; i < 22; i++)
    {
        setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + i); // ��ġ
        for (int j = 0; j < 37; j++)
        {
            switch (gameMap[i][j])
            {
            case NORMAL_WALL:
                setBackgroundColor(0, 7); printf("��"); break;
            case BLANK:
                printf("  "); break;
            case BLUE_WALL:
                setBackgroundColor(0, 9); printf("��"); break;
            case RED_WALL:
                setBackgroundColor(0, 12); printf("��");  break;
            case YELLOW_WALL:
                setBackgroundColor(0, 14); printf("��");  break;
            case PURPLE_WALL:
                setBackgroundColor(0, 13); printf("��");  break;
            case GREEN_WALL:
                setBackgroundColor(0, 10); printf("��"); break;
            case ORANGE_WALL:
                setBackgroundColor(0, 6); printf("��");  break;
            case CYAN_WALL:
                setBackgroundColor(0, 3); printf("��");  break;
            case DARKBLUE_WALL:
                setBackgroundColor(0, 1); printf("��");  break;
            case BLUE_BTN:
                setBackgroundColor(0, 9); printf("��"); break;
            case RED_BTN:
                setBackgroundColor(0, 12); printf("��"); break;
            case YELLOW_BTN:
                setBackgroundColor(0, 14); printf("��"); break;
            case CYAN_BTN:
                setBackgroundColor(0, 3); printf("��"); break;
            case DARKBLUE_BTN:
                setBackgroundColor(0, 1); printf("��"); break;
            case EMERGENCY_EXIT:
                setBackgroundColor(0, 2); printf("��"); break;
            case PRIME:
                setBackgroundColor(0, 6); printf("��"); break;
            case ERASER:
                setBackgroundColor(0, 15); printf("��"); break;
            }
        }

        printf("\n");

    }
}

//������ �� ���� ���θ� ��ȯ -> ������ �ϳ��� �� �ߴٸ� ���� ����, ������ �� ������ �����
bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37]) //���� �� ������ ���ְ�, �ƴϸ� return -> �̿�!!
{
    bool didRemove = false;
    gameMap[posY][posX] = 0; // �� ��ư ���� -> �̰� �÷��̾ ���� �����ߴ����� (��)

    /////
    int start = gameMap[posY][posX];

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    //bfs
    std::queue<std::pair<int, int>> q;
    bool visited[22][37] = { 0 };
    q.push(make_pair(posY, posX));
    visited[posY][posX] = true;
    while (!q.empty())
    {
        std::pair<int, int>now = q.front();
        q.pop();
        for (int k = 0; k < 4; k++)
        {
            int nextY = now.first + dy[k];
            int nextX = now.second + dx[k];
            if (nextY < 0 || nextX < 0 || nextY >= 22 || nextX >= 37)
                continue;
            if (visited[nextY][nextX])
                continue;
            if (gameMap[nextY][nextX] == colorSort)
            {
                didRemove = true;
                int cursorPosX = 2 * nextX + GBOARD_ORIGIN_X;
                int cursorPosY = nextY + GBOARD_ORIGIN_Y;
                setCurrentCursorPos(cursorPosX, cursorPosY);
                printf("  ");
                gameMap[nextY][nextX] = 0;
                continue;
            }
            if (gameMap[nextY][nextX] != BLANK)
                continue;
            q.push(make_pair(nextY, nextX));
            visited[nextY][nextX] = true;
            setCurrentCursorPos(2 * nextX + GBOARD_ORIGIN_X, nextY + GBOARD_ORIGIN_Y);
        }
    }
    return didRemove;
}



void removeItem(int num, int posX, int posY, int gameMap[22][37]) // �̿ϼ�
{
    gameMap[posY][posX] = 0;

    if (num == 11)//������ ���
    {
        //util ���� ���
    }
    else if (num == 12)//���찳�� ���
    {
        //(������) eraseColor�̰� �ּ�ó���� ������ 
        // move���� eraseColor�� �� ȣ���ϴ����? �׷����ϴܿ��� �ּ�ó����. 
        // Ȥ�ö� �����ʿ��ϸ� �ߺ� �� �ǰ� �� �Ű��ּ���
       // eraseColor();
        // �̻��ѵ� ��� ���ľ��ұ�... 
        // ���� 1. �Ǳ�� ��. �ٵ� player�� ���� ������ٰ� �����̸� �ٽ� ��Ÿ��.
        //  -> (����ȣ) �Ʒ� ������Ʈ ���Ӻ��� ������ �׷� �� �Լ� �ּ�ó��
        // ���� 2. 2���� ���� ����ҿ� �־��ٰ� erase�ϸ� ��������
        // �������� �Ծ��� ����ư �ٽ� ������... -> ���� ��Ʈ�� ����
    }

    //updateGameBoard(gameMap);
}



void updateStore(int color1, int color2) // ���� ���� -> ppt�� �߰��ؾ���
{
    //btn enum���� �� ���� �ܼ� ������ �ٲ۴�!!
    //���� collaborate �Լ������� �̰� �����ؾ���.
    switch (color1)
    {
    case BLUE_BTN:
        color1 = 9; break;
    case RED_BTN:
        color1 = 12; break;
    case YELLOW_BTN:
        color1 = 14; break;
    case PURPLE_BTN:
        color1 = 13; break;
    case GREEN_BTN:
        color1 = 10; break;
    case ORANGE_BTN:
        color1 = 6; break;
    case CYAN_BTN:
        color1 = 3; break;
    case DARKBLUE_BTN:
        color1 = 1; break;
    }

    switch (color2)
    {
    case BLUE_BTN:
        color2 = 9; break;
    case RED_BTN:
        color2 = 12; break;
    case YELLOW_BTN:
        color2 = 14; break;
    case PURPLE_BTN:
        color2 = 13; break;
    case GREEN_BTN:
        color2 = 10; break;
    case ORANGE_BTN:
        color2 = 6; break;
    case CYAN_BTN:
        color2 = 3; break;
    case DARKBLUE_BTN:
        color2 = 1; break;
    }


    int x, y;
    int origin_x1 = 20, origin_y1 = 27, h = 2, w = 2;

    for (y = 1; y < h; y++)
    {
        for (x = 2; x <= w * 2; x++)
        {
            setCurrentCursorPos(origin_x1 + x, origin_y1 + y);
            if (color1 == 0) printf("  ");
            else 
            {
                setBackgroundColor(0, color1);
                printf("��");
            }
        }
    }

    int origin_x2 = 28, origin_y2 = 27;

    for (y = 1; y < h; y++)
    {
        for (x = 2; x <= w * 2; x++)
        {
            setCurrentCursorPos(origin_x2 + x, origin_y2 + y);
            if (color2 == 0) printf("  ");
            else
            {
                setBackgroundColor(0, color2);
                printf("��");
            }
        }
    }

}

void drawStore() 
{
    int x, y;

    // ù��° �����
    int origin_x1 = 20, origin_y1 = 27, h = 2, w = 2;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x1, origin_y1 + y);
        if (y == h)
            printf("��");
        else if (y == 0)
            printf("��");
        else
            printf("��");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x1 + (w + 1) * 2, origin_y1 + y);
        if (y == h)
            printf("��");
        else if (y == 0)
            printf("��");
        else
            printf("��");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1);
        printf("��");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1 + h);
        printf("��");
    }

    // �� ��° �����

    int origin_x2 = 28, origin_y2 = 27;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x2, origin_y2 + y);
        if (y == h)
            printf("��");
        else if (y == 0)
            printf("��");
        else
            printf("��");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x2 + (w + 1) * 2, origin_y2 + y);
        if (y == h)
            printf("��");
        else if (y == 0)
            printf("��");
        else
            printf("��");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2);
        printf("��");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2 + h);
        printf("��");
    }

    setCurrentCursorPos(12,28);
    printf("[store]");
}



void drawInfo(double *score, int gradeIdx)
{
    setCurrentCursorPos(14, 1);
    printf("[%d �г�]", gradeIdx);

    setCurrentCursorPos(28, 1);
    printf("���� ���� : %.1f", score[gradeIdx]);

    setCurrentCursorPos(48, 1);
    printf("��� ���� : %.1f", score[0]);
}



void drawBossLife()
{
    int x, y;
    int origin_x = 80, origin_y = 8, h = 15, w = 1;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x, origin_y + y);
        if (y == h)
            printf("��");
        else
            printf("��");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x + (w + 1) * 2, origin_y + y);
        if (y == h)
            printf("��");
        else
            printf("��");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x + x * 2, origin_y + h);
        printf("��");
    }

    setCurrentCursorPos(origin_x, origin_y + h + 1);
    printf("[Boss]");

}

//void drawAttackdot(int dotNum);

//void removeAttackDot();

//void removeAttackTouchedWall();

void removeBossLife()
{
    int x, y;
    int origin_x = 80, origin_y = 8, h = 15, w = 1;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x, origin_y + y);
        if (y == h)
            printf("  ");
        else
            printf("  ");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x + (w + 1) * 2, origin_y + y);
        if (y == h)
            printf("  ");
        else
            printf("  ");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x + x * 2, origin_y + h);
        printf("  ");
    }
}

/*
int* randomEmergencyExit(int posX, int posY, int gameMap[22][37]) // �̿�
{
    srand((unsigned int)time(NULL));
    int num = rand() % Exit_n;

    while (!(Exit[num][0] == posX && Exit[num][1] == posY)) //����� ���� ��ġ�� ������ �ȵȴ�.
    {
        num = rand() % Exit_n;
    }


}
*/

//void drawGameResult();

//void removeGameResult();


