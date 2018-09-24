#include "functions.h"

HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setConsoleSize(int width, int height)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = width - 1;
	r.Bottom = height - 1;
	SetConsoleWindowInfo(consol, TRUE, &r);
	COORD c;
	c.X = width;
	c.Y = height;
	SetConsoleScreenBufferSize(consol, c);
*/

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

void setCursoreAtPosition(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConOut, pos);
}

void printAtCenterOfLine(int line, string text, Printer p, int consoleWidth)
{
	HANDLE consol;
	consol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = consoleWidth / 2 - text.length() / 2;
	position.Y = line;
	SetConsoleCursorPosition(consol, position);
	p.print(text);
}

void showConsoleCursor(bool showFlag) //can hide cursor
{
	HANDLE consol;
	consol = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(consol, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(consol, &cursorInfo);
}

void setConsoleToLucidaConsole()
{
	COORD dwFontSize;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info{ sizeof(CONSOLE_FONT_INFOEX) };
	if (!GetCurrentConsoleFontEx(output, false, &info))
		return;
	dwFontSize.X = 10;
	dwFontSize.Y = 16;
	info.FontFamily = FF_DONTCARE;
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Lucida Console");
	info.dwFontSize = dwFontSize;
	SetCurrentConsoleFontEx(output, false, &info);
}