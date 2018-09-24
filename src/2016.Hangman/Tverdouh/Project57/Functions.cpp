#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

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


void clean()
{
	system("cls");
}

void printLogo()
{
	SetColor(0, 8);
	printInTheCentre("**    **    **    ***    **   ******   ***          ***    **    ***    **", 3, 80);
	SetColor(0, 8);
	printInTheCentre("**    **  **  **  ****   **  **    **  ****        ****  **  **  ****   **", 4, 80);
	SetColor(0, 8);
	printInTheCentre("**    ** **    ** ** **  ** **         ** **      ** ** **    ** ** **  **", 5, 80);
	SetColor(4, 8);
	printInTheCentre("******** ******** **  ** ** **     *** **  **    **  ** ******** **  ** **", 6, 80);
	SetColor(7, 8);
	printInTheCentre("**    ** **    ** **   **** **      ** **   **  **   ** **    ** **   ****", 7, 80);
	SetColor(7, 8);
	printInTheCentre("**    ** **    ** **    ***  **    **  **    ****    ** **    ** **    ***", 8, 80);
	SetColor(7, 8);
	printInTheCentre("**    ** **    ** **     **   ******   **     **     ** **    ** **     **", 9, 80);

}

void resetColour()
{
	HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConOut, 8);
}

HANDLE hConOut = GetStdHandle(STD_OUTPUT_HANDLE);

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

void showConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConOut, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hConOut, &cursorInfo);
}