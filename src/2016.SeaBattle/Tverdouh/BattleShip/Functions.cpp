#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "FunctionsForGame.h"

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

void setCursor(int xx, int yy)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;
	cursor.X = xx;
	cursor.Y = yy;
	SetConsoleCursorPosition(hConsole, cursor);
}

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void printInTheCentre(string str, int numberOfLine, int consoleWidt)
{
	HANDLE consol;
	consol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = consoleWidt / 2 - str.length() / 2;
	position.Y = numberOfLine;
	SetConsoleCursorPosition(consol, position);

	cout << str;
}

void showConsoleCursor(bool showFlag)
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConOut, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConOut, &cursorInfo);
}


void clean()
{
	system("cls");
}


