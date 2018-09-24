#include "Ship.h"
#include <Windows.h>
#include "Consoleutils.h"

Ship::Ship(int _size, PositionOfShip _pos) :size(_size), position(_pos)
{
	shipCells = new StateOfShipCell[size];
	for (size_t i = 0; i < size; i++)
	{
		shipCells[i] = StateOfShipCell::NotKilled;
	}
}

Ship::Ship(int x, int y, int _size, PositionOfShip _position) : coordinateXOfTopOfShip(x), coordinateYOfTopOfShip(y), size(_size), position(_position)
{
	shipCells = new StateOfShipCell[size];
	for (size_t i = 0; i < size; i++)
	{
		shipCells[i] = StateOfShipCell::NotKilled;
	}
}
void Ship::drawCell(double i, int j)
{
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 174, 144));
	HGDIOBJ currentPen = SelectObject(hdc, redPen);
	MoveToEx(hdc, i * 20, j * 16, NULL);
	LineTo(hdc, (i + 1) * 20, (j + 1) * 16);
	MoveToEx(hdc, i * 20, (j + 1) * 16, NULL);
	LineTo(hdc, (i + 1) * 20, j * 16);
	DeleteObject(redPen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}

void Ship::draw(int x, int y)
{
	for (int i = 0; i < size; i++)
	{
		if (position == PositionOfShip::Horizontal && shipCells[i] == StateOfShipCell::Killed)
		{
			drawCell(coordinateYOfTopOfShip + x / 2.0 + i, coordinateXOfTopOfShip + y);
		}
		else if (position == PositionOfShip::Vertical && shipCells[i] == StateOfShipCell::Killed)
		{
			drawCell(coordinateYOfTopOfShip + x / 2.0, coordinateXOfTopOfShip + y + i);
		}
	}
}

PositionOfShip Ship::getPosition()
{
	return position;
}

StateOfShipCell Ship::getStateOfShipCell(int x)
{
	return shipCells[x];
}

int Ship::getSize()
{
	return size;
}

int Ship::getCoordinateXOfTopOfShip()
{
	return coordinateXOfTopOfShip;
}

int Ship::getCoordinateYOfTopOfShip()
{
	return coordinateYOfTopOfShip;
}

void Ship::setStateOfShipCell(int x, StateOfShipCell state)
{
	shipCells[x] = state;
}

void Ship::setPosition(PositionOfShip _position)
{
	position = _position;
}

void Ship::setX(int x)
{
	coordinateXOfTopOfShip = x;
}

void Ship::setY(int y)
{
	coordinateYOfTopOfShip = y;
}

bool Ship::isNotKilled()
{
	bool result = false;
	for (int i = 0; i < size; i++)
	{
		if (shipCells[i] == StateOfShipCell::NotKilled)
		{
			result = true;
			break;
		}
	}
	return result;
}

void Ship::getIndexOfFirstAndLastKilledCell(int& indexOfFirst, int& indexOfLast)
{
	for (size_t i = 0; i < size; i++)
	{
		if (shipCells[i] == StateOfShipCell::Killed && (i == 0 || (i != 0 && shipCells[i - 1] == StateOfShipCell::NotKilled)))
		{
			indexOfFirst = i;
		}
		if (shipCells[i] == StateOfShipCell::Killed && (i == size - 1 || (i != size - 1 && shipCells[i + 1] == StateOfShipCell::NotKilled)))
		{
			indexOfLast = i;
			break;
		}
	}
}