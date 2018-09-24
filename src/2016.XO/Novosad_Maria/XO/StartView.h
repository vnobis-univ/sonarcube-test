#pragma once
#include <iostream>
#include <conio.h>
#include "View.h"
#include "Options.h"
#include "ConsoleFunctions.h"
using namespace std;

class StartView: public View
{
private:
	int selectedOption = 0;
	Options availableOptions[3] ;
	string convertToString(Options option);
	View* applyOption();
public:
	StartView();
	void draw();
	View* handle();
};

