#pragma once
#include "Cell.h"
#include "globals.h"
class Field
{
	static const int size = sizeOfField;
	Cell arrayOfCells[size][size];
public:
	Field();
	Cell &getCell(int i, int j);
	void draw(int coordinateX, int coordinateY);
};

