#include "item.h"

Store myStore = { 0,0 };
int flag = 0; //����� �뷮 Ȯ��

void eraseColor() {
		
	myStore.color1 = 0;
	myStore.color2 = 0;
}

int checkStore() {
	if (flag != 0) return flag = 1; //���� �� ��� 
	else return flag = 0; 
}

void getColor(int colorNum) {
	if (flag != 1) {
		if (myStore.color1 == 0) { //1�� ���������
			myStore.color1 = colorNum;
			//�������Լ�ȣ��(���� �� �� ������ ���� �ƴ� ����)
		}
		else {
			myStore.color2 = colorNum;
		}
	}
	else return;
}
void collaborateColor() {//�����̽��� ������ ȣ���
	int mixColor;
	if (flag == 1) {
		mixColor = myStore.color1 + myStore.color2;
	}
	//�������Լ�ȣ��
}



