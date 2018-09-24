#pragma once

#include "View.h"

class OptionView : public View
{
	int menuCurrent;

	void drawMenu();
public:
	OptionView();

	View* handle();

	void draw();
};