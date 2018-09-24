#include <iostream>
#include <string>
#include "Cell.h"

Cell::Cell(): cellState(cellOptions::empty) { }

std::string* Cell::getHowToDrawCell(int size) const
{
	std::string* print = new std::string[size];

	for (int i = 0; i < size; ++i)
	{
		print[i] = "";

		switch (cellState)
		{
		case cellOptions::empty:
			for (int j = 0; j < size; ++j)
				print[i] += " ";
			break;

		case cellOptions::cross:
			for (int j = 0; j < size; ++j)
				if (i == j || size - i - 1 == j)
					print[i] += "*";
				else
					print[i] += " ";
			break;

		case cellOptions::zero:
			for (int j = 0; j < size; ++j)
				if ((i == 0 || j == 0 || i == size - 1 || j == size - 1) &&
					(i != j && i != size - j - 1 && j != size - i - 1))
					print[i] += "*";
				else
					print[i] += " ";
			break;
		}
	}

	return print;
}

void Cell::setCellState(cellOptions option)
{
	cellState = option;
}

cellOptions Cell::getCellState() const
{
	return cellState;
}

