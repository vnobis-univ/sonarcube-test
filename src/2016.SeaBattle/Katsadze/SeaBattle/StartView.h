#pragma once
#include <conio.h>
#include "View.h"
#include "Buttons.h"
#include "PreFieldView.h"
#include "HighscoresView.h"

class StartView : public View
{
	string optionEn[4] = { "Start", "Highscores", "Exit" };
	short position;
public:
	StartView();
	void draw();
	void printMenu();
	View* handle();
};