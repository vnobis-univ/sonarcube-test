#pragma once
#include <Windows.h>
#include <vector>
#include "Printer.h"

class GameField
{
	enum class FieldType;
	enum class Direction;
	enum class DrawCellType;
	enum class CellState;
	enum class PartToDraw;

	static int sizeOfField;
	static int cellHorizontalSize;
	static int cellVerticalSize;

	static Printer fieldPrinter;
	static Printer missPrinter;
	static Printer shipPrinter;
	static Printer hitShipPrinter;
	static Printer badPutPrinter;
	static Printer selectedCellPrinter;

	std::vector<char> lettersAboveField;
	COORD whereFieldFrameStarts;
	COORD whereFieldStarts;

	FieldType fieldType;
	CellState** field;
	int numberOfShipsLeft;

public:
	GameField(COORD, FieldType);

	GameField(GameField&);

	~GameField();

	void drawField();

	void placeShip(int, int, int, Direction);

	int placeHit(int, int, bool = true);

	void placeMiss(int, int);

	void drawShip(int, int, int, Direction);

	void drawBadtoPutShip(int, int);

	void drawEmptyCell(int, int);

	bool isOkayToPlaceShip(int, int);

	bool isOkayToPlaceShip(int, int, int, Direction);

	void drawAllShips();

	void drawCurrentCell(int, int, bool);

	void randomShipPlacement();

	bool getIfShipOnCell(int, int) const;

	bool getIfEmptyCell(int, int) const;

	bool getIfHitShipOnCell(int, int) const;

	bool getIfMiss(int, int) const;

	int getNumberOfShipsLeft() const;

	void renewField();

	GameField& operator= (GameField&);

private:
	void drawCell(int, int, DrawCellType);

	Printer getPrinter(DrawCellType drawCellType);

	void drawPartOfCell(int, int, PartToDraw);

	bool checkIfAllShipHit(int, int, int&, int = -1, int = -1);

	void drawAroundSunkShip(int, int, int = -1, int = -1);

public:
	enum class FieldType
	{
		playerField,
		oponentField
	};

	enum class Direction
	{
		horizontal,
		vertical
	};

private:
	enum class DrawCellType
	{
		empty,
		ship,
		hitShip,
		miss,
		badPut
	};

	enum class CellState
	{
		empty,
		ship,
		hitShip,
		miss
	};

	enum class PartToDraw
	{
		leftBorder,
		rightBorder,
		topBorder,
		bottomBorder
	};
};

