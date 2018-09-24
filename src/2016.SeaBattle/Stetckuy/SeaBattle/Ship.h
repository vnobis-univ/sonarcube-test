#pragma once

#include <string>

#include "Cell.h"

using namespace std;

enum class Direction
{
	VERTICAL = 1,
	HORIZONTAL
};

string canBePlaced(Cell** field, Direction dir, int top, int left, int size);

class Ship
{
	int left;
	int top;
	int size;
	Direction dir;
	Cell** field;

public:
	Ship(Cell** = nullptr, int = 0, int = 0, int = 2, Direction = Direction::HORIZONTAL);

	void setDirection(Direction);

	int getLeft() const;
	int getTop() const;
	int getSize() const;
	Cell** getField() const;
	Direction getDirection() const;

	void setSize(int);
	void setField(Cell**);

	void drawOutline();
	void draw();
	
	void move(int, int);
};