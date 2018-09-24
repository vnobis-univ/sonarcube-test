#include "ForConsole.h"
#include "Printer.h"
#include <windows.h>
#include <string>

using namespace std;

HANDLE Screen = GetStdHandle(STD_OUTPUT_HANDLE);

int consoleWidth;
int consoleHeight;

void setConsoleSize()
{
	int _consoleWidth = 74;
	int _consoleHeight = 40;
	consoleWidth = _consoleWidth;
	consoleHeight = _consoleHeight;

	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = _consoleWidth - 1;
	r.Bottom = _consoleHeight - 1;
	SetConsoleWindowInfo(Screen, TRUE, &r);

	COORD c;
	c.X = _consoleWidth;
	c.Y = _consoleHeight;
	SetConsoleScreenBufferSize(Screen, c);
}

void setCursorPosition(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(Screen, pos);
}

void showCursor(bool yes_no)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(Screen, &cursorInfo);
	cursorInfo.bVisible = yes_no;
	SetConsoleCursorInfo(Screen, &cursorInfo);
}

void printAtLineCenter(int line, string text, Printer p)
{
	int textSize = text.size();
	int x_pos = (consoleWidth - textSize) / 2 + (consoleWidth - textSize) % 2;
	setCursorPosition(x_pos, line);
	p << text;
}