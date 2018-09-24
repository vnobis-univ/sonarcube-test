#pragma once
#include <iostream>
#include "View.h"
#include "Printer.h"

using std::string;

class StartView : public View
{
	const string options[3] = { "START GAME", "HIGHT SCORES", "EXIT" };
	int selected;
	void printMenu();

public:
	StartView();

	virtual void draw();
	virtual View* handle();
};