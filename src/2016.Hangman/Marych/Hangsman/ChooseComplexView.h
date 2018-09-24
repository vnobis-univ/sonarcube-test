#pragma once
#include "View.h"

using namespace std;

class ChooseComplexView : public View
{
	int selected;
	string options[3];
public:
	ChooseComplexView();
	void printMenu();
	void draw();
	void setOptions();
	View* handle();
};