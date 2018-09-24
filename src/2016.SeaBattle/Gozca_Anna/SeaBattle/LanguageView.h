#pragma once
#include "View.h"
#include "GlobalVars.h"

class LanguageView : public View
{
	string options[3];
	int selected;
	Language language;
public:
	LanguageView();
	LanguageView(Language lang);
	void printLogo();
	void draw();
	View * handle();
};