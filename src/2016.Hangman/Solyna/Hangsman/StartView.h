#pragma once
#include "View.h"
#include "Printer.h"
#include "HighScoresView.h"

class StartView : public View
{
	const static int amountOfOptions = 4;
	string *arrayOfOptions;
	string selectedOption;
	View * nextView();
	int positionOfselectedOption();
public:
	StartView(Languages l,Difficulty d);
	void draw();
	View * handle();
};

