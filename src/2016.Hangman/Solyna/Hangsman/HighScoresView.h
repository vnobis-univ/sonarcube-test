#pragma once
#include "View.h"
#include "Player.h"
#include <fstream>
#include "functions.h"
#include "Printer.h"
class HighScoresView : public View
{
	Player arrayOfEasyPlayers[7];
	Player arrayOfMediumPlayers[7];
	Player arrayOfHardPlayers[7];
	void printingArrays(Player * array, int size, int xCursor, int yCursor);
public:
	HighScoresView(Languages l, Difficulty d);
	void draw();
	View* handle();
};

