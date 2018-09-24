#pragma once
#include "View.h"
#include <iostream>
#include "StartView.h"
#include "ResultView.h"
#include "HighScores.h"

enum Status
{
	Cross,Circle,Empty
};

class FieldView : public View
{
private:
	short score;
	Status matrix[3][3];
	short selectedX = 0;
	short selectedY = 0;
public:
	FieldView();
	FieldView(short);
	void draw();
	View *handle();
	void printCells();
	bool isSelected(short, short);
	Status getStatus(short, short)const;
	bool isEmpty(short, short);
	void botTurn();
	bool botWins();
	bool playerWins();
};

void printField();
void printCell(Status, bool, short, short);