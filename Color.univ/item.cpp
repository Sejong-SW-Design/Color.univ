#include "item.h"
#include "manager.h"

Store myStore = { 0,0 };
extern double score[5];

void eraseColor(int posX, int posY, int gameMap[22][37]) {

	gameMap[posY][posX] = 0;

	myStore.color1 = 0;
	myStore.color2 = 0;
	myStore.capacity = 0;		// 용량 초기화
	updateStore(myStore.color1, myStore.color2); // 게임보드 store 색상 업데이트  -지원-
}


void getColor(int colorNum, int posX, int posY, int gameMap[22][37]) {

	//일단 벽 해제를 시도한다. 벽 해제에 사용되지 않은 건 store에 저장된다.
	bool didRemove = removeWall(colorNum - 14, posX, posY, gameMap);
	if (didRemove)
		return;
	
	if (myStore.capacity < 2) {
		if (myStore.color1 == 0) { //1이 비어있으면
			myStore.color1 = colorNum;
			myStore.capacity++;
			chageNumBTS(myStore.color1, myStore.color2);
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

	bool didRemove = removeWall(mixColor - 28, posX, posY, gameMap);
	if (didRemove) {
		//벽해제를 완료하면 스토어에서 지워야 함
		myStore.color1 = 0;
		myStore.color2 = 0;
		myStore.capacity = 0;
		
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
		color1 = 5; break;
	case GREEN_BTN:
		color1 = 10; break;
	case ORANGE_BTN:
		color1 = 6; break;
	case DARKBLUE_BTN:
		color1 = 1; break;
	case DARKGREEN_BTN:
		color1 = 2; break;
	case DARKSKYBLUE_BTN:
		color1 = 3; break;
	case DARKRED_BTN:
		color1 = 4; break;
	case PINK_BTN:
		color1 = 13; break;
	case DARKYELLOW_BTN:
		color1 = 6; break;
	case DARKGRAY_BTN:
		color1 = 8; break;
	case SKYBLUE_BTN:
		color1 = 11; break;
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
		color2 = 5; break;
	case GREEN_BTN:
		color2 = 10; break;
	case ORANGE_BTN:
		color2 = 6; break;
	case DARKBLUE_BTN:
		color2 = 1; break;
	case DARKGREEN_BTN:
		color2 = 2; break;
	case DARKSKYBLUE_BTN:
		color2 = 3; break;
	case DARKRED_BTN:
		color2 = 4; break;
	case PINK_BTN:
		color2 = 13; break;
	case DARKYELLOW_BTN:
		color2 = 6; break;
	case DARKGRAY_BTN:
		color2 = 8; break;
	case SKYBLUE_BTN:
		color2 = 11; break;
	}
	updateStore(color1, color2);
}

void primeItemCollision(int posX, int posY, int gameMap[22][37]) {
	gameMap[posY][posX] = 0;
	setScore(1, 0.5);
	drawInfo(score, 1);
}