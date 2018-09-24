#pragma once

#include <Windows.h>
#include "SysUtils.h"


Cell::Cell(int _x, int _y, int _side) 
	: x(_x), 
	y(_y), 
	side(_side), 
	state(' ') 
{
}

void Cell::draw(COLORREF pen, COLORREF brush) // draws empty Cell 
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));
	SetDCPenColor(hdc, pen);
	SetDCBrushColor(hdc, brush);
	GetClientRect(hwnd, &rect);
	Rectangle(hdc, x, y, x + side, y + side);
}

void Cell::drawX(int coordX, int coordY, COLORREF penColor) // draws "X" inside the Cell
{
	SetDCPenColor(hdc, penColor);
	GetClientRect(hwnd, &rect);
	MoveToEx(hdc,coordX + 5, coordY + 5, &op);
	LineTo(hdc, coordX + side - 5, coordY + side - 5);
	MoveToEx(hdc, coordX + side - 5, coordY + 5, &op);
	LineTo(hdc, coordX + 5, coordY + side - 5);
}

void Cell::drawO(int coordX, int coordY, COLORREF penColor, COLORREF brushColor) // draws "O" inside the Cell
{
	SetDCPenColor(hdc, penColor);
	SetDCBrushColor(hdc, brushColor);
	GetClientRect(hwnd, &rect);
	Ellipse(hdc, coordX + 5, coordY + 5, coordX + side - 5, coordY + side - 5);
}

void Cell::activate()
{
	draw(RGB(0, 0, 255), RGB(0, 50, 50));

	if (state == 'X')
	{
		drawX(x, y, RGB(255, 255, 255));
	}
	else if (state == 'O')
	{
		drawO(x, y, RGB(0, 0, 255), RGB(200, 200, 0));
	}
}

void Cell::disactivate()
{
	draw(RGB(100, 0, 0), RGB(200, 200, 0));

	if (state == 'X')
	{
		drawX(x, y, RGB(255, 255, 255));
	}
	else if (state == 'O')
	{
		drawO(x, y, RGB(0, 0, 255), RGB(0, 50, 50));
	}
}

void Cell::fill(const char ch)
{
	switch (state)
	{
	case ' ':
		if (ch == 'X')
		{
			state = 'X';
			drawX(x, y, RGB(255, 255, 255));
		}
		else if (ch == 'O')
		{
			state = 'O';
			drawO(x, y, RGB(0, 0, 255), RGB(0, 50, 50));
		}
		break;
	}
}

bool Cell::empty() const 
{ 
	return state == ' '; 
}

int Cell::getX() const
{ 
	return x; 
}

int Cell::getY() const 
{ 
	return y;
}

int Cell::getSide() const 
{ 
	return side;
}

char Cell::getState() const 
{
	return state; 
}