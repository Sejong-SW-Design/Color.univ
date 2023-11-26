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
                drawGameBoard(gameMapHere, stage);      // �÷��̾ ��µǴµ� ������ ���� 

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
    printf("�� �� �� ��");

    setCurrentCursorPos(32, 16);
    printf("���� �г��� ����� �Ͻðڽ��ϱ�?");

    setCurrentCursorPos(32, 18);
    printf("����ȭ������ ���ư���");

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
                return y - 14;      // 0: �̾��ϱ�, 2:�����, 4: ���� ȭ��
            }
        }
    }

}


void setScore(int stage, double s) {
	if (score[stage] > 4.5 || score[stage] <= 0) return; 
    // 4.5���� npc �ε����� ������ �� �������淡 4.5 �ε�ȣ���� "="�� �����! -��
    // �ٵ� �ε�ȣ ���ϱ� ���� �Ծ 5.0 �ǳ�...? 
	score[stage] += s;
    if (score[stage] > 4.5) score[stage] = 4.5; // �׷��� �ӽù������� �̰� ���������! ���߿� ������� �����ּ��� -��
    //if (score[stage] < 0) score[stage] = 0; // �̰ŵ� �߰��߾�� �� �����԰� ��� �ε����� -1.0���� ����淡!!
    drawInfo(score, stage); 
}

//void drawStartScreen();
//
//void drawMenu();
//
void drawDevInfo() { // �ӽ�ȭ��
	setCurrentCursorPos(10, 10);
	std::cout << "[Developer Info]" << endl;

	setCurrentCursorPos(15, 11);
	std::cout << "������" << endl;

	setCurrentCursorPos(15, 13);
	std::cout << "����ȣ" << endl;

	setCurrentCursorPos(15, 14);
	std::cout << "������" << endl;

	setCurrentCursorPos(15, 15);
	std::cout << "������" << endl;

}
//
//void drawStageIntroInfo();
//
//void drawStageEnding();
//

// ��Ʈ �������� �͵� �־��ּ���~ -��

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

    int x = GBOARD_ORIGIN_X, y = GBOARD_ORIGIN_Y;   //���� �����ϴ� ���� ���� �� ������ ��ǥ
    for (int j = 0; j < 37; j++) {
        for (int i = 0; i < 22; i++) {
            setCurrentCursorPos(x + j * 2, y + i);
            if (gameResult[i][j] == 0) {
                setBackgroundColor(0, 0);
                printf("��");
            }

            else {
                setBackgroundColor(0, color);
                printf("��");
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