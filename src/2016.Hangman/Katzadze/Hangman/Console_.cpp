#include "Console_.h"

int consoleWidth;
int consoleHeight;

void setConsoleSize(int width, int height)
{
	consoleWidth = width;
	consoleHeight = height;
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Bottom = height - 1;
	r.Right = width - 1;
	SetConsoleWindowInfo(hconsole, TRUE, &r);
	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(hconsole, c);
}

void setCursor(short x, short y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(hconsole, c);
}

void printInCenter(int line, string text, Printer p)
{
	int size = text.size();
	int x = (consoleWidth - size) / 2 + (consoleWidth - size) % 2;
	setCursor(x, line);
	p << text;
}

void showCursor(bool sth)
{
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hconsole, &info);
	info.bVisible = sth;
	SetConsoleCursorInfo(hconsole, &info);
}

void enableUkrainianLang()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}