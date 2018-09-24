#pragma once
#include "View.h"
#include <iostream>
#include "StartView.h"
#include "ResultView.h"
#include "Highscores.h"

enum Status
{
	Cross, Round, Empty
};

class FieldView : public View
{
	short score;
	Status scheme[3][3];
	short selectX = 0;
	short selectY = 0;
	string complexity;
public:
	FieldView();
	FieldView(short, string);
	void draw();
	View * handle();
	void printAllCell();
	bool isSelected(short, short);
	Status getStatus(short, short)const;
	bool isEmpty(short, short);
	void computerTurn();
	void mediumComputerTurn();
	void smartComputerTurn();
	bool isComputerVictory();
	bool isPlayerVictory();
	bool closeToComputerVictory();
	bool closeToDomination();
};
//Functions
void printField();
void printCell(Status, bool, short, short);