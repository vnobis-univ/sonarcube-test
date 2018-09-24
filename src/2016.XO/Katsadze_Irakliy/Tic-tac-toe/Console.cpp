#include <Windows.h>
#include <string>
#include "Printer.h"
#define _CRT_SECURE_NO_WARNINGS wcsncpy_s

using namespace std;

HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
int consoleWidth;
int consoleHeight;

void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Bottom = height - 1;
	rect.Right = width - 1;
	SetConsoleWindowInfo(hconsole, TRUE, &rect);
	COORD coord;
	coord.X = width;
	coord.Y = height;
	SetConsoleScreenBufferSize(hconsole, coord);
}

void setCursor(short x, short y)
{
	COORD coord = { x, y };
	SetConsoleCursorPosition(hconsole, coord);
}

void printInCenter(int line, string text, Printer p)
{
	int size = text.size();
	int x = (consoleWidth - size) / 2 + (consoleHeight - size) % 2;
	setCursor(x, line);
	p << text;
}

void showCursor(bool val)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hconsole, &info);
	info.bVisible = val;
	SetConsoleCursorInfo(hconsole, &info);
}

string changeFontSize(string tex, short size)
{
	CONSOLE_FONT_INFOEX info;
	GetCurrentConsoleFontEx(hconsole, TRUE, &info);
	short temp = info.dwFontSize.X;
	info.dwFontSize.X = size;
	SetCurrentConsoleFontEx(hconsole, TRUE, &info);
	return tex;
}
