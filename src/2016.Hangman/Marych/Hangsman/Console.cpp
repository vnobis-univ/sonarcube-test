#include "Console.h"
#include "Printer.h"
#include <Windows.h>
#include <string>

using namespace std;

HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

int consoleWidth;
int consoleHeight;

string language;

void setLangToEng()
{
	setlocale(LC_ALL, "English");
	language = "Eng";
}
void setLangToUkr()
{
	setlocale(LC_ALL, "Ukrainian");
	language = "Ukr";
}
void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;

	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(hConOut, TRUE, &r);

	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hConOut, c);
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
void printAtCenterOfLineCh(int line, char text, Printer p)
{
	int x_pos = consoleWidth / 2;

	setCursoreAtPosition(x_pos, line);
	p.print(text);
}

