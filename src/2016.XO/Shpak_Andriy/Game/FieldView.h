#pragma once
#include "View.h"
#include "Cell.h"


class FieldView : public View
{
	const size_t gameSize;
	Cell* fieldArr;
	int hoverCell;
	int score;

public:
	FieldView();

	~FieldView();

	View* handle();

	void draw();

	void resetField();

	void gameLogic(bool&, bool&);

private:
	enum class Direction {
		horizontal,
		vertical,
		diagonalRight,
		diagonalLeft
	};

	enum class EdgePositions
	{
		topRow,
		bottomRow,
		leftColumn,
		rightColumn
	};

	bool checkEdge(EdgePositions, int cellToCheck) const;
 
	bool checkIsWinner(cellOptions) const;

	bool chechIsInRow(cellOptions,int , int, Direction) const;

};

