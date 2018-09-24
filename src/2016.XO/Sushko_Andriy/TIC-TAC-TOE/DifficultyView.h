#pragma once
#include "View.h"

class chooseDifficultyView: public View
{
	const string options[2] = { "NORMAL", "EXPERT" };
	int selected;
	void printMenu();
public:
	chooseDifficultyView();

	virtual void draw();
	virtual View* handle();
};