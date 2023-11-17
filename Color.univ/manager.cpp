#include "manager.h"

double score[5] = { 4.5, 4.5, 4.5, 4.5, 4.5 };
extern int gameMap1[22][37];
extern int gameMap2[22][37];
extern int gameMap3[22][37];


void setScore(int gradeidx, double s) {
    //나 실험좀 해보려고 잠시 주석처리했으
	//if (score[gradeidx] >= 4.5) return;
	score[gradeidx] += s;

    //언니 내가 충돌 확인하고싶어서 임시로 추가했어!!
    drawInfo(score, 1);
}

//void drawStartScreen();
//
//void drawMenu();
//
void drawDevInfo() { // 임시화면
	setCurrentCursorPos(10, 10);
	std::cout << "[Developer Info]" << endl;

	setCurrentCursorPos(15, 11);
	std::cout << "복민정" << endl;

	setCurrentCursorPos(15, 13);
	std::cout << "이지호" << endl;

	setCurrentCursorPos(15, 14);
	std::cout << "신지우" << endl;

	setCurrentCursorPos(15, 15);
	std::cout << "전지원" << endl;

}
//
//void drawStageIntroInfo();
//
//void drawStageEnding();
//
void drawResultScreen(int gameResult[22][37], int check) {
    setCurrentCursorPos(12, 28);
    printf("                                     ");

    int origin_x1 = 20, origin_y1 = 27, h = 2, w = 2;
    setCurrentCursorPos(origin_x1, origin_y1);
    printf("                           ");

    setCurrentCursorPos(origin_x1, origin_y1 + h);
    printf("       ");

    setCurrentCursorPos(origin_x1 + (w + 1) * 2, origin_y1);
    printf("                           ");


    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1);
        printf(" ");
    }
    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1 + h);
        printf(" ");
    }

    int origin_x2 = 28, origin_y2 = 27;
    setCurrentCursorPos(origin_x2, origin_y2);
    printf("                           ");

    setCurrentCursorPos(origin_x2, origin_y2 + h);
    printf("              ");

    setCurrentCursorPos(origin_x2 + (w + 1) * 2, origin_y2);
    printf("                           ");

    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2);
        printf(" ");
    }
    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x2 + x * 2, origin_y2 + h);
        printf(" ");
    }

    Sleep(10);

    int color = 0;
    if (check == 0) color = 4;      // game over 
    else color = 14;                // game clear

    int x = GBOARD_ORIGIN_X, y = GBOARD_ORIGIN_Y;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
    for (int j = 0; j < 37; j++) {
        for (int i = 0; i < 22; i++) {
            setCurrentCursorPos(x + j * 2, y + i);
            if (gameResult[i][j] == 0) {
                setBackgroundColor(0, 0);
                printf("■");
            }

            else {
                setBackgroundColor(0, color);
                printf("■");
            }
        }

        Sleep(30);
    }
}

//void drawGameInstruction();
//
//void drawIntro();
//
//void drawReturnToMain();

//void gameBoardInit() {
//
//}


void getStage(int gameMap[22][37], int stage)
{
    for (int i = 0; i < 22; i++)
        for (int j = 0; j < 37; j++)
        {
            if (stage == 1)
                gameMap[i][j] = gameMap1[i][j];
            else if (stage == 2)
                gameMap[i][j] = gameMap2[i][j];
            else if (stage == 3)
                gameMap[i][j] = gameMap3[i][j];
        }
}