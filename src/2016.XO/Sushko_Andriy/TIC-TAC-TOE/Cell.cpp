#include "Cell.h"


Cell::Cell(int m_x, int m_y, State st) :
	x(m_x), y(m_y), state(st) {}

void Cell::drawCell(HPEN pen)
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	//cells are only for field 3x3 -> edge control for it
	if (x < 0) x = 2;
	if (x > 2) x = 0;
	if (y < 0) y = 2;
	if (y > 2) y = 0;

	MoveToEx(hdc, edgeX + x*cellSize, edgeY + y*cellSize, NULL);
	LineTo(hdc, edgeX + x*cellSize, edgeY + y*cellSize + cellSize);
	LineTo(hdc, edgeX + x*cellSize + cellSize, edgeY + y*cellSize + cellSize);
	LineTo(hdc, edgeX + x*cellSize + cellSize, edgeY + y*cellSize);
	LineTo(hdc, edgeX + x*cellSize, edgeY + y*cellSize);
}

void Cell::drawX(HPEN pen)
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);

	MoveToEx(hdc, edgeX + x*cellSize + 8, edgeY + y*cellSize + 8, NULL);
	LineTo(hdc, edgeX + (x + 1)*cellSize - 8, edgeY + (y + 1)*cellSize - 8);
	MoveToEx(hdc, edgeX + (x + 1)*cellSize - 8, edgeY + y*cellSize + 8, NULL);
	LineTo(hdc, edgeX + x*cellSize + 8, edgeY + (y + 1)*cellSize - 8);

	this -> state = Cell::State::filledX;
}

void Cell::drawO(HPEN pen)
{
	HGDIOBJ currentPen = (HPEN)SelectObject(hdc, pen);
	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));

	Ellipse(hdc, (edgeX + x*cellSize) + 8, (edgeY + y*cellSize) + 8,
		edgeX + (x + 1)*cellSize - 8, edgeY + (y + 1)*cellSize - 8);

	this->state = Cell::State::filledO;
}

void Cell::operator++()
{
	x++;
	if (x > 2)
	{
		x = 0;
		y++;
		if (y > 2)
			y = 0;
	}
}

bool Cell::operator==(const Cell & obj) const
{
	return (obj.state == state && obj.state != Cell::State::empty
							   && state != Cell::State::empty);
}
