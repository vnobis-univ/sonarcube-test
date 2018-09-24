#pragma once
#include "Classes.h"

void Cell::setXY(int xx, int yy)
{
	x = xx;
	y = yy;
}

Gamer::Gamer() : hasWon(false){}

void Gamer::add(Cell cell)
{
	arr[cell.x][cell.y] = 1;
}

bool Gamer::isWinner()
{
	if (!hasWon && ((arr[0][0] == 1 && arr[0][1] == 1 && arr[0][2] == 1) ||
		(arr[1][0] == 1 && arr[1][1] == 1 && arr[1][2] == 1) ||
		(arr[2][0] == 1 && arr[2][1] == 1 && arr[2][2] == 1) ||
		(arr[0][0] == 1 && arr[1][0] == 1 && arr[2][0] == 1) ||
		(arr[0][1] == 1 && arr[1][1] == 1 && arr[2][1] == 1) ||
		(arr[0][2] == 1 && arr[1][2] == 1 && arr[2][2] == 1) ||
		(arr[0][0] == 1 && arr[1][1] == 1 && arr[2][2] == 1) ||
		(arr[0][2] == 1 && arr[1][1] == 1 && arr[2][0] == 1)))
	{
		hasWon = true;
	}
	return hasWon;
}

void Gamer::popElement(Cell cell)
{
	arr[cell.x][cell.y] = 0;
}

bool GamerComputer::tryToWin(Field * _arr, Cell & cell)
{
	Cell tryCell;
	bool isFound = false;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (arr[i][j] != 1)
			{
				tryCell.setXY(i, j);
				add(tryCell);
				if (!(*(_arr + i * 3 + j)).isChosen() && isWinner())
				{
					cell = tryCell;
					isFound = true;
				}
				else
				{
					popElement(tryCell);
				}
			}
		}
	}
	return isFound;
}

Cell GamerComputer::computersChoice(Field * _arr)
{
	Cell cell;
	bool isFound = false;
	while (!isFound)
	{
		//it is added to make computer a little bit smarter
		isFound = tryToWin(_arr, cell);
		if (!isFound)
		{
			int num1 = rand() % 3;
			int num2 = rand() % 3;
			if (!(*(_arr + num1 * 3 + num2)).isChosen())
			{
				cell.setXY(num1, num2);
				add(cell);
				isFound = true;
			}
		}
	}
	return cell;
}

Field::Field(bool x, bool o) :chosenX(x), chosenO(o){}

void Field::draw(int _x, int _y, bool colored)
{
	int x = 250 + delta*_x;
	int y = 100 + delta*_y;	
	
	SelectObject(dc, colored ? penBlue : penOrange);
	SelectObject(dc, colored ? brushBlue : brushOrange);
	Rectangle(dc, x, y, x + delta, y + delta);	

	SelectObject(dc, brushBlack);
	Rectangle(dc, x + 2, y + 2, x + delta - 2, y + delta - 2);

	if (chosenX)
	{
		MoveToEx(dc, x, y + delta, NULL);
		LineTo(dc, x + delta, y);

		MoveToEx(dc, x + delta, y + delta, NULL);
		LineTo(dc, x, y);
	}
	else if (chosenO)
	{
		Ellipse(dc, x + 2, y + 2, x + delta - 2, y + delta - 2);
	}
}

bool Field::isChosen()
{
	return (chosenX || chosenO);
}

void Field::setChosenX(bool isX)
{
	chosenX = isX;
}

void Field::setChosenO(bool isO)
{
	chosenO = isO;
}

void Field::setPure()
{
	chosenX = 0;
	chosenO = 0;
}