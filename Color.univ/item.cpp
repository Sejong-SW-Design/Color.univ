#include "item.h"

Store myStore = { 0,0 };
int flag = 0; //저장소 용량 확인

void eraseColor() {
		
	myStore.color1 = 0;
	myStore.color2 = 0;
}

int checkStore() {
	if (flag != 0) return flag = 1; //가득 찬 경우 
	else return flag = 0; 
}

void getColor(int colorNum) {
	if (flag != 1) {
		if (myStore.color1 == 0) { //1이 비어있으면
			myStore.color1 = colorNum;
			//벽해제함수호출(같은 색 벽 있으면 해제 아님 말구)
		}
		else {
			myStore.color2 = colorNum;
		}
	}
	else return;
}
void collaborateColor() {//스페이스바 누르면 호출됨
	int mixColor;
	if (flag == 1) {
		mixColor = myStore.color1 + myStore.color2;
	}
	//벽해제함수호출
}



