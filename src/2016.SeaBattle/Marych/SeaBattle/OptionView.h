#pragma once
#include "View.h"

using namespace std;

class OptionView : public View
{
	int selected = 0;
	string* options = new string[3];
	Button* allowedButtons = new Button[4]
	{
		Button::UP,
		Button::DOWN,
		Button::ENTER,
		Button::ESC
	};
	int allowedButtonsSize = 4;
public:
	OptionView();
	void printMenu();
	void draw();
	void setOptions();
	View* getNextAction(int);
	View* handle();
};