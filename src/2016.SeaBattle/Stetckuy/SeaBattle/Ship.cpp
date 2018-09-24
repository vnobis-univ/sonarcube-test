#pragma once

#include "Ship.h"

// tells whether ship with direction "dir" can and "size" can be placed on "field" 
// beginning with coordinates (left; top)
// returns "OK" if it can be put
// returns "FILLED" if cells are not empty
// returns "BORDER", when its coordinates are out of "field"
string canBePlaced(Cell** field, Direction dir, int top, int left, int size)
{
	string toReturn = "OK";

	bool isOk = true;

	if (dir == Direction::VERTICAL) // the direction is VERTICAL
	{
		if (top >= 0 && top + (size - 1) < 10 && left >= 0 && left < 10) // if coords not out of field
		{
			for (int i = top - 1; i < top + size + 1; ++i)
			{
				for (int j = left - 1; j < left + 2; ++j)
				{
					if (i >= 0 && i < 10 && j >= 0 && j < 10)
					{
						if (!field[i][j].isEmpty()) // if coords and bordering coords are not empty
						{
							toReturn = "FILLED"; // can't be placeds
							isOk = false;
							break;
						}
					}
				}

				if (!isOk)
				{
					break;
				}
			}

		} // if coords are out of field
		else
		{
			toReturn = "BORDER";
			isOk = false;
		}
	}
	else // if direction is HORIZONTAL
	{
		if (left >= 0 && left + (size - 1) < 10 && top >= 0 && top < 10)
		{

			for (int i = top - 1; i < top + 2; ++i)
			{
				for (int j = left - 1; j < left + size + 1; ++j)
				{
					if (i >= 0 && i < 10 && j >= 0 && j < 10)
					{
						if (!field[i][j].isEmpty())
						{
							toReturn = "FILLED";
							isOk = false;
							break;
						}
					}
				}

				if (!isOk)
				{
					break;
				}
			}
		}
		else
		{
			toReturn = "BORDER";
			isOk = false;
		}
	}

	return toReturn;
}

Ship::Ship(Cell** _f, int _t, int _l, int _s, Direction _d)
	: field(_f),
	left(_l),
	top(_t),
	size(_s),
	dir(_d)
{
}

void Ship::setDirection(Direction _dir) // changes direction of ship and shifts it to fit the field
{
	if (dir != _dir)
	{
		if (_dir == Direction::HORIZONTAL)
		{
			for (size_t i = 0; i < size; ++i)
			{
				field[top + i][left].draw();
			}

			dir = Direction::HORIZONTAL;

			while (left + size >= 10)
			{
				--left;
			}

		}
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				field[top][left + i].draw();
			}

			dir = Direction::VERTICAL;

			while (top + size >= 10)
			{
				--top;
			}
		}

		drawOutline();
	}
}

int Ship::getLeft() const
{
	return left;
}

int Ship::getTop() const
{
	return top;
}

int Ship::getSize() const
{
	return size;
}

Cell** Ship::getField() const
{
	return field;
}

void Ship::setField(Cell** f)
{
	field = f;
}

void Ship::setSize(int _s)
{
	size = _s;
}

void Ship::drawOutline() // draws a green "X" in cell if it is not empty, and red if it is empty
{
	RECT rect;
	POINT op;
	HWND hWnd = GetConsoleWindow();
	HDC hdc = GetDC(GetConsoleWindow());

	if (field != nullptr)
	{
		if (canBePlaced(field, dir, top, left, size) != "OK")
		{
			SetDCPenColor(hdc, RGB(255, 0, 0));
		}
		else
		{
			SetDCPenColor(hdc, RGB(0, 255, 0));
		}

		if (dir == Direction::VERTICAL)
		{
			for (size_t i = 0; i < size; ++i)
			{
				int coordLeft = field[top + i][left].getX();
				int coordTop = field[top + i][left].getY();
				int sideX = field[top + i][left].getSideX();
				int sideY = field[top + i][left].getSideY();

				SelectObject(hdc, GetStockObject(DC_PEN));
				SelectObject(hdc, GetStockObject(DC_BRUSH));

				GetClientRect(hWnd, &rect);

				MoveToEx(hdc, coordLeft + 5, coordTop + 5, &op);
				LineTo(hdc, coordLeft + sideX - 5, coordTop + sideY - 5);
				MoveToEx(hdc, coordLeft + sideX - 5, coordTop + 5, &op);
				LineTo(hdc, coordLeft + 5, coordTop + sideY - 5);
			}
		}
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				int coordLeft = field[top][left + i].getX();
				int coordTop = field[top][left + i].getY();
				int sideX = field[top][left + i].getSideX();
				int sideY = field[top][left + i].getSideY();

				SelectObject(hdc, GetStockObject(DC_PEN));
				SelectObject(hdc, GetStockObject(DC_BRUSH));

				GetClientRect(hWnd, &rect);

				MoveToEx(hdc, coordLeft + 5, coordTop + 5, &op);
				LineTo(hdc, coordLeft + sideX - 5, coordTop + sideY - 5);
				MoveToEx(hdc, coordLeft + sideX - 5, coordTop + 5, &op);
				LineTo(hdc, coordLeft + 5, coordTop + sideY - 5);
			}
		}
	}
}

void Ship::draw() // draws the ship
{
	if (field != nullptr)
	{
		if (dir == Direction::VERTICAL)
		{
			for (size_t i = 0; i < size; ++i)
			{
				field[top + i][left].activate(); // makes ship cells not empty
				field[top + i][left].draw();
			}
		}
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				field[top][left + i].activate(); // makes ship cells not empty
				field[top][left + i].draw();
			}
		}
	}
}

Direction Ship::getDirection() const
{
	return dir;
}

void Ship::move(int offsetTop, int offsetLeft) // moves the ship 
{
	if (canBePlaced(field, dir, top + offsetTop, left + offsetLeft, size) != "BORDER")
	{
		if (dir == Direction::VERTICAL)
		{
			for (size_t i = 0; i < size; ++i)
			{
				field[top + i][left].draw();
			}
		}
		else
		{
			for (size_t i = 0; i < size; ++i)
			{
				field[top][left + i].draw();
			}
		}

		left += offsetLeft;
		top += offsetTop;

		drawOutline();
	}
}