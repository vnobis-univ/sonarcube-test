#pragma once
#include "StartView.h"

class LanguagesView:public View
{
	static const int amountOfOptions = 3;
	string *arrayOfOptions;
	string selectedOption;
	View * nextView();
	int positionOfselectedOption();
public:
	LanguagesView(Languages l, TypeOfGame t);
	void draw();
	View * handle();
};

