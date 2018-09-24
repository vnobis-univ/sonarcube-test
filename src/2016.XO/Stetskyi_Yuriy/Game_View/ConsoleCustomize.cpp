#pragma once

#include "ConsoleCustomize.h"

using namespace std;

void setConsoleProperties()
{
	
	// making cursor invisible
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	// making edges immutable
	HMENU hm = GetSystemMenu(hwnd, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(hwnd);


	// configuring buffer and window size
	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = CONSOLE_WIDTH - 1;
	r.Bottom = CONSOLE_HEIGHT - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &r);

	_COORD c;
	c.X = CONSOLE_WIDTH;
	c.Y = CONSOLE_HEIGHT;
	SetConsoleScreenBufferSize(hConsole, c);
	 
}

void setCursorAt(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void printAtCenter(string st, const Printer& p)
{
	int size = st.size();
	int x_pos = (CONSOLE_WIDTH - size) / 2 + (CONSOLE_WIDTH - size) % 2;
	setCursorAt(x_pos, cursor.Y);
	p.print(st);
}
