#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__

#define GBOARD_ORIGIN_X 6
#define GBOARD_ORIGIN_Y 4

#define GBOARD_WIDTH 36
#define GBOARD_HEIGHT 21

/*
���� 0 ��ο� �Ķ� 1 ��ο� �ʷ� 2 ��ο� �ϴ� 3
��ο� ���� 4 ��ο� ���� 5 ��ο� ��� 6
ȸ�� 7 ��ο� ȸ�� 8 �Ķ� 9 �ʷ� 10
�ϴ� 11 ���� 12 ���� 13 ��� 14 ��� 15
*/

enum GAME_BOARD
{
    BLANK, //0
    NORMAL_WALL,//1 

    BLUE_WALL,//2
    RED_WALL,//3
    YELLOW_WALL,//4

    PURPLE_WALL,//5
    GREEN_WALL,//6
    ORANGE_WALL,//7
    //2�� ȥ�� (��+��=��, ��+��=û��) -> ����
    CYAN_WALL,//8	//û�ϻ�
    DARKBLUE_WALL,//9

    //item
    EMERGENCY_EXIT,//10
    PRIME,//11
    ERASER,//12

    //btn
    BLUE_BTN,//13
    RED_BTN,//14
    YELLOW_BTN,//15
    PURPLE_BTN,//16
    GREEN_BTN,//17
    ORANGE_BTN,//18
    CYAN_BTN,//19
    DARKBLUE_BTN,//20
};

using namespace std;

void drawGameBoard(int arr[][37]);

void updateGameBoard(int colorSort);

void removeWall();

void removeItem();

void drawStore();

void drawInfo(double score[], int grade); // score[0]�� ���

void drawBossLife();

void drawAttackdot(int dotNum);

void removeAttackDot();

void removeAttackTouchedWall();

void removeBossLife();

int randomEmergencyExit();

void drawGameResult();

void removeGameResult();

#endif

