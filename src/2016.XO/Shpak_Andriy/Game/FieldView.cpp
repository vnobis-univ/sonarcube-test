#include <iostream>
#include <vector>
#include <time.h>
#include <conio.h>
#include <string>
#include "View.h"
#include "ResultView.h"
#include "Navigation.h"
#include "FieldView.h"
#include "Printer.h"
#include "ConsoleManipulators.h"

int newScore;

FieldView::FieldView() : gameSize(3), hoverCell(0), score(0)
{
	fieldArr = new Cell[gameSize * gameSize];

	for (size_t i = 0; i < gameSize * gameSize; ++i)
		fieldArr[i] = Cell();
}

FieldView::~FieldView()
{
	delete[] fieldArr;
}

void FieldView::resetField()
{
	delete[] fieldArr;

	fieldArr = new Cell[gameSize * gameSize];

	for (size_t i = 0; i < gameSize * gameSize; ++i)
		fieldArr[i].setCellState(cellOptions::empty);

	hoverCell = 0;

	draw();
}

void FieldView::draw()
{
	View::draw();

	int sizeOfCell = 5 - gameSize / 4;

	Printer(Color::gray, Color::black).print("  Score: " + std::to_string(score));

	drawEmptyLines(3);

	int widthOfField = sizeOfCell * gameSize + 3 * gameSize - 1;

	// cordinates of left top corner of field (where field starts)
	int cordX;
	int cordY;

	// draw field
	Printer fieldPrinter(Color::aqua, Color::black);

	for (size_t i = 0; i < sizeOfCell * gameSize + gameSize - 1; ++i)
	{
		drawLeftPadding(widthOfField);
		if (i == 0) getCursorPosition(cordX, cordY); // to know where field starts

		bool isLineNeeded = false;
		for (size_t k = 1; k < gameSize; ++k)
			if (i == sizeOfCell * k + k - 1)
			{ 
				isLineNeeded = true;
				break;
			}

		if (!isLineNeeded)
		{
			std::string str(sizeOfCell + 2, ' ');
			for (size_t j = 0; j < gameSize; ++j)
				if (j != gameSize - 1)
					fieldPrinter.print(str + "|");
				else 
					fieldPrinter.print(str);
		}
		else
		{
			std::string str(widthOfField, '-');
			fieldPrinter.print(str);
		}

		drawEmptyLines(1);
	}

	// draw cells
	for (size_t i = 0; i < gameSize; ++i)
		for (size_t j = 0; j < gameSize; ++j)
		{
			std::string* cellToDraw = fieldArr[i * gameSize + j].getHowToDrawCell(sizeOfCell);
			
			// changing printer
			Printer printerForCell;
			
				// color if hover
			if ((i * gameSize + j) == hoverCell)
				printerForCell = Printer(Color::white, Color::blue);
			else
				printerForCell = Printer(Color::white, Color::black);

				// color if cross or zero
			if (fieldArr[i * gameSize + j].getCellState() == cellOptions::cross)
				printerForCell.setClFont(Color::lightBlue);
			else
				printerForCell.setClFont(Color::lightRed);

			// draw in specific cell
			setCursoreAtPosition(cordX + j * (sizeOfCell + 3), cordY + i * (sizeOfCell + 1));

			for (size_t k = 0; k < sizeOfCell; ++k)
			{
				printerForCell.print(" " + cellToDraw[k] + " ");
				int x, y; 
				getCursorPosition(x, y);
				setCursoreAtPosition(x - sizeOfCell - 2, y + 1);
			}
		}
	
	setCursoreAtPosition(0, getConsoleHeight() - 2);

	Printer().print("Press 'x' to end the game");
	drawEmptyLines(1);
}

View* FieldView::handle()
{
	View* nextView = this;
	Button button;

	bool isEndOfGame = false;
	bool isEndOfCurrentGame = false;

	while (true)
	{
		// until one of possible buttons is not presed continue loop
		if (!_kbhit() || !getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::UP: //key up
			if (checkEdge(EdgePositions::topRow, hoverCell)) hoverCell -= gameSize;
			break;

		case Button::DOWN: //key down
			if (checkEdge(EdgePositions::bottomRow, hoverCell)) hoverCell += gameSize;
			break;

		case Button::LEFT: //key left
			if (checkEdge(EdgePositions::leftColumn, hoverCell)) hoverCell -= 1;
			break;

		case Button::RIGHT: //key right
			if (checkEdge(EdgePositions::rightColumn, hoverCell)) hoverCell += 1;
			break;

		case Button::X: //key right
			isEndOfGame = true;
			nextView = new ResultView();
			break;

		case Button::ENTER: // key enter
			if (fieldArr[hoverCell].getCellState() == cellOptions::empty)
			{
				fieldArr[hoverCell].setCellState(cellOptions::cross);

				gameLogic(isEndOfCurrentGame, isEndOfGame);
			}
			break;

		default:
			continue;
		}

		break;
	}


	if (isEndOfCurrentGame || isEndOfGame)
	{
		system("pause");

		if (isEndOfGame)
		{
			nextView = new ResultView();
			newScore = score;
		}
		else
			resetField();

	}

	return nextView;
}

bool FieldView::checkEdge(EdgePositions edgeToCheck, int cellToCheck) const
{
	bool result = true;

	switch (edgeToCheck)
	{
	case EdgePositions::topRow:
		for (size_t i = 0; i < gameSize; ++i)
			if (cellToCheck == i) result = false; //check whether it is not top line
		break;

	case EdgePositions::bottomRow:
		for (size_t i = gameSize * gameSize - gameSize; i < gameSize * gameSize; ++i)
			if (cellToCheck == i) result = false; //check whether it is not bottom line
		break;

	case EdgePositions::leftColumn:
		for (size_t i = 0; i < gameSize * gameSize; i += gameSize)
			if (cellToCheck == i) result = false; //check whether it is not left column
		break;

	case EdgePositions::rightColumn:
		for (size_t i = gameSize - 1; i < gameSize * gameSize; i += gameSize)
			if (cellToCheck == i) result = false; //check whether it is not right column
		break;
	}

	return result;
}

void FieldView::gameLogic(bool& isEndOfCurrentGame, bool& isEndOfGames)
{
	std::vector<int> failedAttemps;
	srand(time(NULL));

	if (checkIsWinner(cellOptions::cross))
	{
		isEndOfCurrentGame = true;
		++score;
	}

	if (!isEndOfCurrentGame)
	{
		while (true)
		{
			// checking whether it is possible to make move

			int attemp = rand() % (gameSize * gameSize);


			if (fieldArr[attemp].getCellState() != cellOptions::empty)
			{
				bool isAlreadyFailed = false;

				for (size_t i = 0; i < failedAttemps.size(); ++i)
					if (failedAttemps[i] == attemp)
					{
						isAlreadyFailed = true;
						break;
					}

				if (!isAlreadyFailed) failedAttemps.push_back(attemp);

				if (failedAttemps.size() == gameSize * gameSize)
				{
					isEndOfCurrentGame = true;
					break;
				}
			}
			else
			{
				fieldArr[attemp].setCellState(cellOptions::zero);
				break;
			}
		}
	}

	draw();


	if (!isEndOfCurrentGame && checkIsWinner(cellOptions::zero))
	{
		isEndOfCurrentGame = true;
		isEndOfGames = true;
	}
}

bool FieldView::checkIsWinner(cellOptions stateForCheck) const
{
	int inRowForWin = gameSize;
	bool win = false;

	//cheking whether someone win 
	for (size_t i = 0; i < gameSize * gameSize; ++i)
	{
		if (fieldArr[i].getCellState() == stateForCheck)
		{
			win = chechIsInRow(stateForCheck, i, inRowForWin, Direction::horizontal);

			if (!win) win = chechIsInRow(stateForCheck, i, inRowForWin, Direction::vertical);

			if (!win) win = chechIsInRow(stateForCheck, i, inRowForWin, Direction::diagonalRight);

			if (!win) win = chechIsInRow(stateForCheck, i, inRowForWin, Direction::diagonalLeft);
		
			if (win) break;
		}
	}

	return win;
}

bool FieldView::chechIsInRow(cellOptions stateForCheck, int index, int inRowForWin, Direction direction) const
{
	int counter = 1;
	int directionToInt;

	switch (direction)
	{
	case Direction::horizontal:
		directionToInt = 1;
		break;

	case Direction::vertical:
		directionToInt = gameSize;
		break;

	case Direction::diagonalRight:
		directionToInt = gameSize + 1;
		break;

	case Direction::diagonalLeft:
		directionToInt = gameSize - 1;
		break;
	}

	int checkIndex = index;

	while (true)
	{
		bool isInRowPossible = true;
		
		switch (direction)
		{
		case Direction::horizontal: //check if it is not right column
			if (!checkEdge(EdgePositions::rightColumn, checkIndex)) isInRowPossible = false;
			break;

		case Direction::vertical: //check if it is not bottom line
			if (!checkEdge(EdgePositions::bottomRow, checkIndex)) isInRowPossible = false;
			break;

		case Direction::diagonalRight: //check if it is not right column or bottom line
			if (!checkEdge(EdgePositions::rightColumn, checkIndex) || !checkEdge(EdgePositions::bottomRow, index)) isInRowPossible = false;
			break;

		case Direction::diagonalLeft: //check if it is not left column or bottom line
			if (!checkEdge(EdgePositions::leftColumn, checkIndex) || !checkEdge(EdgePositions::bottomRow, index)) isInRowPossible = false;
			break;
		}

		checkIndex = index + directionToInt * counter;

		if (isInRowPossible)
		{
			if (fieldArr[checkIndex].getCellState() == stateForCheck)
			{
				++counter;

				if (counter == inRowForWin)
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
		else 
		{
			return false;
		}
	}

}
