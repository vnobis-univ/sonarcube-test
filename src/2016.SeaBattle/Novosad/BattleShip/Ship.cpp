#include "Ship.h"
#include "ConsoleFunctions.h"
#include "CellState.h"

Ship::Ship(int size, ShipOrientation orientation) : 
	locationX_(0), 
	locationY_(0), 
	orientation_(orientation)
{
	size_ = size;
	shipCells_ = new CellState[size_];
	for (int i = 0; i < size_; i++)
	{
		shipCells_[i] = CellState::Empty;
	}
}

void Ship::getIndexOfFirstAndLastKilledCell(int& indexOfFirst, int& indexOfLast)
{
	for (int i = 0; i < 10; i++)
	{
		if (shipCells_[i] == CellState::Hit && (i == 0 || (i != 0 && shipCells_[i - 1] == CellState::Empty)))
		{
			indexOfFirst = i;
		}
		if (shipCells_[i] == CellState::Hit && (i == size_ - 1 || (i != size_ - 1 && shipCells_[i + 1] == CellState::Empty)))
		{
			indexOfLast = i;
			break;
		}
	}
}

ShipOrientation Ship::getOrientation()
{
	return orientation_;
}

CellState Ship::getCellState(int i)
{
	return shipCells_[i];
}

int Ship::getSize()
{
	return size_;
}

int Ship::getLocationX()
{
	return locationX_;
}

int Ship::getLocationY()
{
	return locationY_;
}

void Ship::setCellState(int i, CellState state)
{
	shipCells_[i] = state;
}

void Ship::setOrientation(ShipOrientation orientation)
{
	orientation_ = orientation;
}

void Ship::setLocationX(int x)
{
	locationX_ = x;
}

void Ship::setLocationY(int y)
{
	locationY_ = y;
}

bool Ship::isNotKilled()
{
	bool result = false;
	for (int i = 0; i < size_; i++)
	{
		if (shipCells_[i] == CellState::Empty)
		{
			result = true;
			break;
		}
	}
	return result;
}
