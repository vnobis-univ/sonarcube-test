#pragma once
#include "View.h"
#include <iostream>
#include "FieldView.h"
#include "Console.h"
#include "Printer.h"
#include <conio.h>
#include "HighScoresView.h"
#include <fstream>

class ResultView : public View
{
	bool isAchieve;
	short score;
public:
	ResultView(bool, short);
	void draw();
	View* handle();
};
