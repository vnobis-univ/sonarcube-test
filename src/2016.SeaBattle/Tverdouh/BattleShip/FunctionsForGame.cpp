#include <string>
#include <iostream>
#include "FunctionsForGame.h"

using namespace std;


HWND handlew = GetConsoleWindow();
HDC dc = GetDC(handlew);

HPEN redPen = CreatePen(PS_SOLID, 3, RGB(151, 0, 0));
HPEN bluePen = CreatePen(PS_SOLID, 3, RGB(0, 0, 128));
HPEN bluePenSmaller = CreatePen(PS_SOLID, 2, RGB(0, 0, 128));
HPEN redPenSmaller = CreatePen(PS_SOLID, 2, RGB(151, 0, 0));
HPEN blackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));

HBRUSH PenWhite = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH PenBlue = CreateSolidBrush(RGB(90, 126, 143));
HBRUSH PenLightBlue = CreateSolidBrush(RGB(152, 188, 205));
HBRUSH PenDarkerWhite = CreateSolidBrush(RGB(243, 243, 243));
HBRUSH PenBlack = CreateSolidBrush(RGB(0, 0, 0));

int consoleW = 45;
int consoleH = 20;
int lines = 28;

void drawFrame(HPEN pen1, HBRUSH pen2, int x1, int y1, int x2, int y2)
{
	SelectObject(dc, pen1);
	SelectObject(dc, pen2);
	Rectangle(dc, x1, y1, x2, y2);
}

void drawNet(int x1, int y1)
{
	const int numOfLines = 10;
	SelectObject(dc, blackPen);
	SelectObject(dc, blackPen);
	for (int i = 0; i <= numOfLines; ++i)
	{
		int position_x = x1 + i * lines;
		MoveToEx(dc, position_x, y1, NULL);
		LineTo(dc, position_x, y1 + lines * numOfLines);
	}
	for (int i = 0; i <= numOfLines; ++i)
	{
		int position_y = y1 + i * lines;
		MoveToEx(dc, x1, position_y, NULL);
		LineTo(dc, x1 + lines * numOfLines, position_y);
	}
}

void drawCross(bool isSel, int x, int y)
{
	SelectObject(dc, bluePenSmaller);
	isSel ? SelectObject(dc, PenLightBlue) : SelectObject(dc, PenBlue);
	Rectangle(dc, x, y, x + lines, y + lines);
	SelectObject(dc, redPen);
	SelectObject(dc, PenBlue);
	MoveToEx(dc, x, y, NULL);
	LineTo(dc, x + lines, y + lines);
	MoveToEx(dc, x, y + lines, NULL);
	LineTo(dc, x + lines, y);
}

void drawPoint(bool isSel, int x, int y)
{
	SelectObject(dc, bluePenSmaller);
	isSel ? SelectObject(dc, PenLightBlue) : SelectObject(dc, PenWhite);
	Rectangle(dc, x, y, x + lines, y + lines);
	SelectObject(dc, blackPen);
	SelectObject(dc, PenBlack);
	Ellipse(dc, x + lines / 3 + 1, y + lines / 3 + 1, x + lines * 2 / 3, y + lines * 2 / 3);
}

void drawRectangle(HPEN pen, HBRUSH brush, int x, int y)
{
	SelectObject(dc, pen);
	SelectObject(dc, brush);
	Rectangle(dc, x, y, x + lines, y + lines);
}