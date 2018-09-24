#pragma once
#include "View.h"

using namespace std;

class BehindStartView : public View
{
	int selected;
	string options[2] = {"English", "Ukrainian"};

public:
	BehindStartView();
	void printMenu();
	void draw();
	View *handle();
};
