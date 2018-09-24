#pragma once
#include "View.h"

using namespace std;

class StartView : public View
{
	string* options = new string[4];
	int selected = 0;//selected option. Is 0(options[0]) as default. Used int (not string) because we have 2 languages.
	Button* allowedButtons = new Button[4]
	{
		Button::UP,
		Button::DOWN,
		Button::ENTER,
		Button::ESC
	};
	int allowedButtonsSize = 4;
public:
	StartView();
	void printMenu();
	void draw();
	void setOptions();
	View *handle();
};
