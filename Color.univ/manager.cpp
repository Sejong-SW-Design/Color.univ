#include "manager.h"
#include "gameBoard.h"

double score[5] = { 4.5, 4.5, 4.5, 4.5, 4.5 };

void setScore(int gradeidx, double s) {
	if (score[gradeidx] >= 4.5) return;
	score[gradeidx] += s;
}


//void drawStartScreen();
//
//void drawMenu();
//
void drawDevInfo() { // �ӽ�ȭ��
	setCurrentCursorPos(10, 10);
	std::cout << "[Developer Info]" << endl;

	setCurrentCursorPos(15, 11);
	std::cout << "������" << endl;

	setCurrentCursorPos(15, 13);
	std::cout << "����ȣ" << endl;

	setCurrentCursorPos(15, 14);
	std::cout << "������" << endl;

	setCurrentCursorPos(15, 15);
	std::cout << "������" << endl;

}
//
//void drawStageIntroInfo();
//
//void drawStageEnding();
//
//void drawGameOver();
//
//void drawGameInstruction();
//
//void drawIntro();
//
//void drawReturnToMain();

//void gameBoardInit() {
//
//}