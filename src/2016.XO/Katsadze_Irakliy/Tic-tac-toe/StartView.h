#pragma once
#include "View.h"
#include <string>

using namespace std;

class StartView :public View
{
	int selected;
	
public:
	StartView();
	void printMenu();
	void draw();
	View *handle();
};