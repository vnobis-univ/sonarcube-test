#pragma once
#include "View.h"
#include <string>

using namespace std;

class StartView : public View
{
	int selected;
	string options[3] = { "New Game", "High Scores", "Exit" };
public:
	StartView();
	void printMenu();
	void draw();
	View *handle();
};
