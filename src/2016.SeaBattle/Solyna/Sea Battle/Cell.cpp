#include "Cell.h"



Cell::Cell(unsigned _red, unsigned _green, unsigned _blue):
	red(_red), green(_green), blue(_blue), status(CellStatus::Empty)
{
}

void Cell::setStatus(CellStatus _status)
{
	status = _status;
}

void Cell::drawCell(int coordinateX, int coordinateY)
{
	HDC hdc = GetDC(GetConsoleWindow());
	HPEN Pen(CreatePen(PS_SOLID, 2, RGB(red, green, blue)));
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, Pen);
	MoveToEx(hdc, coordinateX,coordinateY, NULL);         
	LineTo(hdc, coordinateX + size, coordinateY);
	LineTo(hdc, coordinateX + size, coordinateY + size);
	LineTo(hdc, coordinateX , coordinateY + size);
	LineTo(hdc, coordinateX, coordinateY);

}

void Cell::changeColor()
{
	red = 0;
	green = 0;
	blue = 204;
}

void Cell::backToColor()
{
	red = 204;
	green = 0;
	blue = 102;
}

CellStatus Cell::getStatus()
{
	return status;
}

Cell::Cell()
{
}


Cell::~Cell()
{
}
