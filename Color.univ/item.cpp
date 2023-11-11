#include "item.h"
#include "gameBoard.h"
#include <Windows.h>

Store myStore = { 0,0 };
int flag = 0; //����� �뷮 Ȯ��

void eraseColor() {

	myStore.color1 = 0;
	myStore.color2 = 0;
	updateStore(myStore.color1, myStore.color2); // ���Ӻ��� store ���� ������Ʈ  -����-
}

int checkStore() {
	if (flag != 0) return flag = 1; //���� �� ��� 
	else return flag = 0; 
}

void getColor(int colorNum, int posX, int posY, int gameMap[22][37]) {
	if (flag != 1) {
		if (myStore.color1 == 0) { //1�� ���������
			myStore.color1 = colorNum;
			//�������Լ�ȣ��(���� �� �� ������ ���� �ƴ� ����)
			removeWall(colorNum,posX,posY,gameMap);
			updateStore(myStore.color1, myStore.color2);// �̰� removeWall �Լ� �ϼ��Ǹ� ���ֱ�
		}
		else {
			myStore.color2 = colorNum;
			updateStore(myStore.color1, myStore.color2);
		}
	}
	else return;
}

void collaborateColor(int posX, int posY,int gameMap[22][37]) {//�����̽��� ������ ȣ���
	int mixColor=0; // �ӽ÷� �س����~ -����
	if (flag == 1) 
	{
		mixColor = myStore.color1 + myStore.color2;
	}
	//�������Լ�ȣ��

	removeWall(mixColor, posX, posY, gameMap);
	updateStore(mixColor, 0);
	
}



