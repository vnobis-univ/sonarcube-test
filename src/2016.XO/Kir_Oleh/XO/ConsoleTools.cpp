#pragma once
#include "ConsoleTools.h"
#include <conio.h>
#include <iostream>
#include "Buttons.h"

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

HBRUSH brushBlack = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH brushOrange = CreateSolidBrush(RGB(200, 140, 111));
HBRUSH brushBlue = CreateSolidBrush(RGB(100, 60, 150));
HBRUSH brushGray = CreateSolidBrush(RGB(128, 128, 128));


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

void scrollOff(int width, int height)
{
	string cols = to_string(width/10);
	string lines = to_string(height/20);
	string str = "mode con cols=" + cols + " lines=" + lines;
	const char* sch = str.c_str();
	system(sch);
}

void printAtMiddle(string text, int y, Printer p)
{
	int x = width / 20 - text.size() / 2;
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

string inputName()
{
	string winName;
	char ch = 0;
	int spCounter = 0;
	while (spCounter < 16 && ch != 13)
	{
		ch = _getch();
		//in case user wants to delete smth
		if (ch == 8 && spCounter > 0)
		{
			winName.pop_back();
			setCursor(38 + spCounter, 10);
			cout << " ";
			setCursor(38 + spCounter, 10);
			spCounter--;
		}
		//in case the user inputed nothing and pressed enter
		//we we make winname = "---"
		else if (ch == 13 && winName.size() == 0)
		{
			winName = "- - -";
		}
		else if (ch != 8 && ch != 13 && spCounter != 14)
		{
			winName += ch;
			cout << ch;
			spCounter++;
		}
	}
	return winName;
}

void setConsole(int w, int h)
{
//	width = w;
//	height = h;
//
//	//turns off the scrollbar
//	scrollOff(width, height);
//
//	//sets console size
//	GetWindowRect(handle, &r);
//	MoveWindow(handle, r.left, r.top, width, height, TRUE);
//
//	//disallows resizing console size manually
//	HMENU hm;
//	hm = GetSystemMenu(handle, FALSE);
//	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
//	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
//	DrawMenuBar(handle);
	width = w * 10;
	height = h * 20;

	scrollOff(width, height);
	//set font settings
	if (hConsole != INVALID_HANDLE_VALUE) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 10;
		cfi.dwFontSize.Y = 20;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = 400;
		wcscpy_s(cfi.FaceName, L"Raster Font");
		SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
	}


	SMALL_RECT r;
	r.Left = 0;
	r.Top = 0;
	r.Right = w - 1;
	r.Bottom = h - 1;
	SetConsoleWindowInfo(hConsole, TRUE, &r);

	COORD c;
	c.X = w;
	c.Y = h;
	SetConsoleScreenBufferSize(hConsole, c);

	/*GetWindowRect(handle, &r);
	MoveWindow(handle, r.left, r.top, width, height, TRUE);*/
	//disallows resizing console size manually


	HMENU hm;
	hm = GetSystemMenu(handle, FALSE);
	RemoveMenu(hm, SC_SIZE, MF_BYCOMMAND | MF_REMOVE);
	RemoveMenu(hm, SC_MAXIMIZE, MF_BYCOMMAND | MF_REMOVE);
	DrawMenuBar(handle);
}

HPEN getPen(int r, int g, int b)
{
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(r, g, b));
	return pen;
}

HBRUSH getBrush(int r, int g, int b)
{
	HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
	return brush;
}

void drawFrame()
{
	SelectObject(dc, penOrange);
	SelectObject(dc, brushBlack);

	Rectangle(dc, 200, 100, 600, 300);
	Rectangle(dc, 210, 105, 590, 295);
}