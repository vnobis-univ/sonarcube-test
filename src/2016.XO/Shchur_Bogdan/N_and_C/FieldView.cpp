#include "FieldView.h"
#include <conio.h>

Printer mainpan(ConsoleColor::LightGray, ConsoleColor::Red);
Printer gappan(ConsoleColor::LightGray, ConsoleColor::LightGray);
short turnCounter = 0;

FieldView::FieldView(): score(0)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			scheme[i][j] = Empty;
		}
	}
}
FieldView::FieldView(short s, string c) : score(s), complexity(c)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			scheme[i][j] = Empty;
		}
	}
}
void FieldView::draw()
{
	printTextOnTheCenter(0, "Your score: " + to_string(score), mainpan);
	printTextOnTheCenter(1, "Your complexity: " + complexity, mainpan);
	printField();
	printAllCell();
}
View* FieldView::handle()
{
	short nx = selectX;
	short ny = selectY;
	View* nextView = this;
	switch (_getch())
	{
	case 80://Down key
		++nx;
		break;
	case 72://Upper key
		--nx;
		break;
	case 75://Left key
		--ny;
		break;
	case 77://Right key
		++ny;
		break;
	case 27://Esc
		nextView = new StartView;
		break;
	case 13:
		if (isEmpty(nx, ny))
		{
			scheme[nx][ny] = Cross;
			++turnCounter;
			if (turnCounter <= 4)
			{
				if (complexity == "Easy")
				{
					computerTurn();
				}
				else if (complexity == "Medium")
				{
					mediumComputerTurn();
				}
				else if(complexity == "Hard")
				{
					smartComputerTurn();
				}
			}
		}
		if (isPlayerVictory())
		{
			++score;
			nextView = new FieldView(score, complexity);
			turnCounter = 0;
		}
		else if (isComputerVictory())
		{
			printAllCell();
			printTextOnTheCenter(2, "You lose:(", mainpan);
			printTextOnTheCenter(22, "Press Enter to continue", mainpan);
			printTextOnTheCenter(23, "                 ", mainpan);
			bool exit = false;
			while (!exit)
			{
				switch (_getch())
				{
				case 13://Enter
					nextView = new ResultView(isInTable(score), score);
					turnCounter = 0;
					exit = true;
				}
			}
		}
		if (turnCounter > 4 && !isPlayerVictory() && !isComputerVictory())
		{
			nextView = new FieldView(score, complexity);
			turnCounter = 0;
		}
		break;
	}
	if (nx >= 0 && nx < 3)
	{
		selectX = nx;
	}
	if (ny >= 0 && ny < 3)
	{
		selectY = ny;
	}
	return nextView;
}
void printField()
{
	printTextOnTheCenter(3,  "----------------------", mainpan);
	printTextOnTheCenter(4,  "|      |      |      |", mainpan);
	printTextOnTheCenter(5,  "|      |      |      |", mainpan);
	printTextOnTheCenter(6,  "|      |      |      |", mainpan);
	printTextOnTheCenter(7,  "|      |      |      |", mainpan);
	printTextOnTheCenter(8,  "|      |      |      |", mainpan);
	printTextOnTheCenter(9,  "----------------------", mainpan);
	printTextOnTheCenter(10, "|      |      |      |", mainpan);
	printTextOnTheCenter(11, "|      |      |      |", mainpan);
	printTextOnTheCenter(12, "|      |      |      |", mainpan);
	printTextOnTheCenter(13, "|      |      |      |", mainpan);
	printTextOnTheCenter(14, "|      |      |      |", mainpan);
	printTextOnTheCenter(15, "----------------------", mainpan);
	printTextOnTheCenter(16, "|      |      |      |", mainpan);
	printTextOnTheCenter(17, "|      |      |      |", mainpan);
	printTextOnTheCenter(18, "|      |      |      |", mainpan);
	printTextOnTheCenter(19, "|      |      |      |", mainpan);
	printTextOnTheCenter(20, "|      |      |      |", mainpan);
	printTextOnTheCenter(21, "----------------------", mainpan);
	printTextOnTheCenter(23, "Press Esc to exit", mainpan);
}
Status FieldView::getStatus(short i, short j)const
{
	return scheme[i][j];
}
void FieldView::printAllCell()
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			Status cell = getStatus(i, j);
			printCell(cell, isSelected(i, j), i, j);
		}
	}
}
bool FieldView::isSelected(short x, short y)
{
	return selectX == x && selectY == y;
}
void printCell(Status c, bool isSelect, short i, short j)
{
	string line1;
	string line2;
	string line3;
	string line4;
	string line5;
	Printer print;
	Printer empty(isSelect ? ConsoleColor::DarkGray : ConsoleColor::LightGray, ConsoleColor::LightGray);
	Printer cross(isSelect ? ConsoleColor::DarkGray : ConsoleColor::LightGray, ConsoleColor::Blue);
	Printer round(isSelect ? ConsoleColor::DarkGray : ConsoleColor::LightGray, ConsoleColor::Green);
	switch (c)
	{
	case Empty:
		line1 = "      "; 
		line2 = "      "; 
		line3 = "      "; 
		line4 = "      "; 
		line5 = "      ";
		print = empty;
		break;
	case Cross:
		line1 = "\\    /";
		line2 = " \\  / ";
		line3 = "  XX  ";
		line4 = " /  \\ ";
		line5 = "/    \\";
		print = cross;
		break;
	case Round:
		line1 = "  /\\  ";
		line2 = " /  \\ ";
		line3 = "<    >";
		line4 = " \\  / ";
		line5 = "  \\/  ";
		print = round;
		break;
	}
	short startPosition = (consoleWidth - 20) / 2 + (consoleWidth - 20) % 2;
	short x = startPosition + 7 * j;
	short y = 4 + 6 * i;
	setCursor(x, y);
	print << line1;
	setCursor(x, y + 1);
	print << line2;
	setCursor(x, y + 2);
	print << line3;
	setCursor(x, y + 3);
	print << line4;
	setCursor(x, y + 4);
	print << line5;
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
void FieldView::computerTurn()
{
	bool isPlaced = false;
	while (!isPlaced)
	{
		short compX = rand() % 3;
		short compY = rand() % 3;
		if (scheme[compX][compY] == Empty)
		{
			scheme[compX][compY] = Round;
			isPlaced = true;
		}
	}
}
void FieldView::mediumComputerTurn()
{
	bool isPlaced = false;
	if (closeToComputerVictory())
	{
		isPlaced = true;
	}
	else
	{
		bool is = false;
		while (!is)
		{
			short compX = rand() % 3;
			short compY = rand() % 3;
			if (scheme[compX][compY] == Empty)
			{
				scheme[compX][compY] = Round;
				is = true;
				isPlaced = true;
			}
		}
	}
}
void FieldView::smartComputerTurn()
{
	bool isPlaced = false;
	while (!isPlaced)
	{
		if (scheme[1][1] == Empty)
		{
			scheme[1][1] = Round;
			isPlaced = true;
		}
		else
		{
			if (closeToDomination())
			{
				isPlaced = true;
			}
			else
			{
	
				if (scheme[0][0] == Cross && scheme[2][2] == Cross)
				{
					scheme[2][1] = Round;
					isPlaced = true;
				}
				else if (scheme[2][0] == Cross && scheme[0][2] == Cross)
				{
					scheme[0][1] = Round;
					isPlaced = true;
				}
				else if (scheme[0][0] == Empty)
				{
					scheme[0][0] = Round;
					isPlaced = true;
				}
				else if (scheme[0][2] == Empty)
				{
					scheme[0][2] = Round;
					isPlaced = true;
				}
				else if (scheme[2][0] == Empty)
				{
					scheme[2][0] = Round;
					isPlaced = true;
				}
				else if (scheme[2][2] == Empty)
				{
					scheme[2][2] = Round;
					isPlaced = true;
				}
				else
				{
					bool is = false;
					while (!is)
					{
						short compX = rand() % 3;
						short compY = rand() % 3;
						if (scheme[compX][compY] == Empty)
						{
							scheme[compX][compY] = Round;
							is = true;
							isPlaced = true;
						}
					}
				}
			}
		}
	}
}
bool FieldView::isPlayerVictory()
{
		for (int i = 0; i < 3; ++i)
		{
			if (scheme[i][0] == Cross && scheme[i][1] == Cross && scheme[i][2] == Cross)
			{
				return true;
			}
		}
		for (int j = 0; j < 3; ++j)
		{
			if (scheme[0][j] == Cross && scheme[1][j] == Cross && scheme[2][j] == Cross)
			{
				return true;
			}
		}
		if (scheme[0][0] == Cross && scheme[1][1] == Cross && scheme[2][2] == Cross)
		{
			return true;
		}
		if (scheme[0][2] == Cross && scheme[1][1] == Cross && scheme[2][0] == Cross)
		{
			return true;
		}
	return false;
}
bool FieldView::closeToComputerVictory()
{
	bool isClose = false;
	for (int i = 0; i < 3; ++i)
	{
		if (scheme[i][0] == Round && scheme[i][1] == Round && scheme[i][2] == Empty)
		{
			scheme[i][2] = Round;
			isClose = true;
			break;
		}
		else if (scheme[i][1] == Round && scheme[i][2] == Round && scheme[i][0] == Empty)
		{
			scheme[i][0] = Round;
			isClose = true;
			break;
		}
		else if (scheme[0][i] == Round && scheme[1][i] == Round && scheme[2][i] == Empty)
		{
			scheme[2][i] = Round;
			isClose = true;
			break;
		}
		else if (scheme[1][i] == Round && scheme[2][i] == Round && scheme[0][i] == Empty)
		{
			scheme[0][i] = Round;
			isClose = true;
			break;
		}
		else if (scheme[0][0] == Round && scheme[1][1] == Round && scheme[2][2] == Empty)
		{
			scheme[2][2] = Round;
			isClose = true;
			break;
		}
		else if (scheme[1][1] == Round && scheme[2][2] == Round && scheme[0][0] == Empty)
		{
			scheme[0][0] = Round;
			isClose = true;
			break;
		}
		else if (scheme[0][2] == Round && scheme[1][1] == Round && scheme[2][0] == Empty)
		{
			scheme[2][0] = Round;
			isClose = true;
			break;
		}
		else if (scheme[2][0] == Round && scheme[1][1] == Round && scheme[0][2] == Empty)
		{
			scheme[0][2] = Round;
			isClose = true;
			break;
		}
	}
	return isClose;
}
bool FieldView::closeToDomination()
{
	bool isClose = false;
	for (int i = 0; i < 3; ++i)
	{
		if ((scheme[i][0] == Round && scheme[i][1] == Round && scheme[i][2] == Empty) || 
			(scheme[i][0] == Cross && scheme[i][1] == Cross && scheme[i][2] == Empty))
		{
			scheme[i][2] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[i][1] == Round && scheme[i][2] == Round && scheme[i][0] == Empty) ||
			(scheme[i][1] == Cross && scheme[i][2] == Cross && scheme[i][0] == Empty))
		{
			scheme[i][0] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[i][0] == Round && scheme[i][2] == Round && scheme[i][1] == Empty) ||
			(scheme[i][0] == Cross && scheme[i][2] == Cross && scheme[i][1] == Empty))
		{
			scheme[i][1] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[0][i] == Round && scheme[1][i] == Round && scheme[2][i] == Empty) ||
			(scheme[0][i] == Cross && scheme[1][i] == Cross && scheme[2][i] == Empty))
		{
			scheme[2][i] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[1][i] == Round && scheme[2][i] == Round && scheme[0][i] == Empty) || 
			(scheme[1][i] == Cross && scheme[2][i] == Cross && scheme[0][i] == Empty))
		{
			scheme[0][i] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[0][i] == Round && scheme[2][i] == Round && scheme[1][i] == Empty) ||
			(scheme[0][i] == Cross && scheme[2][i] == Cross && scheme[1][i] == Empty))
		{
			scheme[1][i] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[0][0] == Round && scheme[1][1] == Round && scheme[2][2] == Empty) || 
			(scheme[0][0] == Cross && scheme[1][1] == Cross && scheme[2][2] == Empty))
		{
			scheme[2][2] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[1][1] == Round && scheme[2][2] == Round && scheme[0][0] == Empty) || 
			(scheme[1][1] == Cross && scheme[2][2] == Cross && scheme[0][0] == Empty))
		{
			scheme[0][0] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[0][0] == Round && scheme[2][2] == Round && scheme[1][1] == Empty) ||
			(scheme[0][0] == Cross && scheme[2][2] == Cross && scheme[1][1] == Empty))
		{
			scheme[1][1] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[0][2] == Round && scheme[1][1] == Round && scheme[2][0] == Empty) || 
			(scheme[0][2] == Cross && scheme[1][1] == Cross && scheme[2][0] == Empty))
		{
			scheme[2][0] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[2][0] == Round && scheme[1][1] == Round && scheme[0][2] == Empty) || 
			(scheme[2][0] == Cross && scheme[1][1] == Cross && scheme[0][2] == Empty))
		{
			scheme[0][2] = Round;
			isClose = true;
			break;
		}
		else if ((scheme[2][0] == Round && scheme[0][2] == Round && scheme[1][1] == Empty) ||
			(scheme[2][0] == Cross && scheme[0][2] == Cross && scheme[1][1] == Empty))
		{
			scheme[1][1] = Round;
			isClose = true;
			break;
		}
	}
	return isClose;
}
bool FieldView::isComputerVictory()
{
	for (int i = 0; i < 3; ++i)
	{
		if (scheme[i][0] == Round && scheme[i][1] == Round && scheme[i][2] == Round)
		{
			return true;
		}
	}
	for (int j = 0; j < 3; ++j)
	{
		if (scheme[0][j] == Round && scheme[1][j] == Round && scheme[2][j] == Round)
		{
			return true;
		}
	}
	if (scheme[0][0] == Round && scheme[1][1] == Round && scheme[2][2] == Round)
	{
		return true;
	}
	if (scheme[0][2] == Round && scheme[1][1] == Round && scheme[2][0] == Round)
	{
		return true;
	}
	return false;
}