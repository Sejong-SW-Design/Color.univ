#include "gameBoard.h"
#include "move.h"
#include "item.h"

//점수 계산 맨 밑에 있어용

vector<pair<int, int>>Exits; //비상구 배열
extern double score[5];
extern int stage;
extern int life[3];
extern int IsAlcoholTime;
extern int IsSpeedTime;
extern double keyInterval;


int checkB = 0; // 시간 확인

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
        P.push_back(new PatternNpc({ 26, 2 }, { 26, 1 }, { 26, 4 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 29, 4 }, { 27, 4 }, { 30, 4 }, NORMAL_NPC));   

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
        P.push_back(new PatternNpc({ 10, 2 }, { 9, 2 }, { 12, 2 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 15, 10 }, { 15, 9 }, { 15, 12 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 18, 6 }, { 17,6 }, { 20, 6 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 10, 6 }, { 9,6 }, { 12, 6 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 30, 5 }, { 29,5 }, { 32, 5 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 18,16 }, { 17,16 }, { 18, 16 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 20,16 }, { 19,16 }, { 20, 16 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 24,10 }, { 24,9 }, { 24, 12 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 16,1 }, { 16,1 }, { 16, 2 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 21,1 }, { 21,1 }, { 21, 2 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 6,17 }, { 6,16 }, {6, 20 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 6,2 }, { 4,2 }, { 7, 2 }, NORMAL_NPC));
        P.push_back(new PatternNpc({ 31,17 }, { 30,17 }, { 32, 17 }, NORMAL_NPC));


        P.push_back(new PatternNpc({ 1, 7 }, { 0, 7 }, { 2, 7 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 1, 12 }, { 0, 12 }, { 2, 12 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 26, 16 }, { 25, 16 }, { 28, 16 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 19, 5 }, { 17,5 }, { 20, 5 }, ALCOHOL_NPC));
        P.push_back(new PatternNpc({ 19, 18 }, { 17,18 }, { 20, 18 }, ALCOHOL_NPC));

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
    
        //C.push_back(new ChasingNpc({ 7, 7 })); // 추적 X
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

void drawGameBoard(int gameMap[22][37], int stage)
{   
    drawGameEdge();
    drawStore();
    if (stage != 1) drawAlcoholTimeEdge();
    

    drawLifeEdge();

    drawInfoOriginal(score, stage);

    drawPause();
    Exits.clear();

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 37; j++)
        {
            drawOnePoint(gameMap, i, j);
        }
    }
}


void drawPause()
{
    setBackgroundColor(0, 8);
    setCurrentCursorPos(30, 31);
    printf("게임을 중단하고 싶다면 p를 누르세요");
}


void drawAllDarkGameBoard(int gameMap[22][37], int stage) // manager에 넣기 위해 새로 만듦. 근데 필요 없어졌음 ㅋ 혹시 몰라 일단 놔둠용
{
    drawGameEdge();
    drawStore();
    if (stage != 1) drawAlcoholTimeEdge();

    drawLifeEdge();

    drawInfoOriginal(score, stage);

    drawPause();
    Exits.clear();

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 37; j++)
        {
            drawOnePoint(gameMap, i, j, 0, 0);
        }
    }
}

void drawOnePoint(int gameMap[22][37], int i, int j)
{
    int textColor = getColor(gameMap[i][j]);
    drawOnePoint(gameMap, i, j, 0, textColor);
}

void drawOnePoint(int gameMap[22][37], int i, int j, int backGround) // 새로 만듦 -> 혹시 함수를 합치고 싶다면 합치세요.
{
    int textColor = getColor(gameMap[i][j]);
    drawOnePoint(gameMap, i, j, backGround, textColor);
}


//새로 만듦
void drawDarkGameBoard(int gameMap[22][37], Player player) 
// getColor 함수는 맨 밑에 있습니다.
{
    drawGameEdge();
    drawStore();
    drawAlcoholTimeEdge();

    drawLifeEdge();

    drawInfoOriginal(score, stage);

    drawPause();
    Exits.clear();

    int textColor;

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 37; j++)
        {
            if (player.isVisiblePos({j, i})) 
            {
                textColor = getColor(gameMap[i][j]);
            }
            else textColor = 0; // 반경이 아니라면 검정색
            drawOnePoint(gameMap, i, j, 0, textColor);
        }
    }
}

void blinkGameBoard(int gameMap[22][37], Player player, EnemiesManager enemies) // ppt 추가
{
    time_t current;
    time(&current);

    int vD = 4;

    if (difftime(current, player.drawStartTime) >= 5 && checkB == 2)
    {
        checkB++; // 3이 됨, 5초 지남 체크, blinkGameBoard 종료
        (&player)->visibleDist = vD;

        drawDarkGameBoard(gameMap, player);
        player.showCharacter();

        return;
    }
    else if (difftime(current, player.drawStartTime) >= 3 && checkB == 1)
    {
        checkB++; //2가 됨

        drawGameBoard(gameMap, stage);
        player.showCharacter();
        enemies.updateColor(gameMap, player);
    }
    else if (difftime(current, player.drawStartTime) >= 2 && checkB == 0)
    {
        checkB++; //1이 됨

        (&player)->visibleDist = vD;
        drawDarkGameBoard(gameMap, player);
        player.showCharacter();
    }

    if (checkB % 2 == 1) (&player)->visibleDist = vD; // 홀수면
    else if (checkB % 2 == 0) (&player)->visibleDist = -1; // 짝수면

    return;

}

void drawOnePoint(int gameMap[22][37], int i, int j, int backGround, int textColor)
{
    int flag = 0; // 비상구 때문에!
    Pos cursorPosition = Move::getCursorPos({j, i});
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);

    switch (gameMap[i][j])
    {
    case NORMAL_WALL:
        setBackgroundColor(backGround, textColor); printf("■"); break;
    case BLANK:
        setBackgroundColor(backGround, backGround); printf("■"); break;
    case GOAL:
        setBackgroundColor(backGround, backGround); printf("■"); break;
    case BLUE_WALL:
        setBackgroundColor(backGround, textColor); printf("■"); break;
    case RED_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case YELLOW_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case PURPLE_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case GREEN_WALL:
        setBackgroundColor(backGround, textColor); printf("■"); break;
    case ORANGE_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case DARKBLUE_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case DARKGREEN_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case DARKSKYBLUE_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case DARKRED_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case PINK_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case DARKYELLOW_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case DARKGRAY_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;
    case SKYBLUE_WALL:
        setBackgroundColor(backGround, textColor); printf("■");  break;

    case BLUE_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙"); break;
    case RED_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙"); break;
    case YELLOW_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙"); break;
    case PURPLE_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case GREEN_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙"); break;
    case ORANGE_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case DARKBLUE_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙"); break;
    case DARKGREEN_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case DARKSKYBLUE_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case DARKRED_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case PINK_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case DARKYELLOW_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case DARKGRAY_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;
    case SKYBLUE_BTN:
        setBackgroundColor(backGround, textColor); printf("⊙");  break;

    case EMERGENCY_EXIT:
        //비상구는 항상 빛나야 하니깐 이렇게 함 해봤어.. (임시)
        setBackgroundColor(backGround, getColor(EMERGENCY_EXIT)); printf("▥");
        //setBackgroundColor(backGround, textColor); printf("▥");

        for (int k = 0; k < Exits.size(); k++) 
        {
            if (Exits[k].first == i && Exits[k].second == j) //같은 것이 있다면
            {
                flag = 1;
                break;
            }
        }
        if(flag==0) Exits.push_back(make_pair(i, j));
        break;
    case PRIME:
        setBackgroundColor(backGround, textColor); printf("★"); break;
    case ERASER:
        setBackgroundColor(backGround, textColor); printf("ⓔ"); break;
    case LIFE:
        setBackgroundColor(backGround, textColor); printf("♥"); break; 
    case SPEED:
        setBackgroundColor(backGround, textColor); printf("⒮"); break; // eraser랑 헷갈릴까봐
    case NORMAL_NPC:
        setBackgroundColor(backGround, textColor); printf("%s", Move::getNpcShape(NORMAL_NPC).c_str()); break;
    case ALCOHOL_NPC:
        setBackgroundColor(backGround, textColor); printf("%s", Move::getNpcShape(ALCOHOL_NPC).c_str()); break;
    case CHASING_NPC:
        setBackgroundColor(backGround, textColor); printf("%s", Move::getNpcShape(CHASING_NPC).c_str()); break;
    case SHOOT_NPC_LEFT:
        setBackgroundColor(backGround, textColor); printf("%s", Move::getNpcShape(SHOOT_NPC_LEFT).c_str()); break;
    case SHOOT_NPC_RIGHT:
        setBackgroundColor(backGround, textColor); printf("%s", Move::getNpcShape(SHOOT_NPC_RIGHT).c_str()); break;
    case SHOOT_NPC_UP:
        setBackgroundColor(backGround, textColor); printf("%s", Move::getNpcShape(SHOOT_NPC_UP).c_str()); break;
    case SHOOT_NPC_DOWN:
        setBackgroundColor(backGround, textColor); printf("%s", Move::getNpcShape(SHOOT_NPC_DOWN).c_str()); break;
    }
}


bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37], bool isStage4) //같은 색 있으면 없애고, 아니면 return -> 미완!!
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
    if (isStage4)
        for (auto e : outLines)
            drawOnePoint(gameMap, e.first, e.second, 0, 0);
    else
        for (auto e : outLines)
            drawOnePoint(gameMap, e.first, e.second);
    

    return true;
}


void drawLifeEdge() // 하트 테두리 + 초기 하트 설정
{
    int x, y, h = 2, w = 6;

    setBackgroundColor(0, 15); // 하얀색
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
        if (life[x] == 1) // 스테이지마다 불러오기 때문에 추가.
        {
            setCurrentCursorPos(origin_x + (x * 3) + 2, origin_y);
            setBackgroundColor(0, 4); // 어두운 빨강
            printf("♥");
        }
    }
    
}


void drawAlcoholTimeEdge()
{
    setBackgroundColor(0, 15); // 하얀색
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


void drawAlcoholTime(int t)
{
    int y = 0, full = 10;
    int origin_x = 87, origin_y = 11 + full - t, h = t, w = 1;
    if (t == full) // 처음 술 먹었을 때(만땅)
    {
        for (y = 0; y < h; y++)
        {
            setCurrentCursorPos(origin_x, origin_y + y);
            setBackgroundColor(0, 12);
            printf("■");
        }
    }
    else if (t >= 0)
    {
        setCurrentCursorPos(origin_x, origin_y - 1);
        printf("  ");

        for (y = 0; y < h; y++)
        {
            setCurrentCursorPos(origin_x, origin_y + y);
            setBackgroundColor(0, 12);
            printf("■");
        }
    }
}

void drawCheckTime(Player* player) // 나중에 ppt에 추가해야함
{
    time_t current;
    time(&current);
    if (player->alcoholStartTime != 0 && player->alcoholStartTime != current)
    {
        IsAlcoholTime--;
        drawAlcoholTime(IsAlcoholTime);
        player->alcoholStartTime = current;
    }
    if (current - player->alcoholStartTime == 10)
    {
        player->alcoholStartTime = 0;
    }
    if (player->speedStartTime != 0 && player->speedStartTime != current)
    {
        IsSpeedTime--;
        player->speedStartTime = current;
    }
    if (current - player->speedStartTime >= 5)
    {
        player->speedStartTime = 0;
    }
}

pair<int, int> randomEmergencyExit(int posX, int posY, int gameMap[22][37]) // 목적지 배열 return
{
    // 랜덤
    srand((unsigned int)time(NULL));
    
    int idx = rand() % (Exits.size()); // 나올 비상구 idx


    while (Exits[idx].first == posY && Exits[idx].second == posX) //현재와 같은 위치로 나오면 안된다.
    {     
        idx = rand() % (Exits.size());
    }

    return Exits[idx];

    // 순서대로 한 번씩 다 나오도록
    /*
    int currIdx=0; 

    for (int i = 0; i < Exits.size(); i++) 
    {
        if (Exits[i].first == posY && Exits[i].second == posX)
        {
            currIdx = i;
            break;
        }
    }

    int idx = (currIdx + 1) % Exits.size();

    return Exits[idx];
    */
}

void drawGameResult(double* score, int stage)
{
    Sleep(100);
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
        printf("퇴학이라니...");
    }
    else if (stage == 1)
    {
        setCurrentCursorPos(25, 18);
        setBackgroundColor(0, 7);
        printf("2학년이 되니까 체력이 예전같지가 않네");

        setCurrentCursorPos(30, 19);
        setBackgroundColor(0, 7);
        printf("입만 대도 술병 나겠어ㅜㅜ"); //2학년에 술 등장해서 언금 - 지우
    }
    else if (stage == 2)
    {
        setCurrentCursorPos(34, 18);
        setBackgroundColor(0, 7);
        printf("벌써 3학년이라니...");

        setCurrentCursorPos(27, 19);
        setBackgroundColor(0, 7);
        printf("할 일도 많아지고 으악 스트레스 !!"); //3학년에 추적엔피씨 등장해서 언급 - 지우
    }
    else if (stage == 3)
    {
        setCurrentCursorPos(32, 18);
        setBackgroundColor(0, 7);
        printf("이제 4학년이라 그런가");

        setCurrentCursorPos(34, 19);
        setBackgroundColor(0, 7);
        printf("눈 앞이 막막하네");
    }
    else if (stage == 4)
    {
        setCurrentCursorPos(37, 18);
        setBackgroundColor(0, 7);
        printf("축★졸업");

        setCurrentCursorPos(33, 19);
        setBackgroundColor(0, 7);
        printf("드디어 졸업이다ㅎㅎ");
    }

    Sleep(4000);

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



void updateStore(int color1, int color2)
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
    setBackgroundColor(0, 15); // 하얀색
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

    setCurrentCursorPos(12, 28);
    printf("[store]");
}

void drawGameEdge()
{
    setBackgroundColor(0, 15); // 하얀색
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



void drawInfo(double* score, int stage)
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

    Sleep(130);
    drawInfoOriginal(score, stage);
}

void drawInfoPlus(double* score, int stage)
{
    setBackgroundColor(0, 9); // 파랑색
    drawInfo(score, stage);

    Sleep(130);
    drawInfoOriginal(score, stage);
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


// 새로 만듦
int getColor(int gameBoardNumber) // enum 색 얻어오는 함수
{
    switch (gameBoardNumber)
    {
    case NORMAL_WALL:
        if (stage == 4) return 8;
        else return 7;
    case BLANK:
        return 0;
    case GOAL:
        return 0;
    case BLUE_WALL: case BLUE_BTN:
        return 9;
    case RED_WALL: case RED_BTN:
        return 12;
    case YELLOW_WALL: case YELLOW_BTN:
        return 14;
    case PURPLE_WALL: case PURPLE_BTN:
        return 5;
    case GREEN_WALL: case GREEN_BTN:
        return 10;
    case ORANGE_WALL: case ORANGE_BTN:
        return 6;
    case DARKBLUE_WALL: case DARKBLUE_BTN:
        return 1;
    case DARKGREEN_WALL: case DARKGREEN_BTN:
        return 2;
    case DARKSKYBLUE_WALL: case DARKSKYBLUE_BTN:
        return 3;
    case DARKRED_WALL: case DARKRED_BTN:
        return 4;
    case PINK_WALL: case PINK_BTN:
        return 13;
    case DARKYELLOW_WALL: case DARKYELLOW_BTN:
        return 6;
    case DARKGRAY_WALL: case DARKGRAY_BTN:
        return 8;
    case SKYBLUE_WALL: case SKYBLUE_BTN:
        return 11;

    case EMERGENCY_EXIT:
        return 2;
    case PRIME:
        return 6;
    case ERASER:
        return 15;
    case LIFE:
        return 4;
    case SPEED:
        return 7;
    case NORMAL_NPC: case ALCOHOL_NPC: case CHASING_NPC: case SHOOT_NPC_LEFT: case SHOOT_NPC_RIGHT: case SHOOT_NPC_UP: case SHOOT_NPC_DOWN:
        return 12;
    }
    return 0;
}



