#include "FieldView.h"
#include <conio.h>

Printer mainpen(Color::LightGray, Color::Black);
short turnCounter = 0;
FieldView::FieldView() :score(0)
{
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			matrix[i][j] = Empty;
		}
	}
}

FieldView::FieldView(short s) :score(s)
{
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			matrix[i][j] = Empty;
		}
	}
}

void FieldView::draw()
{
	printInCenter(0, "You scored: " + to_string(score), mainpen);
	printField();
	printCells();
}

View* FieldView::handle()
{
	short nx = selectedX;
	short ny = selectedY;
	View *nextView = this;
	switch (_getch())
	{
	case 80:
		++nx;
		break;
	case 72:
		--nx;
		break;
	case 75:
		--ny;
		break;
	case 77:
		++ny;
		break;
	case 27:
		nextView = new StartView;
		break;
	case 13:
		if (isEmpty(nx, ny))
		{
			matrix[nx][ny] = Cross;
			++turnCounter;
			if (turnCounter <= 4)
			{
				botTurn();
			}
		}
		if (playerWins())
		{
			++score;
			nextView = new FieldView(score);
			turnCounter = 0;
		}
		else if (botWins())
		{
			printCells();
			printInCenter(2, "You lost!", mainpen);
			printInCenter(3, "Press Enter to continue", mainpen);
			bool exit = false;
			while (!exit)
			{
				switch (_getch())
				{
				case 13:
					nextView = new ResultView(inTable(score), score);
					turnCounter = 0;
					exit = true;
				}

			}
		}
		if (turnCounter > 4 && playerWins() && !botWins())
		{
			nextView = new FieldView(score);
		}
		break;
	}
	if (nx >= 0 && nx < 3)
	{
		selectedX = nx;
	}
	if (ny >= 0 && ny < 3)
	{
		selectedY = ny;
	}
	return nextView;
}

void printField()
{
	printInCenter(24, "Press Ecs to exit", mainpen);
	printInCenter(6, "-------------------", mainpen);
	printInCenter(7, "|     |     |     |", mainpen);
	printInCenter(8, "|     |     |     |", mainpen);
	printInCenter(9, "|     |     |     |", mainpen);
	printInCenter(10, "|     |     |     |", mainpen);
	printInCenter(11, "-------------------", mainpen);
	printInCenter(12, "|     |     |     |", mainpen);
	printInCenter(13, "|     |     |     |", mainpen);
	printInCenter(14, "|     |     |     |", mainpen);
	printInCenter(15, "|     |     |     |", mainpen);
	printInCenter(16, "-------------------", mainpen);
	printInCenter(17, "|     |     |     |", mainpen);
	printInCenter(18, "|     |     |     |", mainpen);
	printInCenter(19, "|     |     |     |", mainpen);
	printInCenter(20, "|     |     |     |", mainpen);
	printInCenter(21, "-------------------", mainpen);
}

Status FieldView::getStatus(short i, short j)const
{
	return matrix[i][j];
}

void FieldView::printCells()
{
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j<3; ++j)
		{
			Status cell = getStatus(i, j);
			printCell(cell, isSelected(i, j), i, j);
		}
	}
}

bool FieldView::isSelected(short x, short y)
{
	return selectedX == x && selectedY == y;
}

void printCell(Status cell, bool isSelect, short i, short j)
{
	string line1, line2, line3, line4;
	Printer print;
	Printer empty(isSelect ? Color::Yellow : Color::LightGray, Color::LightGray);
	Printer cross(isSelect ? Color::Yellow : Color::LightGray, Color::Brown);
	Printer circle(isSelect ? Color::Yellow : Color::LightGray, Color::Green);
	switch (cell)
	{
	case Empty:
		line1 = "     ";
		line2 = "     ";
		line3 = "     ";
		line4 = "     ";
		print = empty;
		break;
	case Cross:
		line1 = "\\  /";
		line2 = " \\/ ";
		line3 = " /\\ ";
		line4 = "/  \\";
		print = cross;
		break;
	case Circle:
		line1 = " /\\ ";
		line2 = "/  \\";
		line3 = "\\  /";
		line4 = " \\/ ";
		print = circle;
		break;
	}
	short startPos = (consoleWidth - 16) / 2 + (consoleWidth - 20) % 2;
	short x = startPos +  6* j;
	short y = 7 + 5 * i;
	setCursor(x, y);
	print << line1;
	setCursor(x, y + 1);
	print << line2;
	setCursor(x, y + 2);
	print << line3;
	setCursor(x, y + 3);
	print << line4;
}

bool FieldView::isEmpty(short i, short j)
{
	if (getStatus(i, j) == Empty)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FieldView::botTurn()
{
	bool isPlaced = false;
	while (!isPlaced)
	{
		short compX = rand() % 3;
		short compY = rand() % 3;
		if (matrix[compX][compY] == Empty)
		{
			matrix[compX][compY] = Circle;
			isPlaced = true;
		}
	}
}

bool FieldView::playerWins()
{
	for (size_t i = 0; i < 3; ++i)
	{
		if (matrix[i][0] == Cross && matrix[i][1] == Cross && matrix[i][2] == Cross)
		{
			return true;
		}
	}

	for (size_t j = 0; j < 3; ++j)
	{
		if (matrix[0][j] == Cross && matrix[1][j] == Cross && matrix[2][j] == Cross)
		{
			return true;
		}
	}

	if (matrix[0][0] == Cross && matrix[1][1] == Cross && matrix[2][2] == Cross)
	{
		return true;
	}

	if (matrix[2][0] == Cross && matrix[1][1] == Cross && matrix[0][2] == Cross)
	{
		return true;
	}

	return false;
}

bool FieldView::botWins()
{
	for (size_t i = 0; i < 3; ++i)
	{
		if (matrix[i][0] == Circle && matrix[i][1] == Circle && matrix[i][2] == Circle)
		{
			return true;
		}
	}

	for (size_t j = 0; j < 3; ++j)
	{
		if (matrix[0][j] == Circle && matrix[1][j] == Circle && matrix[2][j] == Circle)
		{
			return true;
		}
	}

	if (matrix[0][0] == Circle && matrix[1][1] == Circle && matrix[2][2] == Circle)
	{
		return true;
	}

	if (matrix[2][0] == Circle && matrix[1][1] == Circle && matrix[0][2] == Circle)
	{
		return true;
	}

	return false;
}