#pragma once
#include <iostream>
#include <conio.h>
#include "View.h"
#include "Options.h"
#include "ConsoleFunctions.h"
#include "TranslationService.h"
using namespace std;

class StartView : public View
{
private:
	TranslationService service;
	int selectedOption = 0;
	Options availableOptions[3];
	string convertToString(Options option);
	View* applyOption();
public:
	StartView();
	void draw();
	View* handle();
};

