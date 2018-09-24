#include "Field.h"



Field::Field()
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			arrayOfCells[i][j] = Cell(204, 0, 102); // very nice color
		}
	}
}

Cell &Field::getCell(int i, int j)
{
	return arrayOfCells[i][j];
}

void Field::draw(int coordinateX, int coordinateY)
{
	int x = coordinateX;
	int y = coordinateY;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			arrayOfCells[i][j].drawCell(x, y);
			x += sizeOfCell;
		}
		x = coordinateX;
		y += sizeOfCell;
	}
}
