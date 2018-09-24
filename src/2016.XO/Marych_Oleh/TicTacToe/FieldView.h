#pragma once
#include "View.h"
#include <iostream>
#include "StartView.h"
#include "ResultView.h"
#include "HighScoresView.h"

enum Status
{
	Cross, Round, Empty
};

class FieldView : public View
{
	int score;
	Status scheme[3][3];
	short selectX = 0;
	short selectY = 0;
public:
	FieldView();
	FieldView(short);
	void draw();
	View * handle();
	void printAllCell();
	bool isSelected(short, short);
	Status getStatus(short, short)const;
	bool isEmpty(short, short);
	void computerTurn();
	bool isComputerVictory();
	bool isPlayerVictory();
};

void printField();
void printCell(Status, bool, short, short);