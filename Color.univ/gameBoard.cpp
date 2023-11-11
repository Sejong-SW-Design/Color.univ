#include "gameBoard.h"
#include "util.h"
#include "move.h"
#include "item.h"
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <queue>

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
    double score[] = { 4.5,0,0,0,0 }; // util
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

void removeWall(int num, int posX, int posY, int gameMap[22][37]) //같은 색 있으면 없애고, 아니면 return -> 미완!!
{
    gameMap[posY][posX] = 0; // 색 버튼 없앰

    /////
    int start = gameMap[posX][posY];

    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };


    std::queue<std::pair<int, int>> q;


    //erase 엄...
    updateGameBoard(gameMap);
}



void removeItem(int num, int posX, int posY, int gameMap[22][37]) // 미완성
{
    if (num == 11)//족보일 경우
    {
        //util 점수 계산
        gameMap[posY][posX] = 0;
    }
    else if (num == 12)//지우개일 경우
    {
        gameMap[posY][posX] = 0;
        eraseColor();
        // 이상한데 어디를 고쳐야할까... 
        // 문제 1. 되기는 함. 근데 player도 같이 사라졌다가 움직이면 다시 나타남.
        // 문제 2. 2개의 색이 저장소에 있었다가 erase하면 없어졌던
        // 마지막에 먹었던 색버튼 다시 생성됨... -> 지우 파트와 조정
    }

    updateGameBoard(gameMap);
}



void updateStore(int color1, int color2) // 새로 만듦 -> ppt에 추가해야함
{
    //btn enum으로 된 것을 콘솔 색으로 바꾼다!!
    //지우 collaborate 함수에서도 이거 적용해야함.
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



void drawInfo(double score[], int grade)
{
    setCurrentCursorPos(14, 1);
    printf("[%d 학년]", grade);

    setCurrentCursorPos(28, 1);
    printf("현재 학점 : %.1f", score[grade]);

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


