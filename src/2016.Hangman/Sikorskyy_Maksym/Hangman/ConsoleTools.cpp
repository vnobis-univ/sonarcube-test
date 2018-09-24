#pragma once
#include "ConsoleTools.h"
#include <conio.h>
#include <iostream>
#include "Buttons.h"
#include "Dictionary.h"
#include "Translating.h"

#include <iostream>
using namespace std;

int width;
int height;

COORD cursor;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_FONT_INFOEX font;

HWND handle = FindWindow("ConsoleWindowClass", NULL);
HDC dc = GetDC(handle);
RECT r;

HPEN penOrange = CreatePen(PS_SOLID, 1, RGB(200, 140, 111));
HPEN penBlue = CreatePen(PS_SOLID, 1, RGB(100, 60, 150));
HPEN penBlack = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
HPEN penPink = CreatePen(PS_SOLID, 1, RGB(255, 0, 127));


HBRUSH brushBlack = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH brushOrange = CreateSolidBrush(RGB(200, 140, 111));
HBRUSH brushBlue = CreateSolidBrush(RGB(100, 60, 150));
HBRUSH brushGray = CreateSolidBrush(RGB(128, 128, 128));
HBRUSH brushPink = CreateSolidBrush(RGB(255, 0, 127));

void drawFrame()
{
	SelectObject(dc, penBlue);
	SelectObject(dc, brushBlue);
	Rectangle(dc, 0, 0, 960, 450);
	SelectObject(dc, brushBlack);
	Rectangle(dc, 25, 25, 935, 415);
}

void setCursor(int x, int y)
{
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}

void showConsoleCursor(bool showFlag)
{
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = showFlag; 
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void wait()
{
	Button* button = new Button(Button::ENTER);
	Button but = getButton(button, 1);
	delete button;
}

void printAtCenter(string text, int y, Printer p, int beginning)
{
	int x = beginning + (width - beginning*12) / 24 - text.size() / 2;
	setCursor(x, y);
	p.print(text);
}

void printerRect(int x1, int y1, int x2, int y2,Printer& p)
{
	for (int i = y1; i <= y2; ++i)
	{
		setCursor(x1, i);
		for (int j = 0; j < x2 - x1; ++j)
		{
			p.print(" ");
		}
	}
}

void setConsoleVisability(bool visible)
{	AllocConsole();
	ShowWindow(handle, visible);
}


string inputName(int sz, int x, int y)
{
	setCursor(x, y);
	string winName;
	char ch = 0;
	int spCounter = 0;
	while (spCounter < sz + 1 && ch != 13)
	{
		ch = _getch();
		
		if (ch == 8 && spCounter > 0)
		{
			spCounter--;
			winName.pop_back();
			setCursor(x + spCounter, y);
			cout << " ";
			setCursor(x + spCounter, y);
		}
		
		else if (ch == 13 && winName.size() == 0)
		{
			winName = "Nobody";
		}
		else if (ch != 8 && ch != 13 && spCounter != sz - 1)
		{
			winName += ch;
			cout << ch;
			spCounter++;
		}
	}
	return winName;
}


void scrollOff(int width, int height)
{
	string cols = to_string(width / 12);
	string lines = to_string(height / 20);
	string str = "mode con cols=" + cols + " lines=" + lines;
	const char* sch = str.c_str();
	system(sch);
}

void setConsole(int w, int h)
{
	srand(time(0));
	width = w;
	height = h;
	
	scrollOff(width, height);

	if (hConsole != INVALID_HANDLE_VALUE) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 12;
		cfi.dwFontSize.Y = 20;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = 400;
		wcscpy_s(cfi.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	}


	GetWindowRect(handle, &r);
	MoveWindow(handle, r.left, r.top, width, height, TRUE);
	HMENU hm;
	hm = GetSystemMenu(handle, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(handle);
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

int getHP()
{
	switch (currMode)
	{
	case DifficultyModes::Easy:
		return 25;
	case DifficultyModes::Medium:
		return 20;
	case DifficultyModes::Hard:
		return 15;
	}
}

int getBonusses()
{
	switch (currMode)
	{
	case DifficultyModes::Easy:
		return 4;
	case DifficultyModes::Medium:
		return 2;
	case DifficultyModes::Hard:
		return 1;
	}
}

int getFines()
{
	switch (currMode)
	{
	case DifficultyModes::Easy:
		return 2;
	case DifficultyModes::Medium:
		return 1;
	case DifficultyModes::Hard:
		return 1;
	}
}
