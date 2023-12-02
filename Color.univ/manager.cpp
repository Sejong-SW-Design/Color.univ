#include "manager.h"
#include <chrono>

double score[5] = { 4.5, 4.5, 4.5, 4.5, 4.5 };
int stage; 
extern int gameMap1[22][37];
extern int gameMap2[22][37];
extern int gameMap3[22][37];
extern int gameMap4[22][37];

extern int gameMapHere[22][37];

int pKeyPressed = 0;
double keyInterval = 0.15;

int keyControl() {
    static auto lastKeyPressTime = std::chrono::high_resolution_clock::now();

    // int flag = -1;
    if (_kbhit() != 0) {
        int key = _getch();

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedSeconds = currentTime - lastKeyPressTime;


        switch (key) {
        case 112:       // p: 112
            pKeyPressed = 1;
            return key;

        case LEFT:
        case RIGHT:
            if (pKeyPressed) break;
        case UP:
        case DOWN:
            if (elapsedSeconds.count() >= keyInterval) {
                lastKeyPressTime = currentTime;
                
                return key;
            }
            break;
        case SPACEBAR:
            pKeyPressed = 0;
            return key;
        }

        // return flag;
    }
}


int drawPauseScreen() {
    system("cls");
    setBackgroundColor(0, 12);

    setCurrentCursorPos(34, 12);
    printf("> ");

    setCurrentCursorPos(38, 12);
    printf("이 어 하 기");

    setCurrentCursorPos(38, 14);
    printf("게 임 오 버");


    while (1) {
        int x = 36;
        int y = 12;

        while (1) {
            int n = keyControl();
            switch (n) {
            case UP:
                if (y > 12) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y -= 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case DOWN:
                if (y < 14) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y += 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case SPACEBAR:
                setBackgroundColor(0, 15);
                return y - 12;      // 0: 이어하기, 2: 게임 오버
            }
        }
    }

}


void setScore(int stage, double s) {
	score[stage] += s;
    if (score[stage] >= 4.5) score[stage] = 4.5;
    if (score[stage] <= 0) score[stage] = 0;
    drawInfo(score, stage); 
}

int initGame() {
    // stage = 3;
    // drawStartScreen();
    // drawPrologue();
    int menu = drawMenu();
    if (menu == 0) return 0;        // 게임 시작
    else if (menu == 2) return 1;
    else if (menu == 4) return 2;  // todo
    else if (menu == 6) return 3;  // 게임 종료
}

//void drawStartScreen();
//

void drawPrologue() {
    printf("PROLOGUE \n");
    Sleep(1000);
}

int drawMenu() {
    // 0: 게임 시작, 1: 게임 방법, 2: 개발자 정보, 3: 나가기

    system("cls");

    setCurrentCursorPos(36, 9);
    setBackgroundColor(0, 10);
    printf("COLOR UNIV.");


    setBackgroundColor(0, 15);

    setCurrentCursorPos(32, 12);
    printf("> ");

    setCurrentCursorPos(36, 12);
    printf("[GAME START]");

    setCurrentCursorPos(36, 14);
    printf("[HOW TO PLAY]");

    setCurrentCursorPos(36, 16);
    printf("[DEVELOPER INFORMAION]");

    setCurrentCursorPos(36, 18);
    printf("[EXIT]");

    while (1) {
        int x = 34;
        int y = 12;

        while (1) {
            int n = keyControl();
            switch (n) {
            case UP:
                if (y > 12) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y -= 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case DOWN:
                if (y < 18) {
                    setCurrentCursorPos(x - 2, y);
                    printf(" ");
                    y += 2;
                    setCurrentCursorPos(x - 2, y);
                    printf(">");
                }
                break;

            case SPACEBAR:
                setBackgroundColor(0, 15);
                return y - 12;      // 0: game start, 2:how to play, 4: dev,  6: exit
            }
        }
    }
    
}

void drawDevInfo() { // 임시화면
    system("cls");
	setCurrentCursorPos(36, 10);
    setBackgroundColor(0, 10);
	std::cout << "[Developer Info]" << endl;

    setBackgroundColor(0, 15);
	setCurrentCursorPos(36, 12);
    std::cout << "22011191 전지원" << endl;

	setCurrentCursorPos(36, 14);
    std::cout << "22011819 복민정" << endl;

	setCurrentCursorPos(36, 16);
    std::cout << "22011824 이지호" << endl;

	setCurrentCursorPos(36, 18);
    std::cout << "22011839 신지우" << endl;


    setCurrentCursorPos(33, 23);
    printf("돌아가려면 아무키나 누르세요");


    while (1)
        if (_getch()) break;
}
//
//void drawStageIntroInfo();
//
//void drawStageEnding();
//

// 하트 지워지는 것도 넣어주세용~ -뤂

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

    int origin_x3 = 57, origin_y3 = 27, h3 = 2, w3 = 6;
    setCurrentCursorPos(50, 28);
    printf("                           ");

    setCurrentCursorPos(origin_x3, origin_y3);
    printf("                           ");

    setCurrentCursorPos(origin_x3, origin_y3 + h3);
    printf("                        ");

    setCurrentCursorPos(origin_x3 + (w3 + 1) * 2, origin_y3);
    printf("                           ");

    for (int x = 1; x < w3 + 1; x++) {
        setCurrentCursorPos(origin_x3 + x * 2, origin_y3);
        printf(" ");
    }
    for (int x = 1; x < w3 + 1; x++) {
        setCurrentCursorPos(origin_x3 + x * 2, origin_y3 + h3);
        printf(" ");
    }

    setCurrentCursorPos(59, 28);
    printf("           ");

    Sleep(10);

    int color = 0;
    if (check == 0) color = 4;      // game over 
    else color = 14;                // game clear

    if (check == 0) minusLife();

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



    Sleep(100);

    system("cls");
}

//void drawGameInstruction();
//
//void drawIntro();
//
//void drawReturnToMain();

//void gameBoardInit() {
//
//}


void getStage(int gameMap[22][37], int stage) {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 37; j++) {
            if (stage == 1)
                gameMap[i][j] = gameMap1[i][j];
            else if (stage == 2)
                gameMap[i][j] = gameMap2[i][j];
            else if (stage == 3)
                gameMap[i][j] = gameMap3[i][j];
            else if (stage == 4)
                gameMap[i][j] = gameMap4[i][j];
        }
    }
}

//스테이지별로 속도 조절이 필요할 것 같아서 만든 함수(이지호)
int getNpcSleepTime(int stage) {
    //각 맵별로 속도 조절 필요하면 더 해주세요!
    switch (stage)
    {
    case 1: return 150;
    case 2: return 150;
    case 3: return 300;
    case 4: return 150;
    }
    return 150;
}

void calculateAvgScore() {
    float sum = 0.0f;
    for (int i = 1; i <= stage; i++) {
        sum += score[i];
    }

    score[0] = sum / stage;
}