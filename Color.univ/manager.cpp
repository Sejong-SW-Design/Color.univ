#include "manager.h"

double score[5] = { 4.5, 0.0, 0.0, 0.0, 0.0 };

//void setScore();
//
//void drawStartScreen();
//
//void drawMenu();
//
void drawDevInfo() { // 임시화면
	setCurrentCursorPos(10, 10);
	std::cout << "[Developer Info]" << endl;

	setCurrentCursorPos(15, 11);
	std::cout << "복민정" << endl;

	setCurrentCursorPos(15, 13);
	std::cout << "이지호" << endl;

	setCurrentCursorPos(15, 14);
	std::cout << "신지우" << endl;

	setCurrentCursorPos(15, 15);
	std::cout << "전지원" << endl;

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
