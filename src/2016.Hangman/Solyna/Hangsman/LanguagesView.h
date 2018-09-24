#pragma once
#include"View.h"
#include "StartView.h"
#include "functions.h"

class LanguagesView : public View
{
	static const int amountOfOptions = 3;
	string *arrayOfOptions;
	string selectedOption;
	View * nextView();
	int positionOfselectedOption();
public:
	LanguagesView(Languages l,Difficulty d);
	void draw();
	View * handle();
};

