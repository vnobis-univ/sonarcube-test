#pragma once
#include "View.h"
#include "StartView.h"

class ModesView : public View
{
	static const int amountOfOptions = 4;
	string *arrayOfOptions;
	string selectedOption;
	View * nextView();
	int positionOfselectedOption();
public:
	ModesView(Languages l,Difficulty d);
	void draw();
	View * handle();
};

