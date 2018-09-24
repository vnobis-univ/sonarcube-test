#pragma once
#include "View.h"
#include "CellState.h"

class FieldView	: public View
{
private:
	int score;
	CellState array[3][3];
	int x;
	int y;
	void printFieldCells();
public:
	FieldView();
	FieldView(int score);
	void draw();
	View* handle();
};

