#pragma once

#include "View.h"

class OptionView : public View
{
	vector<MenuItem> menu;
	int menuCurrent;

	void drawMenu();
	void changeMenuItems();
public:
	OptionView();

	View* handle();

	void draw();
};