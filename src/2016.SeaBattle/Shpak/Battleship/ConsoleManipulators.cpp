#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include "ConsoleManipulators.h"

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

void setDefaultFontProperties()
{
	CONSOLE_FONT_INFOEX cfi;
	
	cfi.cbSize = 84;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 0x0C;
	cfi.nFont = 6;
	cfi.FontFamily = 48;
	cfi.FontWeight = 400;

	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
}

void setFontSize(int x, int y)
{
	CONSOLE_FONT_INFOEX cfi;

	cfi.cbSize = 84;
	cfi.dwFontSize.X = x;
	cfi.dwFontSize.Y = y;
	cfi.nFont = 6;
	cfi.FontFamily = 48;
	cfi.FontWeight = 400;

	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), false, &cfi);
}

void setCursoreAtPosition(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(hConOut, pos);
}

void moveCursor(short x, short y)
{
	COORD current;
	getCursorPosition(current);

	current = {current.X + x, current.Y + y};

	setCursoreAtPosition(current);
}

void setCursoreAtPosition(COORD coord)
{
	SetConsoleCursorPosition(hConOut, coord);
}

void getCursorPosition(COORD& coord)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	
	coord.X = csbi.dwCursorPosition.X;
	coord.Y = csbi.dwCursorPosition.Y;
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

bool checkIfKeyPressed()
{
	if (_kbhit())
	{
		if (_getch() == 224)
			_getch();

		return true;
	}
	return false;
}

bool checkIfArrowPressed()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD NumInputs = 0;
	DWORD InputsRead = 0;
	bool running = true;

	INPUT_RECORD irInput;

	GetNumberOfConsoleInputEvents(hInput, &NumInputs);

	ReadConsoleInput(hInput, &irInput, 1, &InputsRead);

	switch (irInput.Event.KeyEvent.wVirtualKeyCode)
	{
	case VK_LEFT:
	case VK_UP:
	case VK_RIGHT:
	case VK_DOWN:
		return true;
	}

	return false;
}

void coolConsoleStuff()
{
	SetConsoleTitle("Hangman");

	setCursorState(false);

	setConsoleSize(80, 50);

	setDefaultFontProperties();
}

