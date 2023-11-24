#include "item.h"
#include "manager.h"
#include "move.h"
#include "time.h"

Store myStore = { 0,0 };
extern double score[5];
extern int stage;
extern vector<int>Life; // 하트 배열 -> gameboard.cpp 참고 .뤂


void eraseColor(int posX, int posY, int gameMap[22][37]) {

	gameMap[posY][posX] = 0;

	myStore.color1 = 0;
	myStore.color2 = 0;
	myStore.capacity = 0;		// 용량 초기화
	updateStore(myStore.color1, myStore.color2); 
}


void getColor(int colorNum, int posX, int posY, int gameMap[22][37]) {
	
	if (myStore.capacity < 2) {
		
		gameMap[posY][posX] = BLANK;//일단 스토어가 비어있으면 스토어가 찼든 안찼든 blank 만들기  
		// 일단 벽 해제를 시도
		bool didRemove = removeWall(colorNum - 14, posX, posY, gameMap);
		if (didRemove)
			return;
		//벽 해제에 사용되지 않은 건 store에 저장
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
	setScore(stage, 0.5);
	drawInfoOriginal(score, stage);
}


Pos Move::getDrinkNextPos(int direction, Pos now, int alcoholNum) {
	Pos next = now;

	/*
	srand((unsigned int)time(NULL));
	int prev = alcoholNum;
	while (prev == alcoholNum)
	{
		alcoholNum = rand() % 3;
	}
	*/
	//int n = rand() % 23; 
	int n = alcoholNum;
	
	if (n == 0) {
		switch (direction){
		case LEFT: next.y += 1; break;
		case RIGHT: next.y -= 1; break;
		case UP: next.x -= 1; break;
		case DOWN: next.x += 1; break;
		}
	}
	else if (n == 1) {
		switch (direction){
		case LEFT: next.x += 1; break;
		case RIGHT: next.x -= 1; break;
		case UP: next.y += 1; break;
		case DOWN: next.y -= 1; break;
		}
	}
	else if (n == 2) {
		switch (direction){
		case LEFT: next.y -= 1; break;
		case RIGHT: next.y += 1; break;
		case UP: next.x += 1; break;
		case DOWN: next.x -= 1; break;
		}
	}
	else if (n == -1) {
		switch (direction)
		{
		case LEFT:
			next.x -= 1; break;
		case RIGHT:
			next.x += 1; break;
		case UP:
			next.y -= 1; break;
		case DOWN:
			next.y += 1; break;
		}
	}
	//updateAlcoholEffect(alcoholNum);

	/*
	else if (n == 3) {
		switch (direction){
		case LEFT: next.y += 1; break;
		case RIGHT: next.x -= 1; break;
		case UP: next.y -= 1; break;
		case DOWN: next.x += 1; break;
		}
	}
	else if (n == 4) {
		switch (direction){
		case LEFT: next.y += 1; break;
		case RIGHT: next.x += 1; break;
		case UP: next.y -= 1; break;
		case DOWN: next.x -= 1; break;
		}
	}
	else if (n == 5) {
		switch (direction){
		case LEFT: next.x += 1; break;
		case RIGHT: next.y += 1; break;
		case UP: next.y -= 1; break;
		case DOWN: next.x -= 1; break;
		}
	}
	else if (n == 6) {
		switch (direction){
		case LEFT: next.y -= 1; break;
		case RIGHT: next.x -= 1; break;
		case UP: next.x += 1; break;
		case DOWN: next.y += 1; break;
		}
	}
	else if (n == 7) {
		switch (direction){
		case LEFT: next.y += 1; break;
		case RIGHT: next.x -= 1; break;
		case UP: next.x += 1; break;
		case DOWN: next.y -= 1; break;
		}
	}
	else if (n == 8) {
		switch (direction){
		case LEFT: next.y += 1; break;
		case RIGHT: next.y -= 1; break;
		case UP: next.x += 1; break;
		case DOWN: next.x -= 1; break;
		}
	}
	else if (n == 9) {
		switch (direction){
		case LEFT: next.x -= 1; break;
		case RIGHT: next.y -= 1; break;
		case UP: next.x += 1; break;
		case DOWN: next.y += 1; break;
		}
	}
	else if (n == 10) {
		switch (direction){
		case LEFT: next.x -= 1; break;
		case RIGHT: next.y += 1; break;
		case UP: next.x += 1; break;
		case DOWN: next.y -= 1; break;
		}
	}
	else if (n == 11) {
		switch (direction){
		case LEFT: next.y -= 1; break;
		case RIGHT: next. x+= 1; break;
		case UP: next.y += 1; break;
		case DOWN: next.x -= 1; break;
		}
	}
	else if (n == 12) {
		switch (direction) {
		case LEFT: next.y -= 1; break;
		case RIGHT: next.x -= 1; break;
		case UP: next.y += 1; break;
		case DOWN: next.x += 1; break;
		}
	}
	else if (n == 13) {
		switch (direction) {
		case LEFT: next.x -= 1; break;
		case RIGHT: next.y -= 1; break;
		case UP: next.y += 1; break;
		case DOWN: next.x += 1; break;
		}
	}
	else if (n == 14) {
		switch (direction) {
		case LEFT: next.x -= 1; break;
		case RIGHT: next.x += 1; break;
		case UP: next.y += 1; break;
		case DOWN: next.y -= 1; break;
		}
	}
	else if (n == 15) {
		switch (direction) {
		case LEFT: next.x += 1; break;
		case RIGHT: next.y -= 1; break;
		case UP: next.y += 1; break;
		case DOWN: next.x -= 1; break;
		}
	}
	else if (n == 16) {
		switch (direction) {
		case LEFT: next.x -= 1; break;
		case RIGHT: next.x += 1; break;
		case UP: next.y -= 1; break;
		case DOWN: next.y += 1; break;
		}
	}
	else if (n == 17) {
		switch (direction) {
		case LEFT: next.y -= 1; break;
		case RIGHT: next.x += 1; break;
		case UP: next.x -= 1; break;
		case DOWN: next.y += 1; break;
		}
	}
	else if (n == 18) {
		switch (direction) {
		case LEFT: next.y -= 1; break;
		case RIGHT: next.y += 1; break;
		case UP: next.x -= 1; break;
		case DOWN: next.x += 1; break;
		}
	}
	else if (n == 19) {
		switch (direction) {
		case LEFT: next.y += 1; break;
		case RIGHT: next.x += 1; break;
		case UP: next.x -= 1; break;
		case DOWN: next.y -= 1; break;
		}
	}
	else if (n == 20) {
		switch (direction) {
		case LEFT: next.x += 1; break;
		case RIGHT: next.x -= 1; break;
		case UP: next.y -= 1; break;
		case DOWN: next.y += 1; break;
		}
	}
	else if (n == 21) {
		switch (direction) {
		case LEFT: next.x += 1; break;
		case RIGHT: next.y -= 1; break;
		case UP: next.x -= 1; break;
		case DOWN: next.y += 1; break;
		}
	}
	else if (n == 22) {
		switch (direction) {
		case LEFT: next.x += 1; break;
		case RIGHT: next.y += 1; break;
		case UP: next.x -= 1; break;
		case DOWN: next.y -= 1; break;
		}
	}
	*/

	return next;
}

void Move::updateAlcoholEffect(int alcoholNum) {
	
	/*
	time_t alcoholEffectTime, current;

	time(&alcoholEffectTime);

	while (1) {
		time(&current);

		if (difftime(current, alcoholEffectTime) >= 10) {
			alcoholNum = -1;
			//Sleep(10);
			//printf("%d", difftime(current, alcoholEffectTime));
			break;
		}
	}
	*/

	
	/*
	int alcoholEffectTime = (unsigned)time(NULL);
	
	alcoholEffectTime += 10;

	while (1) {
		int startTime = (unsigned)time(NULL);
		Sleep(10);
		if (alcoholEffectTime - startTime == 0) {
			alcoholNum = -1;
			break;
		}
	}
	*/
	
}

