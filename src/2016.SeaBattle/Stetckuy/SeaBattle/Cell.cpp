#pragma once

#include "Cell.h"
#include "ConsoleProperties.h"

Cell::Cell(int _x, int _y, int _sideX, int _sideY, bool _hidden, bool _marked)
	: x(_x),
	y(_y),
	sideX(_sideX),
	sideY(_sideY),
	empty(true),
	hidden(_hidden),
	marked(_marked)
{
}

void Cell::draw()
{

	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	SetDCPenColor(hdc, RGB(255, 255, 255));
	SetDCBrushColor(hdc, RGB(0, 0, 255));
	
	if (!hidden)
	{
		if (!isEmpty())
		{
			SetDCBrushColor(hdc, RGB(255, 0, 0)); // if not - empty -> paint red; else -> blue
		}
	}

	GetClientRect(hwnd, &rect);
	Rectangle(hdc, x, y, x + sideX, y + sideY);
}

void Cell::activate()
{
	empty = false;
}

void Cell::disactivate()
{
	empty = true;
}

bool Cell::isEmpty()
{ 
	return empty;
}

int Cell::getX() const
{ 
	return x; 
}

int Cell::getY() const 
{ 
	return y;
}

int Cell::getSideX() const 
{ 
	return sideX;
}

int Cell::getSideY() const
{
	return sideY;
}

void Cell::setX(int _x)
{
	x = _x;
}

void Cell::setY(int _y)
{
	y = _y;
}

void Cell::setSideX(int _sideX)
{
	sideX = _sideX;
}

void Cell::setSideY(int _sideY)
{
	sideY = _sideY;
}

void Cell::hide()
{
	hidden = true;
}

void Cell::reveal()
{
	hidden = false;
}

bool Cell::isHidden() const
{
	return hidden;
}

bool Cell::isMarked() const
{
	return marked;
}

void Cell::drawOutline(State st)
{
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	GetClientRect(hwnd, &rect);

	if (st == State::ACTIVE)
	{
		SetDCPenColor(hdc, RGB(255, 0, 0));
	}
	else
	{
		SetDCPenColor(hdc, RGB(255, 255, 255));
	}

	// draws a "X"

	POINT op;
	MoveToEx(hdc, x + 5, y + 5, &op);
	LineTo(hdc, x + sideX - 5, y + sideY - 5);
	MoveToEx(hdc, x + sideX - 5, y + 5, &op);
	LineTo(hdc, x + 5, y + sideY - 5);
}

void Cell::mark()
{
	// makes cell hit

	marked = true;
	hidden = false;

	// when not empty - background is red; else - blue

	draw();
	drawOutline(State::PASSIVE); // draws a "X"
}