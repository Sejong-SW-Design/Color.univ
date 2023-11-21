#include "manager.h"

double score[5] = { 4.5, 4.5, 4.5, 4.5, 4.5 };
int stage; //�߰��Կ� - ��
extern int gameMap1[22][37];
extern int gameMap2[22][37];
extern int gameMap3[22][37];
extern int gameMap4[22][37];

int keyControl() {
    if (_kbhit() != 0) {
        int key = _getch();
        switch (key)
        {
        case LEFT:
            return LEFT;
            break;
        case RIGHT:
            return RIGHT;
            break;
        case UP:
            return UP;
            break;
        case DOWN:
            return DOWN;
            break;
        case SPACEBAR:
            return SPACEBAR;
            break;

        case 112:
            drawPauseScreen();
            break;
        }
    }
}


/*
* main���� ȣ���Ұ���
* ��.. �𸣰ٴ�;
* 
*/
//int modeControl() {
//    
//}

void drawPauseScreen() {
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

            // ȭ�� �� ����� �ּ������Ұ���
            /*case SPACEBAR:
                return y - 12;
                */
            }
        }
    }
}


void setScore(int gradeidx, double s) {
    //�� ������ �غ����� ��� �ּ�ó������
	//if (score[gradeidx] >= 4.5) return;
	score[gradeidx] += s;

    //��� ���� �浹 Ȯ���ϰ��; �ӽ÷� �߰��߾�!!
    drawInfo(score, 1);
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