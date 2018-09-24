#include "Functions.h"

void SetColor(int text, int background)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConOut, background * 16 + text);
}

void setConsoleSize(int width, int height)
{
	HANDLE consol;
	consol = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(consol, TRUE, &r);
	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(consol, c);
}

void setCursoreAtPosition(int x, int y)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos = { x, y };
	SetConsoleCursorPosition(hConOut, pos);
}

void printAtCenterOfLine(int line, string text, Printer p, int consoleWidth)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = consoleWidth / 2 - text.length() / 2;
	position.Y = line;
	SetConsoleCursorPosition(hConOut, position);
	p.print(text);
}

void showConsoleCursor(bool showFlag)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConOut, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConOut, &cursorInfo);
}
