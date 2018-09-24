#pragma once
//#include "View.h"
//#include "globals.h"
#include "StartView.h"

class ModesView: public View
{
	static const int amountOfOptions = 3;
	string *arrayOfOptions;
	string selectedOption;
	View * nextView();
	int positionOfselectedOption();
public:
	ModesView(Languages l, TypeOfGame t);
	void draw();
	View * handle();
};

