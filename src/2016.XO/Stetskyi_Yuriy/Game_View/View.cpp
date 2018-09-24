#pragma once

#include <iostream>
#include <string>

#include "ConsoleCustomize.h"
#include "View.h"
#include "SysUtils.h"

using namespace std;

extern const int FONT_WIDTH;
extern const int FONT_HEIGHT;
extern const int CONSOLE_WIDTH;
extern const int CONSOLE_HEIGHT;


Printer headline(Color::YELLOW, Color::BLUE);
Printer stats(Color::YELLOW, Color::BROWN);
Printer finish(Color::BLACK, Color::WHITE);

HWND hwnd = GetConsoleWindow();
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HDC hdc = GetDC(hwnd);
RECT rect;
POINT op;
COORD cursor;

void View::clear() // sets green background for all windows
{
	system("cls");

	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	SetDCBrushColor(hdc, RGB(0, 200, 0));
	SetDCPenColor(hdc, RGB(100, 0, 0));

	GetClientRect(hwnd, &rect);
	Rectangle(hdc, 0, 0, CONSOLE_WIDTH*FONT_WIDTH, CONSOLE_HEIGHT*FONT_HEIGHT + 30);

}
