#include "gameBoard.h"
#include "move.h"
#include "item.h"

//점수 계산 맨 밑에 있어용

vector<pair<int, int>>Exits; //비상구 배열
//vector<int>Life;
extern double score[5];
extern int stage;
 

Pos setPcInitPos(int stage) //(게임보드 기준! 곱하기 2 이딴거 안해도됨)
{
    switch (stage)
    {
    case 1:
        return { 18,0 };
    case 2: case 3:
        return  { 1,10 };
    case 4:
        return { 1,10 }; //  임시
    default:
        return { 1,10 };
    }
}

vector<PatternNpc*> setPatternNpcInitPos(int stage, vector<PatternNpc*> P)
{
    P.clear();

    switch (stage)
    {
    case 1:
        P.push_back(new PatternNpc({ 32,13 }, { 32,7 }, { 32,14 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 23,8 }, { 22,8 }, { 26,8 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 23,13 }, { 22,13 }, { 26,13 }, NORMAL_NPC));
        //P.push_back(new PatternNpc({ 22,10 }, { 22,9 }, { 22,12 }, NORMAL_NPC));
        //P.push_back(new PatternNpc({ 26,10 }, { 26,9 }, { 26,12 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 11,11 }, { 10,11 }, { 14,11 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 4,13 }, { 4,7 }, { 4,14 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 19,10 }, { 19,6 }, { 19,15 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 17,1 }, { 16,1 }, { 20,1 }, NORMAL_NPC));

        break;
    case 2:
        P.push_back(new PatternNpc({ 19, 5 }, { 19, 4 }, { 19, 6 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 12,17 }, { 12,15 }, { 12,17 }, NORMAL_NPC));

        P.push_back(new PatternNpc({ 6,18 }, { 4,18 }, { 7,18 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 12, 10 }, { 12, 8 }, { 12, 13 }, ALCOHOL_NPC)); 
        break;
    case 3:
        P.push_back(new PatternNpc({ 34,9 }, { 34,8 }, { 34,10 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 34,12 }, { 34,13 }, { 34,11 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 27, 2 }, { 27, 1 }, { 27, 4 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 29, 4 }, { 28, 4 }, { 30, 4 }, NORMAL_NPC));   

        P.push_back(new PatternNpc({ 14, 15 }, { 12, 15 }, { 21, 15 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 14, 18 }, { 12, 18 }, { 21, 18 }, NORMAL_NPC));

        P.push_back(new PatternNpc({ 12, 17 }, { 12, 16 }, { 12, 17 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 21, 17 }, { 21, 16 }, { 21, 17 }, NORMAL_NPC));
    
        P.push_back(new PatternNpc({ 5, 16 }, { 4, 16 }, { 7, 16 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 5, 5 }, { 4, 5 }, { 7, 5 }, ALCOHOL_NPC));
        break;
    case 4:
        P.push_back(new PatternNpc({ 18, 6 }, { 17, 6 }, { 20, 6 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 10, 15 }, { 9, 15 }, { 12, 15 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 15, 10 }, { 15, 9 }, { 15, 12 }, NORMAL_NPC));

        P.push_back(new PatternNpc({ 1, 7 }, { 0, 7 }, { 2, 7 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 26, 17 }, { 25, 17 }, { 28, 17 }, ALCOHOL_NPC));

        break;
    }
    

    return P;
}

vector<ChasingNpc*> setChasingNpcInitPos(int stage, vector<ChasingNpc*> C)
{
    C.clear();

    switch (stage)
    {
    case 1:
        //C.push_back(new ChasingNpc({ 5, 17 })); //  정신 사나워서 주석
        C.push_back(new ChasingNpc({ 31, 4 })); 
        break;
    case 2:
        C.push_back(new ChasingNpc({ 26, 5 }));
        break;
    case 3:
        C.push_back(new ChasingNpc({ 9, 4 }));
        C.push_back(new ChasingNpc({ 19, 17 }));
        C.push_back(new ChasingNpc({ 19, 16 }));
        break;
    case 4:
    
        C.push_back(new ChasingNpc({ 12, 1 }));
        break;
    }
    return C;
}

vector<ShootNpc*> setShootNpcInitPos(int stage, vector<ShootNpc*> S)
{
    S.clear();

    switch (stage)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        S.push_back(new ShootNpc({ 16, 8 }, SHOOT_NPC_UP));
        S.push_back(new ShootNpc({ 17, 8 }, SHOOT_NPC_UP));
        S.push_back(new ShootNpc({ 18, 8 }, SHOOT_NPC_UP));
        S.push_back(new ShootNpc({ 15, 9 }, SHOOT_NPC_LEFT));
        S.push_back(new ShootNpc({ 15, 10}, SHOOT_NPC_LEFT));
        S.push_back(new ShootNpc({ 19, 9 }, SHOOT_NPC_RIGHT));
        S.push_back(new ShootNpc({ 19, 10 }, SHOOT_NPC_RIGHT));
        S.push_back(new ShootNpc({ 16, 11 }, SHOOT_NPC_DOWN));
        S.push_back(new ShootNpc({ 17, 11 }, SHOOT_NPC_DOWN));
        S.push_back(new ShootNpc({ 18, 11 }, SHOOT_NPC_DOWN));
        break;
    case 4:
        break;
    }
    return S;
}

void drawOnePoint(int gameMap[22][37], int i, int j)
{
    drawOnePoint(gameMap, i, j, 0);
}
//게임보드 x y 좌표 기준으로 받는다!!
void drawOnePoint(int gameMap[22][37], int i, int j, int backGround)
{
    int flag = 0; // 비상구 때문에!
    Pos cursorPosition = Move::getCursorPos({j, i});
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
    switch (gameMap[i][j])
    {
    case NORMAL_WALL:
        if (stage == 4) setBackgroundColor(backGround, 8); // 어두운 회색
        else setBackgroundColor(backGround, 7); // 그냥 회색
        printf("■"); break;
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
        for (int k = 0; k < Exits.size(); k++) // 이거 안해서 비상구 이상했음
        {
            if (Exits[k].first == i && Exits[k].second == j) //같은 것이 있다면
            {
                flag = 1;
            }
        }
        if(flag==0) Exits.push_back(make_pair(i, j));
        break;
    case PRIME:
        setBackgroundColor(backGround, 6); printf("★"); break;
    case ERASER:
        setBackgroundColor(backGround, 15); printf("ⓔ"); break;
    case LIFE:
        setBackgroundColor(backGround, 4); printf("♥"); break; // npc랑 헷갈릴까봐 다크 레드 사용
    case SPEED:
        setBackgroundColor(backGround, 7); printf("⒮"); break; // eraser랑 헷갈릴까봐
    case NORMAL_NPC:
        setBackgroundColor(backGround, 12); printf("%s", Move::getNpcShape(NORMAL_NPC).c_str()); break;
    case ALCOHOL_NPC:
        setBackgroundColor(backGround, 12); printf("%s", Move::getNpcShape(ALCOHOL_NPC).c_str()); break;
    case CHASING_NPC:
        setBackgroundColor(backGround, 12); printf("%s", Move::getNpcShape(CHASING_NPC).c_str()); break;
    case SHOOT_NPC_LEFT:
        setBackgroundColor(backGround, 12); printf("%s", Move::getNpcShape(SHOOT_NPC_LEFT).c_str()); break;
    case SHOOT_NPC_RIGHT:
        setBackgroundColor(backGround, 12); printf("%s", Move::getNpcShape(SHOOT_NPC_RIGHT).c_str()); break;
    case SHOOT_NPC_UP:
        setBackgroundColor(backGround, 12); printf("%s", Move::getNpcShape(SHOOT_NPC_UP).c_str()); break;
    case SHOOT_NPC_DOWN:
        setBackgroundColor(backGround, 12); printf("%s", Move::getNpcShape(SHOOT_NPC_DOWN).c_str()); break;
    }
}

void drawGameBoard(int gameMap[22][37],int stage)
{
    drawGameEdge();
    drawStore();  
    if (stage != 1) drawAlcoholTime();
    drawLifeEdge();
    updateAlcoholTime(0); // 알코올 처음엔 X
    // updateAlcoholTime(10); // 알코올 만땅

    drawInfoOriginal(score, stage);


    Exits.clear();

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 37; j++)
        {
            drawOnePoint(gameMap, i, j);
        }
    }
}

void drawGameEdge()
{
    int x, y;

    int origin_x1 = 4, origin_y1 = 3, h = 23, w = 37;
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


//벽 해제 애니메이션 때문이 임시로 만들었었으(이지호)
int getWallColor(int gameBoardWallNumber)
{
    switch (gameBoardWallNumber)
    {
    case BLUE_WALL:
        return 9;
    case RED_WALL:
        return 12;
    case YELLOW_WALL:
        return 14;
    case PURPLE_WALL:
        return 5;
    case GREEN_WALL:
        return 10;
    case ORANGE_WALL:
        return 6;
    case DARKBLUE_WALL:
        return 1;
    case DARKGREEN_WALL:
        return 2;
    case DARKSKYBLUE_WALL:
        return 3;
    case DARKRED_WALL:
        return 4;
    case PINK_WALL:
        return 13;
    case DARKYELLOW_WALL:
        return 6;
    case DARKGRAY_WALL:
        return 8;
    case SKYBLUE_WALL:
        return 11;
    }
    return 0;

}

bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37]) //같은 색 있으면 없애고, 아니면 return -> 미완!!
{
    vector<Pos>ErasePos;
    int filter[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1} };
    queue<pair<int, int>> q;
    bool visited[22][37] = { 0 };

    //벽 해제 애니메이션 관련
    vector<pair<int, int>>outLines;

    //bfs
    q.push(make_pair(posY, posX));
    visited[posY][posX] = true;
    while (!q.empty())
    {
        pair<int, int>now = q.front();
        q.pop();
        
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
                ErasePos.push_back({ nextX, nextY });
                continue;
            }
            if (Move::isWall(gameMap[nextY][nextX]))
            {
                outLines.push_back(make_pair(nextY, nextX));
                continue;
            }
            q.push(make_pair(nextY, nextX));
            visited[nextY][nextX] = true;
            setCurrentCursorPos(2 * nextX + GBOARD_ORIGIN_X, nextY + GBOARD_ORIGIN_Y);
        }
    }

    if (ErasePos.empty())
        return false;

    //벽을 해제한 경우만 애니메이션
    for (auto e : outLines)
    {
        drawOnePoint(gameMap, e.first, e.second, getWallColor(colorSort));
    }

    for (auto e : ErasePos)
    {
        gameMap[e.y][e.x] = 0;
        drawOnePoint(gameMap, e.y, e.x);
    }

    Sleep(50);
    for (auto e : outLines)
    {
        drawOnePoint(gameMap, e.first, e.second);
    }

    return true;
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




void drawLifeEdge() // 하트 테두리 + 초기 하트 설정
{
    int x, y, h = 2, w = 6;

    int origin_x = 57, origin_y = 27;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x, origin_y + y);
        if (y == h)
            printf("└");
        else if (y == 0)
            printf("┌");
        else
            printf("│");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x + (w + 1) * 2, origin_y + y);
        if (y == h)
            printf("┘");
        else if (y == 0)
            printf("┐");
        else
            printf("│");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x + x * 2, origin_y);
        printf("─");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x + x * 2, origin_y + h);
        printf("─");
    }

    setCurrentCursorPos(50, 28);
    printf("[life]");

    
    origin_x = 59, origin_y = 28;
    for (x = 0; x < 3; x++)
    {
        setCurrentCursorPos(origin_x + (x * 3) + 2, origin_y);
        setBackgroundColor(0, 4); // 어두운 빨강
        printf("♥");

        //Life.push_back(1);
        
        // 하트 1,2,3 기억 
        // 1 -> 하트 있다. 0 -> 하트 없다
    }
    
}



/*
void updateLife() // 하트 업데이트
{   
    
    int x;
    int origin_x = 59, origin_y = 28;
    for (x = 0; x < 3; x++)
    {
        if (Life.at(x) == 1) // 하트가 있다면
        {
            setCurrentCursorPos(origin_x + (x * 3) + 2, origin_y);
            setBackgroundColor(0, 4); // 어두운 빨강
            printf("♥");
        }
    }
    
}
*/
// 하트 줄어드는 것, 늘어나는 것 아이템에서 구현!! -> 색저장소처럼
//이 부분은 없애고 아이템에서 할게여 - 지우



void drawInfo(double *score, int stage)
{
    setCurrentCursorPos(14, 1); 
    printf("[%d 학년]", stage);

    setCurrentCursorPos(34, 1);
    printf("현재 학점 : %.1f", score[stage]);

    setCurrentCursorPos(60, 1);
    printf("평균 학점 : %.1f", score[0]);
}

void drawInfoOriginal(double* score, int stage)
{
    setBackgroundColor(0, 15); // 하얀색
    drawInfo(score, stage);
}

void drawInfoMinus(double* score, int stage)
{
    setBackgroundColor(0, 12); // 빨간색
    drawInfo(score, stage);

    Sleep(150);
    drawInfoOriginal(score, stage);
}

void drawInfoPlus(double* score, int stage)
{
    setBackgroundColor(0, 9); // 파랑색
    drawInfo(score, stage);

    Sleep(150);
    drawInfoOriginal(score, stage);
}

void drawAlcoholTime()
{
    int x, y;
    int origin_x = 85, origin_y = 11, h = 10, w = 1;
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

    setCurrentCursorPos(origin_x-1, origin_y + h + 1);
    printf("[Alcohol]");
}

void updateAlcoholTime(int t)
{
    int y, full = 10;
    int origin_x = 87, origin_y = 11+full-t, h = t, w = 1;
    for (y = 0; y < h; y++)
    {
        setCurrentCursorPos(origin_x, origin_y + y);
        setBackgroundColor(0, 12);
        printf("■");
    }
}


void removeAlcoholTime()
{
    int x, y;
    int origin_x = 85, origin_y = 11, h = 10, w = 1;
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
    /*
    srand((unsigned int)time(NULL));
    
    int idx = rand() % (Exits.size()); // 나올 비상구 idx


    while (Exits[idx].first == posY && Exits[idx].second == posX) //현재와 같은 위치로 나오면 안된다.
    {     
        idx = rand() % (Exits.size());
    }

    return Exits[idx];
    */

    int currIdx=0; 

    for (int i = 0; i < Exits.size(); i++) // 순서대로 한 번씩 다 나오도록
    {
        if (Exits[i].first == posY && Exits[i].second == posX)
        {
            currIdx = i;
            break;
        }
    }

    int idx = (currIdx + 1) % Exits.size();

    return Exits[idx];
}

void drawGameResult(double* score, int stage)
{
    Sleep(1300);

    system("cls");

    setBackgroundColor(0, 14);
    setCurrentCursorPos(36, 10);
    printf("[  %d 학년  ]",stage);


    setBackgroundColor(0, 15);
    setCurrentCursorPos(33, 13);
    printf("최종 학점 : %.1f  %s", score[stage],calculate(score[stage]).c_str());


    setCurrentCursorPos(33, 15);
    printf("평균 학점 : %.1f", score[0]);

    if (score[stage] == 0) // gameover일 때
    {
        setCurrentCursorPos(35, 18);
        setBackgroundColor(0, 7);
        printf("퇴학입니다.");
    }
    else if (stage == 1)
    {
        setCurrentCursorPos(30, 18);
        setBackgroundColor(0, 7);
        printf("2학년에는 술이 등장합니다");
    }
    else if (stage == 2)
    {
        setCurrentCursorPos(27, 18);
        setBackgroundColor(0, 7);
        printf("벌써 3학년이라니..시간 참 빠르다");
    }
    else if (stage == 3)
    {
        setCurrentCursorPos(33,18);
        setBackgroundColor(0, 7);
        printf("왜 이렇게 어둡지...?");

        setCurrentCursorPos(34, 19);
        setBackgroundColor(0, 7);
        printf("내 미래인가...?");
    }
    else if (stage == 4)
    {
        setCurrentCursorPos(37, 18);
        setBackgroundColor(0, 7);
        printf("축★졸업");
    }


    Sleep(2500);

}

string calculate(double score) // 학점 계산
{
    string result;
    if (score == 4.5)
    {
        result = "A+";
    }
    else if (score == 4.0)
    {
        result = "A0";
    }
    else if (score == 3.5)
    {
        result = "B+";
    }
    else if (score == 3.0)
    {
        result = "B0";
    }
    else if (score == 2.5)
    {
        result = "C+";
    }
    else if (score == 2.0)
    {
        result = "C0";
    }
    else
    {
        result = "F";
    }
    return result;
}



