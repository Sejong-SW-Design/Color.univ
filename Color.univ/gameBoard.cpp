#include "gameBoard.h"
#include "move.h"

int Exit[5][2]; // 비상구 전역 변수 배열
int Exit_n = 0; // 비상구 수

extern double score[5];

void drawGameBoard(int gameMap[22][37])
{
    drawInfo(score, 1);
    drawStore();

    // if(grade==4)
    drawBossLife();

    for (int i = 0; i < 22; i++)
    {
        setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y+i); // 위치
        for (int j = 0; j < 37; j++)
        {
            switch (gameMap[i][j])
            {
            case NORMAL_WALL:
                setBackgroundColor(0, 7); printf("■"); break;
            case BLANK:
                printf("  "); break;
            case BLUE_WALL:
                setBackgroundColor(0, 9); printf("■"); break;
            case RED_WALL:
                setBackgroundColor(0, 12); printf("■");  break;
            case YELLOW_WALL:
                setBackgroundColor(0, 14); printf("■");  break;
            case PURPLE_WALL:
                setBackgroundColor(0, 13); printf("■");  break;
            case GREEN_WALL:
                setBackgroundColor(0, 10); printf("■"); break;
            case ORANGE_WALL:
                setBackgroundColor(0, 6); printf("■");  break;
            case CYAN_WALL:
                setBackgroundColor(0, 3); printf("■");  break;
            case DARKBLUE_WALL:
                setBackgroundColor(0, 1); printf("■");  break;
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
                setBackgroundColor(0, 2); printf("▥"); 
                Exit[Exit_n][0] = i; Exit[Exit_n][1] = j;
                Exit_n++;
                break;
            case PRIME:
                setBackgroundColor(0, 6); printf("★"); break;
            case ERASER:
                setBackgroundColor(0, 15); printf("ⓔ"); break;
            }
        }
        
        printf("\n");
        
    }
}

void updateGameBoard(int gameMap[22][37]) // 게임보드, 게임 정보 업데이트  -> 미완
{
    drawInfo(score, 1);

    for (int i = 0; i < 22; i++)
    {
        setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + i); // 위치
        for (int j = 0; j < 37; j++)
        {
            switch (gameMap[i][j])
            {
            case NORMAL_WALL:
                setBackgroundColor(0, 7); printf("■"); break;
            case BLANK:
                printf("  "); break;
            case BLUE_WALL:
                setBackgroundColor(0, 9); printf("■"); break;
            case RED_WALL:
                setBackgroundColor(0, 12); printf("■");  break;
            case YELLOW_WALL:
                setBackgroundColor(0, 14); printf("■");  break;
            case PURPLE_WALL:
                setBackgroundColor(0, 13); printf("■");  break;
            case GREEN_WALL:
                setBackgroundColor(0, 10); printf("■"); break;
            case ORANGE_WALL:
                setBackgroundColor(0, 6); printf("■");  break;
            case CYAN_WALL:
                setBackgroundColor(0, 3); printf("■");  break;
            case DARKBLUE_WALL:
                setBackgroundColor(0, 1); printf("■");  break;
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

        printf("\n");

    }
}

//해제할 벽 해제 여부를 반환 -> 해제를 하나도 안 했다면 스토어에 저장, 해제한 게 있으면 저장노
bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37]) //같은 색 있으면 없애고, 아니면 return -> 미완!!
{
    bool didRemove = false;
    gameMap[posY][posX] = 0; // 색 버튼 없앰 -> 이게 플레이어도 같이 삭제했던거임 (복)

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

void updateStore(int color1, int color2) // 새로 만듦 -> ppt에 추가해야함
{
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
                printf("■");
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
                printf("■");
            }
        }
    }

}

void drawStore() 
{
    int x, y;

    // 첫번째 저장소
    int origin_x1 = 20, origin_y1 = 27, h = 2, w = 2;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x1, origin_y1 + y);
        if (y == h)
            printf("└");
        else if (y == 0)
            printf("┌");
        else
            printf("│");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x1 + (w + 1) * 2, origin_y1 + y);
        if (y == h)
            printf("┘");
        else if (y == 0)
            printf("┐");
        else
            printf("│");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1);
        printf("─");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1 + h);
        printf("─");
    }

    // 두 번째 저장소

    int origin_x2 = 28, origin_y2 = 27;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x2, origin_y2 + y);
        if (y == h)
            printf("└");
        else if (y == 0)
            printf("┌");
        else
            printf("│");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x2 + (w + 1) * 2, origin_y2 + y);
        if (y == h)
            printf("┘");
        else if (y == 0)
            printf("┐");
        else
            printf("│");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2);
        printf("─");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2 + h);
        printf("─");
    }

    setCurrentCursorPos(12,28);
    printf("[store]");
}



void drawInfo(double *score, int gradeIdx)
{
    setCurrentCursorPos(14, 1);
    printf("[%d 학년]", gradeIdx);

    setCurrentCursorPos(28, 1);
    printf("현재 학점 : %.1f", score[gradeIdx]);

    setCurrentCursorPos(48, 1);
    printf("평균 학점 : %.1f", score[0]);
}



void drawBossLife()
{
    int x, y;
    int origin_x = 80, origin_y = 8, h = 15, w = 1;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x, origin_y + y);
        if (y == h)
            printf("└");
        else
            printf("│");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x + (w + 1) * 2, origin_y + y);
        if (y == h)
            printf("┘");
        else
            printf("│");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x + x * 2, origin_y + h);
        printf("─");
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
int* randomEmergencyExit(int posX, int posY, int gameMap[22][37]) // 미완
{
    srand((unsigned int)time(NULL));
    int num = rand() % Exit_n;

    while (!(Exit[num][0] == posX && Exit[num][1] == posY)) //현재와 같은 위치로 나오면 안된다.
    {
        num = rand() % Exit_n;
    }


}
*/

//void drawGameResult();

//void removeGameResult();


