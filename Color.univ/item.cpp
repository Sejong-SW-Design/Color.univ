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

	//�ϴ� �� ������ �õ��Ѵ�. �� ������ ������ ���� �� store�� ����ȴ�.
	bool didRemove = removeWall(colorNum - 11, posX, posY, gameMap);
	if (didRemove)
		return;
	
	if (myStore.capacity < 2) {
		if (myStore.color1 == 0) { //1�� ���������
			myStore.color1 = colorNum;
			myStore.capacity++;
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
	
	int mixColor = 0;
	if (myStore.capacity == 2) 
	{
		mixColor = myStore.color1 + myStore.color2;
	}

	///
	bool didRemove = removeWall(mixColor - 22, posX, posY, gameMap);
	if (didRemove) {
		//�������� �Ϸ��ϸ� ������ ������ ��
		myStore.color1 = 0;
		myStore.color2 = 0;
		int x, y;
		int origin_x1 = 20, origin_y1 = 27, h = 2, w = 2;

		for (y = 1; y < h; y++)
		{
			for (x = 2; x <= w * 2; x++)
			{
				setCurrentCursorPos(origin_x1 + x, origin_y1 + y);
				if (myStore.color1 == 0) printf("  ");
				else
				{
					setBackgroundColor(0, myStore.color1);
					printf("��");
				}
			}
		}

		int origin_x2 = 28, origin_y2 = 27;

		for (y = 1; y < h; y++)
		{
			for (x = 2; x <= w * 2; x++)
			{
				setCurrentCursorPos(origin_x2 + x, origin_y2 + y);
				if (myStore.color2 == 0) printf("  ");
				else
				{
					setBackgroundColor(0, myStore.color2);
					printf("��");
				}
			}
		}
		return;
	}
	else return;
	//removeWall(mixColor, posX, posY, gameMap);
	//updateStore(mixColor, 0); -> ������ �ȵǸ� �׳� ���� ���θ� ��  
}