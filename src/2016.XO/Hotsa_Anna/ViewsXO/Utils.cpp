#include "Utils.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

int consoleWidth;
int consoleHeight;

void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;

	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &r);

	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConsole, c);
}

void moveCursorTo(int x, int y)
{
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(hConsole, position);
}

void showCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void printAtCenter(int lineNumber, string text, Printer p)
{
	int textSize = text.size();
	int xPosition = (consoleWidth - textSize) / 2 + (consoleWidth - textSize) % 2;
	moveCursorTo(xPosition, lineNumber);
	p << text ;
}

