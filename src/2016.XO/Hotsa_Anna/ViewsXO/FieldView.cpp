#include "FieldView.h"
#include "Printer.h"
#include "Utils.h"
#include "StartView.h"
#include "ResultView.h"
#include "HighScoreView.h"
#include <string>
#include <conio.h>

CellStatus FieldView::getStatus(int i, int j)
{
	return field[i][j];
}

FieldView::FieldView():	selectedCellX(1), selectedCellY(1), score(0)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			field[i][j] = CellStatus::EMPTY;
		}
	}
}

FieldView::FieldView(int score1):selectedCellX(1), selectedCellY(1), score (score1)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			field[i][j] = CellStatus::EMPTY;
		}
	}
}

bool FieldView::isSelected(int i, int j)
{
	return i == selectedCellX && j == selectedCellY;
}

void drawEmptyField()
{
	Printer field(Color::GRAY, Color::GRAY);
	for (size_t i = 7; i < 11; i++)
	{
		printAtCenter(i, "    ||    ||    ", field);
	}
	printAtCenter(11, "================", field);
	for (size_t i = 12; i < 16; i++)
	{
		printAtCenter(i, "    ||    ||    ", field);
	}
	printAtCenter(16,"================", field); 
	for (size_t i = 17; i < 21; i++)
	{
		printAtCenter(i, "    ||    ||    ", field);
	}
}

void drawSelectedCell(int i, int j, bool isCellSelected, CellStatus status)
{
	string line1;
	string line2;
	string line3;
	string line4;
	Printer printer;
	Printer emptyPrinter(Color::RED, isCellSelected ? Color::LIGHT_WHITE : Color::LIGHT_BLUE);
	Printer crossPrinter(Color::BLACK, isCellSelected ? Color::LIGHT_AQUA : Color::LIGHT_BLUE);
	Printer zeroPrinter(Color::BLACK, isCellSelected ? Color::LIGHT_AQUA : Color::LIGHT_BLUE);

	switch (status)
	{
	case CellStatus ::EMPTY:
	{
		line1 = "    ";
		line2 = "    ";
		line3 = "    ";
		line4 = "    ";
		printer = emptyPrinter;
	}
	break;
	case CellStatus ::CROSS:
	{
		line1 = "\\  /";
		line2 = " \\/ ";
		line3 = " /\\ ";
		line4 = "/  \\";
		printer = crossPrinter;
	}
	break;
	case CellStatus ::ZERO:
	{
		line1 = " /\\ ";
		line2 = "/  \\";
		line3 = "\\  /";
		line4 = " \\/ ";
		printer = zeroPrinter;
	}
	}
	int x = 21 + 6 * i;
	int y = 7 + 5 * j;
	moveCursorTo(x, y);
	printer << line1;
	moveCursorTo(x, y + 1);
	printer << line2;
	moveCursorTo(x, y + 2);
	printer << line3;
	moveCursorTo(x, y + 3);
	printer << line4;
}

void FieldView::printAllCells()
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			CellStatus status = getStatus(i, j);
			bool isSelect = isSelected(i, j);
			drawSelectedCell(i, j, isSelect, status);
		}
	}
}

void typeName();
void FieldView::draw()
{
	typeName();
	View::draw();
	Printer field(Color::BLUE, Color::LIGHT_WHITE);
	printAtCenter(5, " SCORE : " + to_string(score), field);
	drawEmptyField();
	printAllCells();
	printAtCenter(24, "[ PRESS ESC TO BACK TO MENU ]", field);
	showCursor(false);
}

View *FieldView::handle()
{
	View * nextView = this;
	bool choose = false;
	int x = selectedCellX;
	int y = selectedCellY;

	int button;
	while (!choose)
	{
		button = _getwch();
		switch (button)
		{
		case 80: //Down
		{
			y++;
			if(y > 2)
			{
				y = 0;
			}
		}
		break;
		case 72: //Up
		{
			y--;
			if (y < 0)
			{
				y = 2;
			}
		}
		break;
		case 75: //Left
		{
			x--;			
			if (x < 0)
			{
				x = 2;
			}
		}
		break;
		case 77: //Right
		{
			x++;
			if (x > 2)
			{
				x = 0;
			}
		}
		break;
		case 13: //Enter
		{
			if (field[x][y] != CellStatus::CROSS && field[x][y] != CellStatus::ZERO)
			{
				field[x][y] = CellStatus::CROSS;
				if (isCellEmpty(field))
				{
					while (true)
					{
						int newX = rand() % 3;
						int newY = rand() % 3;
						if (field[newX][newY] != CellStatus::CROSS && field[newX][newY] != CellStatus::ZERO)
						{
							field[newX][newY] = CellStatus::ZERO;
							break;
						}
					}
					if (whoWins(CellStatus::CROSS, field))
					{
						nextView = new FieldView(score + 1);
					}
					else if (whoWins(CellStatus::ZERO, field))
					{
						nextView = new ResultView(score);
					}
				}
				else
				{
					if (whoWins(CellStatus::CROSS, field))
					{
						nextView = new FieldView(score + 1);
					}
					else if (whoWins(CellStatus::ZERO, field))
					{
						nextView = new ResultView(score);
					}
					else
					{
						nextView = new FieldView(score);
					}
				}
			}
		}
		break;
		case 27: //Esc
		{
			nextView = new StartView;	
		}
		break;
		}
		selectedCellX = x;
		selectedCellY = y;
		return nextView;
	}
}

bool isCellEmpty(CellStatus helpField[3][3])
{
	bool isEmpty;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (helpField[i][j] != CellStatus::ZERO && helpField[i][j] != CellStatus::CROSS)
			{
				isEmpty = true;
				return isEmpty;
				break;
			}
		}
	}
	isEmpty = false;
	return isEmpty;
}

bool whoWins(CellStatus playerStatus, CellStatus field[3][3])
{
	//check for diagonals
	if (field[0][0] == playerStatus && field[1][1] == playerStatus && field[2][2] == playerStatus)
	{
		return true;
	}
	if (field[0][2] == playerStatus && field[1][1] == playerStatus && field[2][0] == playerStatus)
	{
		return true;
	}
	
	//check for columns
	for (int i = 0; i < 3; i++)
	{
		if (field[0][i] == playerStatus && field[1][i] == playerStatus && field[2][i] == playerStatus)
		{
			return true;
		}
	}

	//check for rows
	for (int i = 0; i < 3; i++)
	{
		if (field[i][0] == playerStatus && field[i][1] == playerStatus && field[i][2] == playerStatus)
		{
			return true;
		}
	}
	return false;
}