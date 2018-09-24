#pragma once
#include "globals.h"
//#include "Printer.h"

enum class CellStatus
{
	Empty,
	Hit,
	Missed,
	HasShip,
	NearShip
};
class Cell
{
	static const int size = sizeOfCell;
	unsigned red;
	unsigned green; // for RGB
	unsigned blue;
	CellStatus status;

public:
	Cell(unsigned _red, unsigned _green, unsigned _blue);
	void setStatus(CellStatus _status);
	void drawCell(int coordinateX, int coordinateY);
	void changeColor();
	void backToColor();
	CellStatus getStatus();
	Cell();
	~Cell();
};

