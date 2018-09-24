#pragma once
#include <fstream>
#include <iostream>
#include <conio.h>
#include "View.h"
#include "FieldView.h"
#include "HighScores.h"
#include "Printer.h"


class ResultView:public View
{
private:
	bool isHere;
	short score;
public:
	ResultView(bool,short);
	void draw();
	View *handle();
};