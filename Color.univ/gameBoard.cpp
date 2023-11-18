#include "gameBoard.h"
#include "move.h"

vector<pair<int, int>>Exits; //비상구 배열
vector<pair<int, int>>dots; 
extern double score[5];

Pos setPcInitPos(int stage)
{
    switch (stage)
    {
    case 1: case 3:
        return { 1,10 };
    case 2:
        return { 16,1 };
    case 4:
        return { 1,10 }; //  임시
    default:
        return { 1,10 };
    }
}

vector<PatternNpc*> setPatternNpcInitPos(int stage, vector<PatternNpc*> P)
{
    switch (stage)
    {
    case 1:
        P.push_back(new PatternNpc({ 6,18 }, { 4,18 }, { 7,18 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 12,17 }, { 12,15 }, { 12,17 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 19, 5 }, { 19, 4 }, { 19, 6 }, ALCOHOL_NPC));
    }

    return P;
}

vector<ChasingNpc*> setChasingNpcInitPos(int stage, vector<ChasingNpc*> C)
{
    switch (stage)
    {
    case 1:
        C.push_back(new ChasingNpc({ 26, 5 }));
        break;
    case 2:
        C.push_back(new ChasingNpc({ 4, 17 }));
        C.push_back(new ChasingNpc({ 4, 31 }));
        break;
    case 3:
        C.push_back(new ChasingNpc({ 26, 5 }));
        break;
    }
    return C;
}

void drawOnePoint(int gameMap[22][37], int i, int j)
{
    drawOnePoint(gameMap, i, j, 0);
}

void drawOnePoint(int gameMap[22][37], int i, int j, int backGround)
{
    Pos cursorPosition = Move::getCursorPos({j, i});
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
    switch (gameMap[i][j])
    {
    case NORMAL_WALL:
        setBackgroundColor(backGround, 7); printf("■"); break;
    case BLANK:
        setBackgroundColor(backGround, backGround); printf("■"); break;
    case GOAL:
        setBackgroundColor(backGround, backGround); printf("■"); break;
    case BLUE_WALL:
        setBackgroundColor(backGround, 9); printf("■"); break;
    case RED_WALL:
        setBackgroundColor(backGround, 12); printf("■");  break;
    case YELLOW_WALL:
        setBackgroundColor(backGround, 14); printf("■");  break;
    case PURPLE_WALL:
        setBackgroundColor(backGround, 5); printf("■");  break;
    case GREEN_WALL:
        setBackgroundColor(backGround, 10); printf("■"); break;
    case ORANGE_WALL:
        setBackgroundColor(backGround, 6); printf("■");  break;
    case DARKBLUE_WALL:
        setBackgroundColor(backGround, 1); printf("■");  break;
    case DARKGREEN_WALL:
        setBackgroundColor(backGround, 2); printf("■");  break;
    case DARKSKYBLUE_WALL:
        setBackgroundColor(backGround, 3); printf("■");  break;
    case DARKRED_WALL:
        setBackgroundColor(backGround, 4); printf("■");  break;
    case PINK_WALL:
        setBackgroundColor(backGround, 13); printf("■");  break;
    case DARKYELLOW_WALL:
        setBackgroundColor(backGround, 6); printf("■");  break;
    case DARKGRAY_WALL:
        setBackgroundColor(backGround, 8); printf("■");  break;
    case SKYBLUE_WALL:
        setBackgroundColor(backGround, 11); printf("■");  break;

    case BLUE_BTN:
        setBackgroundColor(backGround, 9); printf("⊙"); break;
    case RED_BTN:
        setBackgroundColor(backGround, 12); printf("⊙"); break;
    case YELLOW_BTN:
        setBackgroundColor(backGround, 14); printf("⊙"); break;
    case PURPLE_BTN:
        setBackgroundColor(backGround, 5); printf("⊙");  break;
    case GREEN_BTN:
        setBackgroundColor(backGround, 10); printf("⊙"); break;
    case ORANGE_BTN:
        setBackgroundColor(backGround, 6); printf("⊙");  break;
    case DARKBLUE_BTN:
        setBackgroundColor(backGround, 1); printf("⊙"); break;
    case DARKGREEN_BTN:
        setBackgroundColor(backGround, 2); printf("⊙");  break;
    case DARKSKYBLUE_BTN:
        setBackgroundColor(backGround, 3); printf("⊙");  break;
    case DARKRED_BTN:
        setBackgroundColor(backGround, 4); printf("⊙");  break;
    case PINK_BTN:
        setBackgroundColor(backGround, 13); printf("⊙");  break;
    case DARKYELLOW_BTN:
        setBackgroundColor(backGround, 6); printf("⊙");  break;
    case DARKGRAY_BTN:
        setBackgroundColor(backGround, 8); printf("⊙");  break;
    case SKYBLUE_BTN:
        setBackgroundColor(backGround, 11); printf("⊙");  break;

    case EMERGENCY_EXIT:
        setBackgroundColor(backGround, 2); printf("▥");
        Exits.push_back(make_pair(i, j));
        break;
    case PRIME:
        setBackgroundColor(backGround, 6); printf("★"); break;
    case ERASER:
        setBackgroundColor(backGround, 15); printf("ⓔ"); break;
    case HIDDEN:
        setBackgroundColor(backGround, 13); printf("♥"); break;
    case STOP:
        setBackgroundColor(backGround, 7); printf("※"); break;
    case NORMAL_NPC:
        setBackgroundColor(backGround, 12); printf("▲"); break;
    case ALCOHOL_NPC:
        setBackgroundColor(backGround, 12); printf("§"); break;
    }
}

void drawGameBoard(int gameMap[22][37])
{
    drawInfo(score, 1);
    drawStore();
    drawGameEdge();
    //if (gradeidx == 4) drawBossLife();

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 37; j++)
        {
            drawOnePoint(gameMap, i, j);
        }
        
        printf("\n");
        
    }
}


void drawGameEdge()
{
    int x, y;

    int origin_x1 = 4, origin_y1 = 2, h = 24, w = 38;
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
}

////벽 해제 애니메이션 때문이 임시로 만들었었으(이지호)
//int getWallColor(int GAMEBOARD_NUM)
//{
//    switch (GAMEBOARD_NUM)
//    {
//    case BLUE_WALL:
//        return 9;
//    case RED_WALL:
//        return 12;
//    case YELLOW_WALL:
//        return 14;
//    case PURPLE_WALL:
//        return 5;
//    case GREEN_WALL:
//        return 10;
//    case ORANGE_WALL:
//        return 6;
//    case DARKBLUE_WALL:
//        return 1;
//    case DARKGREEN_WALL:
//        return 2;
//    case DARKSKYBLUE_WALL:
//        return 3;
//    case DARKRED_WALL:
//        return 4;
//    case PINK_WALL:
//        return 13;
//    case DARKYELLOW_WALL:
//        return 6;
//    case DARKGRAY_WALL:
//        return 8;
//    case SKYBLUE_WALL:
//        return 11;
//    }
//    return 0;
//
//}

bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37]) //같은 색 있으면 없애고, 아니면 return -> 미완!!
{
    bool didRemove = false;
    //gameMap[posY][posX] = BLANK;
    vector<Pos>ErasePos;
    int filter[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1} };
    queue<pair<int, int>> q;
    bool visited[22][37] = { 0 };

    //temptemp
    vector<pair<int, int>>tempbackgrounds;

    //bfs
    q.push(make_pair(posY, posX));
    visited[posY][posX] = true;
    while (!q.empty())
    {
        pair<int, int>now = q.front();
        q.pop();
        
        //벽 해제 애니메이션 관련
        /*drawOnePoint(gameMap, now.first, now.second, mytemptemptemptempFunc(colorSort));
        tempbackgrounds.push_back(now);*/

        for (int k = 0; k < 8; k++)
        {
            int nextY = now.first + filter[k][0];
            int nextX = now.second + filter[k][1];
            if (nextY < 0 || nextX < 0 || nextY >= 22 || nextX >= 37)
                continue;
            if (visited[nextY][nextX])
                continue;
            if (gameMap[nextY][nextX] == colorSort)
            {
                didRemove = true;
                ErasePos.push_back({ nextX, nextY });
                continue;
            }
            if (Move::isWall(gameMap[nextY][nextX]))
                continue;
            q.push(make_pair(nextY, nextX));
            visited[nextY][nextX] = true;
            setCurrentCursorPos(2 * nextX + GBOARD_ORIGIN_X, nextY + GBOARD_ORIGIN_Y);
        }
    }

    for (auto e : ErasePos)
    {
        Pos cursorPos = Move::getCursorPos(e);
        setCurrentCursorPos(cursorPos.x, cursorPos.y);
        gameMap[e.y][e.x] = 0;
        drawOnePoint(gameMap, e.y, e.x);
    }

    //벽 해제 애니메이션 관련
    //Sleep(50);
    //for (auto e : tempbackgrounds)
    //{
    //    drawOnePoint(gameMap, e.first, e.second);
    //}

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

    setCurrentCursorPos(33, 1);
    printf("현재 학점 : %.1f", score[gradeIdx]);

    setCurrentCursorPos(58, 1);
    printf("평균 학점 : %.1f", score[0]);
}


void drawBossLife()
{
    int x, y;
    int origin_x = 84, origin_y = 8, h = 15, w = 1;
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

void drawAttackdot(int gameMap[22][37])
{
    srand((unsigned int)time(NULL));

    // 미완

    return;
}

//void removeAttackDot();

//void removeAttackTouchedWall();

void removeBossLife()
{
    int x, y;
    int origin_x = 84, origin_y = 8, h = 15, w = 1;
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

pair<int, int> randomEmergencyExit(int posX, int posY, int gameMap[22][37]) // 목적지 배열 return
{
    srand((unsigned int)time(NULL));

    int idx = rand() % Exits.size(); // 나올 비상구 idx

    while (Exits[idx].first == posY && Exits[idx].second == posX) //현재와 같은 위치로 나오면 안된다.
    {
        idx = rand() % Exits.size();
    }

    return Exits[idx];
}

//void drawGameResult();

//void removeGameResult();


