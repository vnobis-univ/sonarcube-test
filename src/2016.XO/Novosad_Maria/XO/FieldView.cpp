#include "FieldView.h"
#include <windows.h>
#include <conio.h>
#include "func.h"
#include "StartView.h"
#include "ResultView.h"
#include <cstdlib>
#include <time.h>
#include "Player.h"
#include "Globals.h"

FieldView::FieldView() : x(0), y(0), score(0)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			array[i][j] = CellState::EMPTY;
		}
	}
}

FieldView::FieldView(int score) : x(0), y(0), score(score)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			array[i][j] = CellState::EMPTY;
		}
	}
}

void printCell(int i, int j, CellState cellStatus, bool isSelected)
{
	string line1, line2, line3, line4;
	Printer printer;
	Printer empty(Color::Light_Green, isSelected ? Color::Light_Green : Color::Green);
	Printer zero(Color::Light_Green, isSelected ? Color::Light_Green : Color::Green);
	Printer cross(Color::Red, isSelected ? Color::Light_Green : Color::Green);

	switch (cellStatus)
	{
	case CellState::EMPTY:
		line1 = "    ";
		line2 = "    ";
		line3 = "    ";
		line4 = "    ";
		printer = empty;
		break;
	case CellState::CROSS:
		line1 = "\\  /";
		line2 = " \\/ ";
		line3 = " /\\ ";
		line4 = "/  \\";
		printer = cross;
		break;
	case CellState::ZERO:
		line1 = " /\\ ";
		line2 = "/  \\";
		line3 = "\\  /";
		line4 = " \\/ ";
		printer = zero;
		break;
	}

	int xStartPos = (consoleWidth - 14) / 2 + (consoleWidth - 14) % 2;

	int x = xStartPos + 5 * i;
	int y = 5 + 5 * j;
	setCursoreAtPosition(x, y);
	printer.print(line1);
	setCursoreAtPosition(x, y + 1);
	printer.print(line2);
	setCursoreAtPosition(x, y + 2);
	printer.print(line3);
	setCursoreAtPosition(x, y + 3);
	printer.print(line4);
}
void FieldView::printFieldCells()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printCell(i, j, array[j][i], (i == x && j == y));
		}
	}
}

void drawEmptyField()
{
	printAtCenterOfLine(5, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(6, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(7, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(8, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(9, "--------------", yellowSymbolsGreenBackground);
	printAtCenterOfLine(10, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(11, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(12, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(13, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(14, "--------------", yellowSymbolsGreenBackground);
	printAtCenterOfLine(15, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(16, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(17, "    |    |    ", yellowSymbolsGreenBackground);
	printAtCenterOfLine(18, "    |    |    ", yellowSymbolsGreenBackground);
}
void FieldView::draw()
{
	printAtCenterOfLine(1, "Score: " + to_string(score), yellowSymbolsGreenBackground);
	printAtCenterOfLine(25, "Press ESC to return to main menu", yellowSymbolsGreenBackground);
	drawEmptyField();
	printFieldCells();
}

bool playerWins(CellState array[3][3], CellState player)
{
	//player can be user or computer:
	//if CellState player is CROSS, then function check if user won, 
	//and if CellState player is ZERO, then function check if computer won
	for (int i = 0; i < 3; i++)
	{
		if (array[i][0] == player
			&& array[i][1] == player
			&& array[i][2] == player)
		{
			return true;
		}
	}
	for (int j = 0; j < 3; j++)
	{
		if (array[0][j] == player
			&& array[1][j] == player
			&& array[2][j] == player)
		{
			return true;
		}
	}

	if (array[0][0] == player
		&& array[1][1] == player
		&& array[2][2] == player)
	{
		return true;
	}

	if (array[0][2] == player
		&& array[1][1] == player
		&& array[2][0] == player)
	{
		return true;
	}

	return false;
}

bool hasEmptyCells(CellState array[3][3])
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (array[i][j] != CellState::CROSS && array[i][j] != CellState::ZERO)
			{
				return true;
			}
		}
	}

	return false;
}

View* FieldView::handle()
{
	View* newView = this;
	int key = _getch();
	srand(time(NULL));

	switch (key)
	{
	case KEY_ESCAPE:
		newView = new StartView();
		break;
	case KEY_ENTER:
	{
		if (array[y][x] != CellState::CROSS && array[y][x] != CellState::ZERO)
		{
		  array[y][x] = CellState::CROSS;
		  if (hasEmptyCells(array))
		  {
			  while (true)
			  {
				  int newX = rand() % 3;
				  int newY = rand() % 3;
				  if (array[newY][newX] != CellState::CROSS && array[newY][newX] != CellState::ZERO)
				  {
					  array[newY][newX] = CellState::ZERO;
					  break;
				  }
			  }
			  if (playerWins(array, CellState::CROSS))
			  {
				  newView = new FieldView(score + 1);
			  }
			  else if (playerWins(array, CellState::ZERO))
			  {
				  newView = new ResultView(score);
			  }
		  }
		  else
		  {
			  if (playerWins(array, CellState::ZERO))
			  {
				  newView = new ResultView(score);
			  }
			  else if (playerWins(array, CellState::CROSS))
			  {
				  newView = new FieldView(score + 1);
			  }
			  else
			  {
				  newView = new FieldView(score);
			  }
		  }
		}
		break;
	}
	case KEY_LEFT:
		if (x - 1 < 0)
		{
			x = 2;
		}
		else
		{
			x--;
		}
		break;
	case KEY_RIGHT:
		x = (x + 1) % 3;
		break;
	case KEY_UP:
		if (y - 1 < 0)
		{
			y = 2;
		}
		else
		{
			y--;
		}
		break;
	case KEY_DOWN:
		y = (y + 1) % 3;
		break;
	}
	return newView;
}
