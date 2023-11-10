#include "gameBoard.h"
#include "util.h"
//#include "move.h"
//#include "item.h"
#include <stdio.h>
#include <time.h>
#include <queue>

int Exit[5][2]; // 비상구 전역 변수 배열
int Exit_n = 0; // 비상구 수

void drawGameBoard(int arr[][37])
{
    double score[] = { 4.5,0,0,0,0 }; // util
    drawInfo(score, 1);

    // if(grade==4)
    drawBossLife();

    for (int i = 0; i < 22; i++)
    {
        setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y+i); // 위치
        for (int j = 0; j < 37; j++)
        {
            switch (arr[i][j])
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

void updateGameBoard(int colorSort) // 업데이트
{

}

void removeWall()
{

}

void removeItem()
{

}

void drawStore() // 아이템에서 정의
{

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
int randomEmergencyExit()//PC의 위치 받음(전역)
{
    srand((unsigned int)time(NULL));
    int num = rand() % Exit_n;
    //while(Exit[num]!=Pos Player)
}

*/
//void drawGameResult();

//void removeGameResult();