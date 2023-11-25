#include "gameBoard.h"
#include "move.h"
#include "item.h"

//���� ��� �� �ؿ� �־��

vector<pair<int, int>>Exits; //��� �迭
//vector<int>Life;
extern double score[5];
extern int stage;
 

Pos setPcInitPos(int stage) //(���Ӻ��� ����! ���ϱ� 2 �̵��� ���ص���)
{
    switch (stage)
    {
    case 1:
        return { 18,0 };
    case 2: case 3:
        return  { 1,10 };
    case 4:
        return { 1,10 }; //  �ӽ�
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
        //C.push_back(new ChasingNpc({ 5, 17 })); //  ���� �糪���� �ּ�
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
//���Ӻ��� x y ��ǥ �������� �޴´�!!
void drawOnePoint(int gameMap[22][37], int i, int j, int backGround)
{
    int flag = 0; // ��� ������!
    Pos cursorPosition = Move::getCursorPos({j, i});
    setCurrentCursorPos(cursorPosition.x, cursorPosition.y);
    switch (gameMap[i][j])
    {
    case NORMAL_WALL:
        if (stage == 4) setBackgroundColor(backGround, 8); // ��ο� ȸ��
        else setBackgroundColor(backGround, 7); // �׳� ȸ��
        printf("��"); break;
    case BLANK:
        setBackgroundColor(backGround, backGround); printf("��"); break;
    case GOAL:
        setBackgroundColor(backGround, backGround); printf("��"); break;
    case BLUE_WALL:
        setBackgroundColor(backGround, 9); printf("��"); break;
    case RED_WALL:
        setBackgroundColor(backGround, 12); printf("��");  break;
    case YELLOW_WALL:
        setBackgroundColor(backGround, 14); printf("��");  break;
    case PURPLE_WALL:
        setBackgroundColor(backGround, 5); printf("��");  break;
    case GREEN_WALL:
        setBackgroundColor(backGround, 10); printf("��"); break;
    case ORANGE_WALL:
        setBackgroundColor(backGround, 6); printf("��");  break;
    case DARKBLUE_WALL:
        setBackgroundColor(backGround, 1); printf("��");  break;
    case DARKGREEN_WALL:
        setBackgroundColor(backGround, 2); printf("��");  break;
    case DARKSKYBLUE_WALL:
        setBackgroundColor(backGround, 3); printf("��");  break;
    case DARKRED_WALL:
        setBackgroundColor(backGround, 4); printf("��");  break;
    case PINK_WALL:
        setBackgroundColor(backGround, 13); printf("��");  break;
    case DARKYELLOW_WALL:
        setBackgroundColor(backGround, 6); printf("��");  break;
    case DARKGRAY_WALL:
        setBackgroundColor(backGround, 8); printf("��");  break;
    case SKYBLUE_WALL:
        setBackgroundColor(backGround, 11); printf("��");  break;

    case BLUE_BTN:
        setBackgroundColor(backGround, 9); printf("��"); break;
    case RED_BTN:
        setBackgroundColor(backGround, 12); printf("��"); break;
    case YELLOW_BTN:
        setBackgroundColor(backGround, 14); printf("��"); break;
    case PURPLE_BTN:
        setBackgroundColor(backGround, 5); printf("��");  break;
    case GREEN_BTN:
        setBackgroundColor(backGround, 10); printf("��"); break;
    case ORANGE_BTN:
        setBackgroundColor(backGround, 6); printf("��");  break;
    case DARKBLUE_BTN:
        setBackgroundColor(backGround, 1); printf("��"); break;
    case DARKGREEN_BTN:
        setBackgroundColor(backGround, 2); printf("��");  break;
    case DARKSKYBLUE_BTN:
        setBackgroundColor(backGround, 3); printf("��");  break;
    case DARKRED_BTN:
        setBackgroundColor(backGround, 4); printf("��");  break;
    case PINK_BTN:
        setBackgroundColor(backGround, 13); printf("��");  break;
    case DARKYELLOW_BTN:
        setBackgroundColor(backGround, 6); printf("��");  break;
    case DARKGRAY_BTN:
        setBackgroundColor(backGround, 8); printf("��");  break;
    case SKYBLUE_BTN:
        setBackgroundColor(backGround, 11); printf("��");  break;

    case EMERGENCY_EXIT:
        setBackgroundColor(backGround, 2); printf("��");
        for (int k = 0; k < Exits.size(); k++) // �̰� ���ؼ� ��� �̻�����
        {
            if (Exits[k].first == i && Exits[k].second == j) //���� ���� �ִٸ�
            {
                flag = 1;
            }
        }
        if(flag==0) Exits.push_back(make_pair(i, j));
        break;
    case PRIME:
        setBackgroundColor(backGround, 6); printf("��"); break;
    case ERASER:
        setBackgroundColor(backGround, 15); printf("��"); break;
    case LIFE:
        setBackgroundColor(backGround, 4); printf("��"); break; // npc�� �򰥸���� ��ũ ���� ���
    case SPEED:
        setBackgroundColor(backGround, 7); printf("��"); break; // eraser�� �򰥸����
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
    updateAlcoholTime(0); // ���ڿ� ó���� X
    // updateAlcoholTime(10); // ���ڿ� ����

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
}


//�� ���� �ִϸ��̼� ������ �ӽ÷� ���������(����ȣ)
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

bool removeWall(int colorSort, int posX, int posY, int gameMap[22][37]) //���� �� ������ ���ְ�, �ƴϸ� return -> �̿�!!
{
    vector<Pos>ErasePos;
    int filter[8][2] = { {0,1},{1,0},{0,-1},{-1,0},{1,1},{-1,1},{1,-1},{-1,-1} };
    queue<pair<int, int>> q;
    bool visited[22][37] = { 0 };

    //�� ���� �ִϸ��̼� ����
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

    //���� ������ ��츸 �ִϸ��̼�
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

void updateStore(int color1, int color2) // ���� ���� -> ppt�� �߰��ؾ���
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




void drawLifeEdge() // ��Ʈ �׵θ� + �ʱ� ��Ʈ ����
{
    int x, y, h = 2, w = 6;

    int origin_x = 57, origin_y = 27;
    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x, origin_y + y);
        if (y == h)
            printf("��");
        else if (y == 0)
            printf("��");
        else
            printf("��");
    }

    for (y = 0; y <= h; y++)
    {
        setCurrentCursorPos(origin_x + (w + 1) * 2, origin_y + y);
        if (y == h)
            printf("��");
        else if (y == 0)
            printf("��");
        else
            printf("��");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x + x * 2, origin_y);
        printf("��");
    }

    for (x = 1; x < w + 1; x++)
    {
        setCurrentCursorPos(origin_x + x * 2, origin_y + h);
        printf("��");
    }

    setCurrentCursorPos(50, 28);
    printf("[life]");

    
    origin_x = 59, origin_y = 28;
    for (x = 0; x < 3; x++)
    {
        setCurrentCursorPos(origin_x + (x * 3) + 2, origin_y);
        setBackgroundColor(0, 4); // ��ο� ����
        printf("��");

        //Life.push_back(1);
        
        // ��Ʈ 1,2,3 ��� 
        // 1 -> ��Ʈ �ִ�. 0 -> ��Ʈ ����
    }
    
}



/*
void updateLife() // ��Ʈ ������Ʈ
{   
    
    int x;
    int origin_x = 59, origin_y = 28;
    for (x = 0; x < 3; x++)
    {
        if (Life.at(x) == 1) // ��Ʈ�� �ִٸ�
        {
            setCurrentCursorPos(origin_x + (x * 3) + 2, origin_y);
            setBackgroundColor(0, 4); // ��ο� ����
            printf("��");
        }
    }
    
}
*/
// ��Ʈ �پ��� ��, �þ�� �� �����ۿ��� ����!! -> �������ó��
//�� �κ��� ���ְ� �����ۿ��� �ҰԿ� - ����



void drawInfo(double *score, int stage)
{
    setCurrentCursorPos(14, 1); 
    printf("[%d �г�]", stage);

    setCurrentCursorPos(34, 1);
    printf("���� ���� : %.1f", score[stage]);

    setCurrentCursorPos(60, 1);
    printf("��� ���� : %.1f", score[0]);
}

void drawInfoOriginal(double* score, int stage)
{
    setBackgroundColor(0, 15); // �Ͼ��
    drawInfo(score, stage);
}

void drawInfoMinus(double* score, int stage)
{
    setBackgroundColor(0, 12); // ������
    drawInfo(score, stage);

    Sleep(150);
    drawInfoOriginal(score, stage);
}

void drawInfoPlus(double* score, int stage)
{
    setBackgroundColor(0, 9); // �Ķ���
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
        printf("��");
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

pair<int, int> randomEmergencyExit(int posX, int posY, int gameMap[22][37]) // ������ �迭 return
{
    /*
    srand((unsigned int)time(NULL));
    
    int idx = rand() % (Exits.size()); // ���� ��� idx


    while (Exits[idx].first == posY && Exits[idx].second == posX) //����� ���� ��ġ�� ������ �ȵȴ�.
    {     
        idx = rand() % (Exits.size());
    }

    return Exits[idx];
    */

    int currIdx=0; 

    for (int i = 0; i < Exits.size(); i++) // ������� �� ���� �� ��������
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
    printf("[  %d �г�  ]",stage);


    setBackgroundColor(0, 15);
    setCurrentCursorPos(33, 13);
    printf("���� ���� : %.1f  %s", score[stage],calculate(score[stage]).c_str());


    setCurrentCursorPos(33, 15);
    printf("��� ���� : %.1f", score[0]);

    if (score[stage] == 0) // gameover�� ��
    {
        setCurrentCursorPos(35, 18);
        setBackgroundColor(0, 7);
        printf("�����Դϴ�.");
    }
    else if (stage == 1)
    {
        setCurrentCursorPos(30, 18);
        setBackgroundColor(0, 7);
        printf("2�г⿡�� ���� �����մϴ�");
    }
    else if (stage == 2)
    {
        setCurrentCursorPos(27, 18);
        setBackgroundColor(0, 7);
        printf("���� 3�г��̶��..�ð� �� ������");
    }
    else if (stage == 3)
    {
        setCurrentCursorPos(33,18);
        setBackgroundColor(0, 7);
        printf("�� �̷��� �����...?");

        setCurrentCursorPos(34, 19);
        setBackgroundColor(0, 7);
        printf("�� �̷��ΰ�...?");
    }
    else if (stage == 4)
    {
        setCurrentCursorPos(37, 18);
        setBackgroundColor(0, 7);
        printf("�������");
    }


    Sleep(2500);

}

string calculate(double score) // ���� ���
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



