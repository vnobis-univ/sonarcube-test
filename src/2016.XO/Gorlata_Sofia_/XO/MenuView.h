#pragma once
#include <string>
#include "View.h"

using std::string;

class MenuView: public View
{
	const string option[3] = { " Start ", " High Score ", "Exit " };
	int selected;

	void printMenu();
public:
	MenuView();

	virtual void draw();
	virtual View* handle();
};