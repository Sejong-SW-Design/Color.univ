#include "manager.h"

double score[5] = { 4.5, 4.5, 4.5, 4.5, 4.5 };

void setScore(int gradeidx, double s) {
	if (score[gradeidx] >= 4.5) return;
	score[gradeidx] += s;
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
    for (int i = 0; i < 20; i++) {
        printf(" ");
    }

    int origin_x1 = 20, origin_y1 = 27, h = 2, w = 2;
    for (int y = 0; y <= h; y++) {
        setCurrentCursorPos(origin_x1, origin_y1 + y);
        printf(" ");
    }
    for (int y = 0; y <= h; y++) {
        setCurrentCursorPos(origin_x1 + (w + 1) * 2, origin_y1 + y);
        printf(" ");
    }
    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1);
        printf(" ");
    }
    for (int x = 1; x < w + 1; x++) {
        setCurrentCursorPos(origin_x1 + x * 2, origin_y1 + h);
        printf(" ");
    }

    int origin_x2 = 28, origin_y2 = 27;
    for (int y = 0; y <= h; y++) {
        setCurrentCursorPos(origin_x2, origin_y2 + y);
        printf(" ");
    }
    for (int y = 0; y <= h; y++) {
        setCurrentCursorPos(origin_x2 + (w + 1) * 2, origin_y2 + y);
        printf(" ");
    }
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