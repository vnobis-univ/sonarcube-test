#pragma once
#include "View.h"
#include "Complexity.h"
#include <string>

using namespace std;

class StartView : public View
{
	int selected;
	string options[3] = { "Start", "Table of Heroes", "Exit" };
public:
	StartView();
	void printMenu();
	void draw();
	View *handle();
};