#pragma once
#include "View.h"

using namespace std;

class OptionView : public View
{
	int selected;
	string options[3];
public:
	OptionView();
	void printMenu();
	void draw();
	void setOptions();
	View* handle();
};