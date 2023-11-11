#include "item.h"

Store myStore = { 0,0 };
// int flag = 0; //저장소 용량 확인

void eraseColor() {

	myStore.color1 = 0;
	myStore.color2 = 0;
	myStore.capacity = 0;		// 용량 초기화
	updateStore(myStore.color1, myStore.color2); // 게임보드 store 색상 업데이트  -지원-
}


void getColor(int colorNum, int posX, int posY, int gameMap[22][37]) {
	if (myStore.capacity < 2) {
		if (myStore.color1 == 0) { //1이 비어있으면
			myStore.color1 = colorNum;
			myStore.capacity++;
			//벽해제함수호출(같은 색 벽 있으면 해제 아님 말구)
			// removeWall(colorNum,posX,posY,gameMap);
			updateStore(myStore.color1, myStore.color2);// 이거 removeWall 함수 완성되면 없애기
		}
		else {
			myStore.color2 = colorNum;
			myStore.capacity++;
			updateStore(myStore.color1, myStore.color2);
		}
	}
	else return;
}

void collaborateColor(int posX, int posY,int gameMap[22][37]) {//스페이스바 누르면 호출됨
	if (myStore.capacity < 2) return;

	int mixColor=0; // 임시로 해놨어요~ -지원
	if (myStore.capacity == 2) 
	{
		mixColor = myStore.color1 + myStore.color2;
	}
	//벽해제함수호출

	// removeWall(mixColor, posX, posY, gameMap);
	updateStore(mixColor, 0);
	// updateGameBoard(gameMap);
}



