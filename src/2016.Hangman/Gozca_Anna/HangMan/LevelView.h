#pragma once
#include "View.h"
#include "Printers.h"
#include "ConsoleUtils.h"
#include "GameView.h"
#include "GlobalVar.h"

class LevelView : public View
{
private:
	string levels[3];
	int numOfSelectedLevel;
public:
	LevelView();
	void draw();
	View * handle();
};
