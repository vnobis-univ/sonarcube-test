#pragma once
#include "View.h"
#include <string>
#include "GlobalVars.h"
using namespace std;

class StartView :public View
{
	string options[4];
	int selected;
	Language language;
public:
	StartView();
	StartView(Language lang);
	void printLogo();
	void draw();
	View * handle();
};