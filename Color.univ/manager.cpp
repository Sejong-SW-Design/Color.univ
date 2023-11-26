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
double keyInterval = 0.2;

int keyControl() {
    static auto lastKeyPressTime = std::chrono::high_resolution_clock::now();

    int flag = -1;
    if (_kbhit() != 0) {
        int key = _getch();

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedSeconds = currentTime - lastKeyPressTime;


        switch (key) {
        case 112:       // p: 112
            pKeyPressed = 1;

            flag = drawPauseScreen();
            if (flag == 0) {
                system("cls");
                drawGameBoard(gameMapHere, stage);      // 플레이어가 출력되는데 딜레이 생김 

                pKeyPressed = 0;
            }
            break;

        case LEFT:
        case RIGHT:
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

        return flag;
    }
}


int drawPauseScreen() {
    system("cls");

    setBackgroundColor(0, 12);

    setCurrentCursorPos(30, 14);
    printf("> ");

    setCurrentCursorPos(32, 14);
    printf("이 어 하 기");

    setCurrentCursorPos(32, 16);
    printf("현재 학년을 재수강 하시겠습니까?");

    setCurrentCursorPos(32, 18);
    printf("메인화면으로 돌아가기");

    while (1) {
        int x = 32;
        int y = 14;

        while (1) {
            int n = keyControl();
            switch (n) {
            case UP:
                if (y > 14) {
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
                if (y - 14 != 0) break;
                setBackgroundColor(0, 15);
                return y - 14;      // 0: 이어하기, 2:재수강, 4: 메인 화면
            }
        }
    }

}


void setScore(int stage, double s) {
	if (score[stage] > 4.5 || score[stage] <= 0) return; 
    // 4.5에서 npc 부딪혀도 점수가 안 내려가길래 4.5 부등호에서 "="만 뺐어요! -뤂
    // 근데 부등호 빼니까 족보 먹어서 5.0 되네...? 
	score[stage] += s;
    if (score[stage] > 4.5) score[stage] = 4.5; // 그래서 임시방편으로 이거 만들어놨어요! 나중에 마음대로 고쳐주세용 -뤂
    //if (score[stage] < 0) score[stage] = 0; // 이거도 추가했어요 뤂 족보먹고 계속 부딪히면 -1.0점이 생기길래!!
    drawInfo(score, stage); 
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
            else if (stage == 4)
                gameMap[i][j] = gameMap4[i][j];
        }
}