#pragma once
#include "MainMenu.h"

class OptionsMenu
{
	int IsSelected;
	int level;
public:
	OptionsMenu();

	int GetSelected();
	int GetLevel();

	void drawUKR();

	void drawENG();

	void draw(bool);
};
