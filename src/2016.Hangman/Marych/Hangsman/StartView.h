#pragma once
#include "View.h"

using namespace std;

class StartView : public View
{
	int selected;
	string options[4];
public:
	StartView();
	void printMenu();
	void draw();
	void setOptions();
	View *handle();
};
