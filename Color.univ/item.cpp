#include "item.h"

Store myStore = { 0,0 };
// int flag = 0; //����� �뷮 Ȯ��

void eraseColor() {

	myStore.color1 = 0;
	myStore.color2 = 0;
	myStore.capacity = 0;		// �뷮 �ʱ�ȭ
	updateStore(myStore.color1, myStore.color2); // ���Ӻ��� store ���� ������Ʈ  -����-
}


void getColor(int colorNum, int posX, int posY, int gameMap[22][37]) {
	if (myStore.capacity < 2) {
		if (myStore.color1 == 0) { //1�� ���������
			myStore.color1 = colorNum;
			myStore.capacity++;
			//�������Լ�ȣ��(���� �� �� ������ ���� �ƴ� ����)
			// removeWall(colorNum,posX,posY,gameMap);
			updateStore(myStore.color1, myStore.color2);// �̰� removeWall �Լ� �ϼ��Ǹ� ���ֱ�
		}
		else {
			myStore.color2 = colorNum;
			myStore.capacity++;
			updateStore(myStore.color1, myStore.color2);
		}
	}
	else return;
}

void collaborateColor(int posX, int posY,int gameMap[22][37]) {//�����̽��� ������ ȣ���
	if (myStore.capacity < 2) return;

	int mixColor=0; // �ӽ÷� �س����~ -����
	if (myStore.capacity == 2) 
	{
		mixColor = myStore.color1 + myStore.color2;
	}
	//�������Լ�ȣ��

	// removeWall(mixColor, posX, posY, gameMap);
	updateStore(mixColor, 0);
	// updateGameBoard(gameMap);
}



