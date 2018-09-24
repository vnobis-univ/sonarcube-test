#pragma once
#include "ShipOrientation.h"
#include "CellState.h"
#include <vector>

using namespace std;

class Ship
{
	int size_;
	int locationX_;
	int locationY_;
	ShipOrientation orientation_;
	CellState* shipCells_;
public:
	Ship(int _size, ShipOrientation _position);
	int getSize();
	int getLocationX();
	int getLocationY();
	void setLocationX(int x);
	void setLocationY(int y);
	void setCellState(int i, CellState state);
	void setOrientation(ShipOrientation orientation);
	CellState getCellState(int i);
	ShipOrientation getOrientation();
	bool isNotKilled();
	void getIndexOfFirstAndLastKilledCell(int& indexOfFirst, int& indexOfLast);
};

