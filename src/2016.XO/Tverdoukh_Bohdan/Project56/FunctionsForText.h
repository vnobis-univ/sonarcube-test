#pragma once
#include "View.h"
#include "FieldView.h"
void setCursorPosition(int xx, int yy)
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

void printInTheCentre(string str, int numberOfLine, int consoleWidth) // print in the centre of console
{
	HANDLE consol;
	consol = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = consoleWidth / 2 - str.length() / 2;
	position.Y = numberOfLine;
	SetConsoleCursorPosition(consol, position);

	cout << str;
}