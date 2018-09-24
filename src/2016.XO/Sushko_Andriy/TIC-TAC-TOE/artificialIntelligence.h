#pragma once
#include "FieldView.h"

class artificialIntelligence
{
	FieldView* fld;

	Cell diagonalCell[5];
	unsigned doneMoves;

	int countCrossInCol(int);
	int countCrossInRow(int);
	int countCrossInDiag(int);

	bool freeCellInCol(int);
	bool freeCellInRow(int);
	bool freeCellInDiag(int);

	void makeMoveInCol(int);
	void makeMoveInRow(int);
	void makeMoveInDiag(int);

	void makeMoveInCell(Cell cell);
	bool preventPlayerWin();
public:
	artificialIntelligence(FieldView* p_field);
	
	//looks for two crosses in row/column/diagonal to make move, 
	//else looks for free diagonal cell, else for any free cell
	void makeExpertMove();
	
	//only looks for free diagonal cell, else for any free cell
	void makeNoobMove();
};