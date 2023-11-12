#include "util.h"

void setConsoleSize() {
	// con cols: 가로, lines: 세로
	system("mode con cols=100 lines=35 | title Color.univ");
}

void removeCursor() {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

COORD getCurrentCursorPos() {
	COORD cursor;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	cursor.X = curInfo.dwCursorPosition.X;
	cursor.Y = curInfo.dwCursorPosition.Y;

	return cursor;
}

void setCurrentCursorPos(int x, int y) {
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void setBackgroundColor(int backColor, int textColor) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}

// void setBGM(int sort, int playFlag);
