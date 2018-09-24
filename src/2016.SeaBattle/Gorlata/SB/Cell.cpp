#include "Cell.h"
#include "Utils.h"
#include <Windows.h>

Cell::Cell(int _x, int _y, State _st): x(_x), y(_y), state(_st)
{
}

void Cell::draw(int FieldX, int FieldY, HPEN pen)
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, FieldX + x*size, FieldY + y*size, NULL);
	LineTo(hdc, FieldX + x*size, FieldY + y*size + size);
	LineTo(hdc, FieldX + x*size + size, FieldY + y*size + size);
	LineTo(hdc, FieldX + x*size + size, FieldY + y*size);
	LineTo(hdc, FieldX + x*size, FieldY + y*size);
}

void Cell::drawDot(int FieldX, int FieldY, HPEN pen) 
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	SetDCBrushColor(hdc, RGB(242, 134, 109));
	SelectObject(hdc, GetStockObject(DC_BRUSH));

	Ellipse(hdc, (FieldX + x*size) + 5, (FieldY + y*size) + 5,
		FieldX + (x + 1)*size - 5, FieldY + (y + 1)*size - 5);
}

void Cell::drawCross(int FieldX, int FieldY, HPEN pen)
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, FieldX + x*size +1, FieldY + y*size + 1, NULL);
	LineTo(hdc, FieldX + (x + 1)*size - 1, FieldY + (y + 1)*size - 1);
	MoveToEx(hdc, FieldX + (x + 1)*size - 1, FieldY + y*size + 1, NULL);
	LineTo(hdc, FieldX + x*size + 1, FieldY + (y + 1)*size - 1);

}

int Cell::getX()
{
	return x;
}

int Cell::getY()
{
	return y;
}

void Cell::setY(int _y)
{
	y = _y;
}

void Cell::setX(int _x)
{
	x = _x;
}

int Cell::getSize()
{
	return size;
}

State Cell::getState()
{
	return state;
}

void Cell::setState(State my_state)
{
	state = my_state;
}

bool Cell::isValid()
{
	return (x >= 1 && x <= 10 && y >= 1 && y <= 10);
}

