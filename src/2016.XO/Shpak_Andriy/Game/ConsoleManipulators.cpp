#include <windows.h>

static HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

void setConsoleSize(int width, int height)
{
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

void getCursorPosition(int& x, int& y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	
	x = csbi.dwCursorPosition.X;
	y = csbi.dwCursorPosition.Y;
}

void setCursorState(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConOut, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(hConOut, &cursorInfo);
}

int getConsoleWidth()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getConsoleHeight()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}




