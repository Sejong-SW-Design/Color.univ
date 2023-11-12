#include "item.h"
#include "manager.h"

Store myStore = { 0,0 };
extern double score[5];

void eraseColor(int posX, int posY, int gameMap[22][37]) {

	gameMap[posY][posX] = 0;
	//setCurrentCursorPos(posX, posY); printf("  ");  -> 안해도 될 것 같음. -지원-

	myStore.color1 = 0;
	myStore.color2 = 0;
	myStore.capacity = 0;		// 용량 초기화
	updateStore(myStore.color1, myStore.color2); // 게임보드 store 색상 업데이트  -지원-
}


void getColor(int colorNum, int posX, int posY, int gameMap[22][37]) {

	//일단 벽 해제를 시도한다. 벽 해제에 사용되지 않은 건 store에 저장된다.
	bool didRemove = removeWall(colorNum - 11, posX, posY, gameMap);
	if (didRemove)
		return;
	
	if (myStore.capacity < 2) {
		if (myStore.color1 == 0) { //1이 비어있으면
			myStore.color1 = colorNum;
			myStore.capacity++;
			chageNumBTS(myStore.color1, myStore.color2);// 이거 removeWall 함수 완성되면 없애기
		}
		else {
			myStore.color2 = colorNum;
			myStore.capacity++;
			chageNumBTS(myStore.color1, myStore.color2);
		}
	}
	else return;
}

void collaborateColor(int posX, int posY,int gameMap[22][37]) {//스페이스바 누르면 호출됨
	if (myStore.capacity < 2) return;
	
	int mixColor = 0;
	if (myStore.capacity == 2) 
	{
		mixColor = myStore.color1 + myStore.color2;
	}

	///
	bool didRemove = removeWall(mixColor - 22, posX, posY, gameMap);
	if (didRemove) {
		//벽해제를 완료하면 스토어에서 지워야 함
		myStore.color1 = 0;
		myStore.color2 = 0;
		
		updateStore(myStore.color1, myStore.color2);

		return;
	}
	else return;
	//removeWall(mixColor, posX, posY, gameMap);
	//updateStore(mixColor, 0); -> 벽해제 안되면 그냥 색깔 냅두면 됨  
}

void chageNumBTS(int color1, int color2) {
	//btn enum으로 된 것을 콘솔 색으로 바꾸기
	switch (color1)
	{
	case BLUE_BTN:
		color1 = 9; break;
	case RED_BTN:
		color1 = 12; break;
	case YELLOW_BTN:
		color1 = 14; break;
	case PURPLE_BTN:
		color1 = 13; break;
	case GREEN_BTN:
		color1 = 10; break;
	case ORANGE_BTN:
		color1 = 6; break;
	case CYAN_BTN:
		color1 = 3; break;
	case DARKBLUE_BTN:
		color1 = 1; break;
	}

	switch (color2)
	{
	case BLUE_BTN:
		color2 = 9; break;
	case RED_BTN:
		color2 = 12; break;
	case YELLOW_BTN:
		color2 = 14; break;
	case PURPLE_BTN:
		color2 = 13; break;
	case GREEN_BTN:
		color2 = 10; break;
	case ORANGE_BTN:
		color2 = 6; break;
	case CYAN_BTN:
		color2 = 3; break;
	case DARKBLUE_BTN:
		color2 = 1; break;
	}
	updateStore(color1, color2);
}

void primeItemCollision(int posX, int posY, int gameMap[22][37]) {
	gameMap[posY][posX] = 0;
	setScore(1, 0.5);
	drawInfo(score, 1);
}