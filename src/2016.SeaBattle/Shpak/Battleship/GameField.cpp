#include "GameField.h"
#include "LanguageManipulator.h"
#include "ConsoleManipulators.h"
#include "FilesManipulator.h"
#include "Printer.h"
#include <string>
#include <time.h>
#include <vector>
#include <iostream>

int GameField::sizeOfField = 10;
int GameField::cellHorizontalSize = 3;
int GameField::cellVerticalSize = 2;

Printer GameField::fieldPrinter = Printer(Color::yellow, Color::black);
Printer GameField::missPrinter = Printer(Color::yellow, Color::black);
Printer GameField::shipPrinter = Printer(Color::aqua, Color::black);
Printer GameField::hitShipPrinter = Printer(Color::red, Color::black);
Printer GameField::badPutPrinter = Printer(Color::red, Color::black);
Printer GameField::selectedCellPrinter = Printer(Color::yellow, Color::purple);

GameField::GameField(COORD whereFieldFrameStarts, FieldType fieldType) :
	whereFieldFrameStarts(whereFieldFrameStarts),
	whereFieldStarts({ whereFieldFrameStarts.X + 2, whereFieldFrameStarts.Y + 2 }), // 2 chars for letters and digits 
	fieldType(fieldType)
{
	LanguageManipulator().getLettersAboveField(lettersAboveField);

	field = new CellState*[sizeOfField];

	for (size_t i = 0; i < sizeOfField; ++i)
	{
		field[i] = new CellState[sizeOfField];
	}

	for (size_t i = 0; i < sizeOfField; ++i)
	{
		for (size_t j = 0; j < sizeOfField; ++j)
		{
			field[i][j] = CellState::empty;
		}
	}

	numberOfShipsLeft = 4 + 3 + 2 + 1; // number of all ships
}

GameField::~GameField()
{
	for (size_t i = 0; i < sizeOfField; ++i)
	{
		delete[] field[i];
	}

	delete[] field;
}

GameField::GameField(GameField& toCopy) :
	whereFieldFrameStarts(whereFieldFrameStarts),
	whereFieldStarts({ whereFieldFrameStarts.X + 2, whereFieldFrameStarts.Y + 2 }), // 2 chars for letters and digits 
	fieldType(fieldType)
{
	LanguageManipulator().getLettersAboveField(lettersAboveField);

	field = new CellState*[sizeOfField];

	for (size_t i = 0; i < sizeOfField; ++i)
	{
		field[i] = new CellState[sizeOfField];
	}

	for (size_t i = 0; i < sizeOfField; ++i)
	{
		for (size_t j = 0; j < sizeOfField; ++j)
		{
			field[i][j] = toCopy.field[i][j];
		}
	}

	numberOfShipsLeft = 4 + 3 + 2 + 1; // number of all ships
}

GameField& GameField::operator= (GameField& toCopy)
{
	if (this == &toCopy)
		return *this;

	GameField::~GameField();

	LanguageManipulator().getLettersAboveField(lettersAboveField);

	field = new CellState*[sizeOfField];

	for (size_t i = 0; i < sizeOfField; ++i)
	{
		field[i] = new CellState[sizeOfField];
	}

	for (size_t i = 0; i < sizeOfField; ++i)
	{
		for (size_t j = 0; j < sizeOfField; ++j)
		{
			field[i][j] = toCopy.field[i][j];
		}
	}

	numberOfShipsLeft = toCopy.numberOfShipsLeft; // number of all ships

	whereFieldFrameStarts = toCopy.whereFieldFrameStarts;

	whereFieldStarts = { toCopy.whereFieldFrameStarts.X + 2, toCopy.whereFieldFrameStarts.Y + 2 };

	fieldType = toCopy.fieldType;

	return *this;
}

void GameField::renewField()
{
	for (size_t i = 0; i < sizeOfField; ++i)
	{
		for (size_t j = 0; j < sizeOfField; ++j)
		{
			field[i][j] = CellState::empty;
		}
	}

	numberOfShipsLeft = 4 + 3 + 2 + 1; // number of all ships
}

void GameField::drawField()
{
	std::vector<std::string> field;

	FilesManipulator().getHowToDrawField(field);

	size_t whichLetter = 0;

	for (size_t i = 0; i < field.size(); ++i)
	{
		setCursoreAtPosition(whereFieldFrameStarts.X, whereFieldFrameStarts.Y + i);

		if (i >= 2 && i % 2 == 0 && whichLetter < 10) // starting from third position in vec need to draw letters
			fieldPrinter << lettersAboveField[whichLetter++] << field[i];
		else
			fieldPrinter << ' ' << field[i];
	}
}

void GameField::placeShip(int index_i, int index_j, int size, Direction direction)
{
	switch (direction)
	{
	case GameField::Direction::horizontal:
		for (size_t k = 0; k < size; ++k)
		{
			field[index_i][index_j + k] = CellState::ship;
		}
		break;
	case GameField::Direction::vertical:
		for (size_t k = 0; k < size; ++k)
		{
			field[index_i + k][index_j] = CellState::ship;
		}
		break;
	default:
		break;
	}
}

void GameField::drawShip(int index_i, int index_j, int size, Direction direction)
{
	switch (direction)
	{
	case Direction::horizontal:
		for (size_t k = 0; k < size; ++k)
		{
			drawCell(index_i, index_j + k, DrawCellType::ship);
		}

		break;

	case Direction::vertical:
		for (size_t k = 0; k < size; ++k)
		{
			drawCell(index_i + k, index_j, DrawCellType::ship);
		}

		break;
	}
}

int GameField::placeHit(int index_i, int index_j, bool isNeedToCheckForSunk)
{
	field[index_i][index_j] = CellState::hitShip;

	drawCell(index_i, index_j, DrawCellType::hitShip);

	if (isNeedToCheckForSunk)
	{
		int sunkShipSize = 0;

		if (checkIfAllShipHit(index_i, index_j, sunkShipSize))
		{
			--numberOfShipsLeft;
			drawAroundSunkShip(index_i, index_j);

			return sunkShipSize;
		}
	}

	return -1;
}

void GameField::placeMiss(int index_i, int index_j)
{
	field[index_i][index_j] = CellState::miss;

	drawCell(index_i, index_j, DrawCellType::miss);

	if (fieldType != FieldType::playerField)
	{
		drawPartOfCell(index_i + 1, index_j, PartToDraw::topBorder);
	}
}

void GameField::drawBadtoPutShip(int index_i, int index_j)
{
	drawCell(index_i, index_j, DrawCellType::badPut);
}

void GameField::drawEmptyCell(int index_i, int index_j)
{
	drawCell(index_i, index_j, DrawCellType::empty);
}

void GameField::drawCell(int index_i, int index_j, DrawCellType drawCellType)
{
	Printer printer = getPrinter(drawCellType);

	if (field[index_i][index_j] == CellState::miss)
	{
		setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize + 1, whereFieldStarts.Y + index_i * cellVerticalSize);
		printer << ",,";
	}
	else
	{
		setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize + 1, whereFieldStarts.Y + index_i * cellVerticalSize - 1);

		printer << "__";

		for (size_t k = 0; k < 2; ++k)
		{
			setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize, whereFieldStarts.Y + index_i * cellVerticalSize + k);


			if (k == 0)

				printer << "|  |";
			else
				printer << "|__|";

		}
	}
}


bool GameField::isOkayToPlaceShip(int index_i, int index_j)
{
	if (field[index_i][index_j] != CellState::empty)
		return false;


	for (int i = -1; i <= 1; ++i)
	{
		if (index_i + i < 0 || index_i + i >= sizeOfField)
			continue;

		for (int j = -1; j <= 1; ++j)
		{
			if (index_j + j < 0 || index_j + j >= sizeOfField)
				continue;


			if (field[index_i + i][index_j + j] == CellState::ship)
			{
				return false;
			}
		}
	}

	return true;
}

bool GameField::isOkayToPlaceShip(int index_i, int index_j, int size, Direction direction)
{
	switch (direction)
	{
	case GameField::Direction::horizontal:
		for (size_t k = 0; k < size; ++k)
		{
			if (index_j + k >= 10)
				return false;

			if (!isOkayToPlaceShip(index_i, index_j + k))
				return false;
		}
		break;

	case GameField::Direction::vertical:
		for (size_t k = 0; k < size; ++k)
		{
			if (index_i + k >= 10)
				return false;

			if (!isOkayToPlaceShip(index_i + k, index_j))
				return false;
		}
		break;
	}

}

void GameField::drawAllShips()
{
	for (size_t i = 0; i < sizeOfField; ++i)
	{
		for (size_t j = 0; j < sizeOfField; ++j)
		{
			if (field[i][j] == CellState::ship)
			{
				drawCell(i, j, DrawCellType::ship);
			}
		}
	}
}

void GameField::drawCurrentCell(int index_i, int index_j, bool isNewSelectedCell)
{
	if (isNewSelectedCell)
	{
		// picking printer
		Printer printer = selectedCellPrinter;

		if (field[index_i][index_j] != CellState::ship)
			printer.setClFont(getPrinter(static_cast<DrawCellType>(field[index_i][index_j])).getClFont());

		for (size_t k = 0; k < 2; ++k)
		{
			setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize + 1, whereFieldStarts.Y + index_i * cellVerticalSize + k);

			if (k == 0)
				if (field[index_i][index_j] == CellState::miss)
					printer << ",,";
				else
					printer << "  ";
			else
				printer << "__";
		}
	}
	else
	{
		if (field[index_i][index_j] == CellState::empty || field[index_i][index_j] == CellState::ship)
		{
			if (field[index_i][index_j] == CellState::ship)
				drawCell(index_i, index_j, DrawCellType::empty);
			else
				drawCell(index_i, index_j, static_cast<DrawCellType>(field[index_i][index_j]));
		}

		if (index_i - 1 >= 0)
			drawPartOfCell(index_i - 1, index_j, PartToDraw::bottomBorder);

		if (index_j - 1 >= 0)
			drawPartOfCell(index_i, index_j - 1, PartToDraw::rightBorder);

		if (index_j + 1 < 10)
			drawPartOfCell(index_i, index_j + 1, PartToDraw::leftBorder);

		if (index_i < 10)
			drawPartOfCell(index_i + 1, index_j, PartToDraw::topBorder);

		if (field[index_i][index_j] != CellState::empty && field[index_i][index_j] != CellState::ship)
			drawCell(index_i, index_j, static_cast<DrawCellType>(field[index_i][index_j]));
	}
}

Printer GameField::getPrinter(DrawCellType drawCellType)
{
	switch (drawCellType)
	{
	case GameField::DrawCellType::empty:
		return fieldPrinter;

	case GameField::DrawCellType::ship:
		return shipPrinter;

	case GameField::DrawCellType::hitShip:
		return hitShipPrinter;

	case GameField::DrawCellType::miss:
		return missPrinter;

	case GameField::DrawCellType::badPut:
		return badPutPrinter;
	}
}

void GameField::drawPartOfCell(int index_i, int index_j, PartToDraw partToDraw)
{
	// getting printer
	Printer printer;

	if (partToDraw == PartToDraw::topBorder && index_i == 10)
	{
		printer = getPrinter(static_cast<DrawCellType>(field[index_i - 1][index_j]));

		if (field[index_i - 1][index_j] == CellState::ship)
			printer = fieldPrinter;
	}
	else
	{
		printer = getPrinter(static_cast<DrawCellType>(field[index_i][index_j]));

		if (field[index_i][index_j] == CellState::ship)
			printer = fieldPrinter;
	}

	// drawing
	switch (partToDraw)
	{
	case GameField::PartToDraw::leftBorder:
		for (size_t k = 0; k < 2; ++k)
		{
			setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize, whereFieldStarts.Y + index_i * cellVerticalSize + k);

			if (k == 0)
				printer << "|";
			else
				printer << "|";
		}
		break;

	case GameField::PartToDraw::rightBorder:
		for (size_t k = 0; k < 2; ++k)
		{
			setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize + 3, whereFieldStarts.Y + index_i * cellVerticalSize + k);

			if (k == 0)
				printer << "|";
			else
				printer << "|";
		}
		break;

	case GameField::PartToDraw::topBorder:
		setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize + 1, whereFieldStarts.Y + (index_i - 1) * cellVerticalSize + 1);

		printer << "__";
		break;

	case GameField::PartToDraw::bottomBorder:
		setCursoreAtPosition(whereFieldStarts.X + index_j * cellHorizontalSize + 1, whereFieldStarts.Y + index_i * cellVerticalSize + 1);

		printer << "__";
		break;
	}
}

void GameField::randomShipPlacement()
{
	srand(time(NULL));

	for (size_t i = 4; i >= 1; --i) // ship size
	{
		for (size_t j = 1; j <= 5 - i; ++j) // number of ships
		{
			Direction direction = static_cast<Direction>(rand() % 2);

			std::vector<std::pair<int, int>> vecOfPossiblePossitions;

			for (size_t ii = 0; ii < sizeOfField; ++ii)
			{
				for (size_t jj = 0; jj < sizeOfField; ++jj)
				{
					if (isOkayToPlaceShip(ii, jj, i, direction))
					{
						vecOfPossiblePossitions.push_back(std::make_pair(ii, jj));
					}
				}
			}

			std::pair<int, int> toPlace = vecOfPossiblePossitions[rand() % vecOfPossiblePossitions.size()];

			placeShip(toPlace.first, toPlace.second, i, direction);
		}
	}
}

bool GameField::checkIfAllShipHit(int index_i, int index_j, int& sunkShipSize, int fromWhichCalled_i, int fromWhichCalled_j)
{
	// recursive function

	++sunkShipSize;

	for (int i = -1; i <= 1; ++i)
	{
		if (index_i + i < 0 || index_i + i >= 10) //check for edge of field
			continue;

		for (int j = -1; j <= 1; ++j)
		{

			if (index_j + j < 0 || index_j + j >= 10) // check for edge of field
				continue;

			if (index_i + i == fromWhichCalled_i && index_j + j == fromWhichCalled_j) // in order not to cause infinite recursive call
				continue;

			if ((j == -1 && i == -1) || (j == -1 && i == 1) || (j == 1 && i == -1) || (j == 1 && i == 1) || (j == 0 && i == 0))
			{
				// exclude pairs (-1, -1), (-1, 1), (1, -1), (1, 1) and (0, 0)
				continue;
			}

			// check for non hit ship
			if (field[index_i + i][index_j + j] == CellState::ship)
			{
				return false;
			}
			else if (field[index_i + i][index_j + j] == CellState::hitShip)
			{
				if (!checkIfAllShipHit(index_i + i, index_j + j, sunkShipSize, index_i, index_j)) // recursive call of function
					return false;
			}
		}
	}

	return true;
}

void GameField::drawAroundSunkShip(int index_i, int index_j, int fromWhichCalled_i, int fromWhichCalled_j)
{
	// recursive function


	for (int i = -1; i <= 1; ++i)
	{
		if (index_i + i < 0 || index_i + i >= 10) //check for edge of field
			continue;

		for (int j = -1; j <= 1; ++j)
		{

			if (index_j + j < 0 || index_j + j >= 10) // check for edge of field
				continue;

			if (index_i + i == fromWhichCalled_i && index_j + j == fromWhichCalled_j) // in order not to cause infinite recursive call
				continue;

			if (j == 0 && i == 0) // exclude pair (0, 0)	
				continue;


			// placing "miss" around sunk ship
			if (field[index_i + i][index_j + j] == CellState::empty)
			{
				placeMiss(index_i + i, index_j + j);
			}
			else if (field[index_i + i][index_j + j] == CellState::hitShip)
			{
				drawAroundSunkShip(index_i + i, index_j + j, index_i, index_j); // recursive call of function
			}
		}
	}
}

bool GameField::getIfShipOnCell(int index_i, int index_j) const
{
	return field[index_i][index_j] == CellState::ship;
}

bool GameField::getIfEmptyCell(int index_i, int index_j) const
{
	return field[index_i][index_j] == CellState::empty;
}

bool GameField::getIfHitShipOnCell(int index_i, int index_j) const
{
	return field[index_i][index_j] == CellState::hitShip;
}

bool GameField::getIfMiss(int index_i, int index_j) const
{
	return field[index_i][index_j] == CellState::miss;
}

int GameField::getNumberOfShipsLeft() const
{
	return numberOfShipsLeft;
}
