#pragma once
#include "LanguageMenu.h"

class MainMenu
{
	int IsSelected;
public:
	MainMenu();

	void drawUKR();

	void drawENG();

	void draw(bool);
};
