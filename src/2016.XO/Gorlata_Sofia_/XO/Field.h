#pragma once
#include "View.h"

#include "Cell.h"

class Field : public View
{
private:
	enum class State{ playersMove, compMove };
	
	State state;

	Cell field[3][3];
	Cell selected;
	int playerScore;
	

	void makeMove();

	bool checkGameOver(bool& state);
	void clearField();
public:
	Field();
	void draw();
	View* handle();


};
