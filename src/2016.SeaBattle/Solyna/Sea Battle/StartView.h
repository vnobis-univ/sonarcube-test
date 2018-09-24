#pragma once
#include "View.h"
#include "globals.h"
#include "HighScoresView.h"
#include <string>

using namespace std;

class StartView: public View
{
	const static int amountOfOptions = 4;
	string *arrayOfOptions;
	string selectedOption;
	View * nextView();
	int positionOfselectedOption();
public:
	StartView(Languages l, TypeOfGame t);
	void draw();
	View * handle();
};

