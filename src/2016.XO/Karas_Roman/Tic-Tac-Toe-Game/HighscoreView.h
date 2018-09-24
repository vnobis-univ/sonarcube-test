#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include "View.h"
#include "ForConsole.h"
#include "Printer.h"
#include "Color.h"

Printer lGrOnBlue(Color::LIGHT_GREEN, Color::BLUE);
class HighscoreView: public View
{
	
public:
	HighscoreView(){}
	View* handle()
	{
		View* nextView = this;
		clean();
		View::draw();
		printAtLineCenter(4, "Nicknames:        |       Scores:", lGrOnBlue);
		printAtLineCenter(5, "Chuck Norris      |       1000000", lGrOnBlue);
		printAtLineCenter(6, "T-800             |           760", lGrOnBlue);
		printAtLineCenter(7, "Die Hard          |           540", lGrOnBlue);
		printAtLineCenter(8, "Rembo             |           420", lGrOnBlue);
		printAtLineCenter(14, "                                ", lGrOnBlue);
		_getch();
		return nextView;
	}
};

