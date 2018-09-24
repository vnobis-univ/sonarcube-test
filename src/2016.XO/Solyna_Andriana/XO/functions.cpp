#include <string>
#include <iostream>
#include <windows.h>
#include <iomanip>

using namespace std;

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
void printInTheCentre(string str, int numberOfLine, int consoleWidth) // print in the centre of console
{
	HANDLE consol;
	consol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = consoleWidth/2 - str.length()/2;
	position.Y = numberOfLine;
	SetConsoleCursorPosition(consol, position);

	cout << str;
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

