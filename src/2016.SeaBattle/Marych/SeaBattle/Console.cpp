#include "Console.h"
#include "Printer.h"
#include <windows.h>
#include <string>

using namespace std;

HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

int consoleWidth;
int consoleHeight;

void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;

	COORD maxWindow = { width, height }; // our size
	SMALL_RECT srctWindow = { 0, 0, maxWindow.X - 1, maxWindow.Y - 1 };
	SMALL_RECT minWindow = { 0, 0, 0, 0 };
	SetConsoleWindowInfo(hConOut, true, &minWindow);
	SetConsoleScreenBufferSize(hConOut, maxWindow);
	SetConsoleWindowInfo(hConOut, true, &srctWindow);
}

void setCursoreAtPosition(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConOut, pos);
}

void showConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConOut, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConOut, &cursorInfo);
}

void printAtCenterOfLine(int line, string text, Printer p)
{
	int textSize = text.size();
	int x_pos = (consoleWidth - textSize) / 2 + (consoleWidth - textSize) % 2;

	setCursoreAtPosition(x_pos, line);
	p << text;
}