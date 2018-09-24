#pragma once
#include "View.h"
#include "GlobalVars.h"
#include "ConsoleUtils.h"
#include "Player.h"

class HighScoreView:public View
{
	Language language;
public:
	HighScoreView();
	HighScoreView(Language _language);
	void printLogo();
	void draw();
	View * handle();
};