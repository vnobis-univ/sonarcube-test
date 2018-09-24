#pragma once
#include <iostream>
#include "View.h"
#include "Utils.h"

enum class CellStatus { EMPTY, CROSS, ZERO };
class FieldView : public View
{
private:
	CellStatus field[3][3];
	int selectedCellX ;
	int selectedCellY ;
	int score;
	bool isSelected(int i, int j);
	void printAllCells();
	CellStatus getStatus(int i, int j);	
public:
	FieldView();
	FieldView(int score1);
	void draw();
	View* handle();

	friend bool isCellEmpty(CellStatus helpField[3][3]);
	friend bool whoWins(CellStatus playerStatus, CellStatus field[3][3]);
};
