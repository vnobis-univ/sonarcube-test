#pragma once

#include <vector>
#include <ctime>
#include <cstdlib>
#include <conio.h>

#include "SysUtils.h"

using namespace std;

bool allFilled(const vector<Cell> &v)
{
	int num = 0;
	for (size_t i = 0; i < 9; ++i)
	{
		if (v[i].empty()) ++num;
	}

	return (num == 0 ? true : false);
}


bool wonPlayer(const vector<Cell>& field)
{
	bool res = false;
	if ((field[0].getState() == 'X' && field[1].getState() == 'X' && field[2].getState() == 'X') ||
		(field[3].getState() == 'X' && field[4].getState() == 'X' && field[5].getState() == 'X') ||
		(field[6].getState() == 'X' && field[7].getState() == 'X' && field[8].getState() == 'X') ||
		(field[0].getState() == 'X' && field[4].getState() == 'X' && field[8].getState() == 'X') ||
		(field[0].getState() == 'X' && field[3].getState() == 'X' && field[6].getState() == 'X') ||
		(field[1].getState() == 'X' && field[4].getState() == 'X' && field[7].getState() == 'X') ||
		(field[2].getState() == 'X' && field[5].getState() == 'X' && field[8].getState() == 'X') ||
		(field[2].getState() == 'X' && field[4].getState() == 'X' && field[6].getState() == 'X'))
	{
		res = true;
	}
	return res;
}

bool wonBot(const vector<Cell>& field)
{
	bool res = false;
	if ((field[0].getState() == 'O' && field[1].getState() == 'O' && field[2].getState() == 'O') ||
		(field[3].getState() == 'O' && field[4].getState() == 'O' && field[5].getState() == 'O') ||
		(field[6].getState() == 'O' && field[7].getState() == 'O' && field[8].getState() == 'O') ||
		(field[0].getState() == 'O' && field[4].getState() == 'O' && field[8].getState() == 'O') ||
		(field[0].getState() == 'O' && field[3].getState() == 'O' && field[6].getState() == 'O') ||
		(field[1].getState() == 'O' && field[4].getState() == 'O' && field[7].getState() == 'O') ||
		(field[2].getState() == 'O' && field[5].getState() == 'O' && field[8].getState() == 'O') ||
		(field[2].getState() == 'O' && field[4].getState() == 'O' && field[6].getState() == 'O'))
	{
		res = true;
	}
	return res;
}

void turnOfBot(vector<Cell>& fields)
{
	srand(time(0));
	bool choice = false;
	while (!choice)
	{
		int selectCell = rand() % 8;
		if (fields[selectCell].empty())
		{
			fields[selectCell].fill('O');
			choice = true;
		}
	}
}

void analyseField(vector<Cell> fields, bool& end)
{
	if (wonPlayer(fields))
	{
		resultView.setResult(Result::VICTORY);
		resultView.draw();
		end = true;
	}
	else if (wonBot(fields))
	{
		resultView.setResult(Result::DEFEAT);
		resultView.draw();
		end = true;
	}
	else
	{
		if (allFilled(fields))
		{
			resultView.setResult(Result::DEFEAT);
			resultView.draw();
			end = true;
		}
	}
}

Cell& cell(vector<Cell>& fields, int x, int y)
{
	if ((x >= 0 && y >= 0) && (x + 3 * y < fields.size()))
	{
		return fields[x + 3 * y];
	}
}

void playGame(vector<Cell> fields)
{
	// activate  first cell
	int currentX = 0;
	int currentY = 0;
	cell(fields, currentX, currentY).activate();

	int c = 0;
	bool end = false;

	while ((c = _getch()) && !end)
	{
		switch (c)
		{
		case 224:
			switch (_getch())
			{
			case 72:	// top
				if (currentY > 0)
				{
					cell(fields, currentX, currentY).disactivate();
					--currentY;
					cell(fields, currentX, currentY).activate();
				}
				break;
			case 75: // left
				if (currentX > 0)
				{
					cell(fields, currentX, currentY).disactivate();
					--currentX;
					cell(fields, currentX, currentY).activate();
				}
				break;
			case 77: // right
				if (currentX < 2)
				{
					cell(fields, currentX, currentY).disactivate();
					++currentX;
					cell(fields, currentX, currentY).activate();
				}
				break;
			case 80: // down
				if (currentY < 2)
				{
					cell(fields, currentX, currentY).disactivate();
					++currentY;
					cell(fields, currentX, currentY).activate();
				}
				break;
			}
			break;
		case VK_RETURN:

			if (cell(fields, currentX, currentY).empty())
			{
				cell(fields, currentX, currentY).fill('X');

				if (!allFilled(fields))
				{
					turnOfBot(fields);
				}

				analyseField(fields, end);
			}
        break;
		}
	}
}

