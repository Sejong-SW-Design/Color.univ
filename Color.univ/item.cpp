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

	//일단 벽 해제를 시도한다. 벽 해제에 사용되지 않은 건 store에 저장된다.
	bool didRemove = removeWall(colorNum - 11, posX, posY, gameMap);
	if (didRemove)
		return;
	
	if (myStore.capacity < 2) {
		if (myStore.color1 == 0) { //1이 비어있으면
			myStore.color1 = colorNum;
			myStore.capacity++;
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
					printf("■");
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
					printf("■");
				}
			}
		}
		return;
	}
	else return;
	//removeWall(mixColor, posX, posY, gameMap);
	//updateStore(mixColor, 0); -> 벽해제 안되면 그냥 색깔 냅두면 됨  
}