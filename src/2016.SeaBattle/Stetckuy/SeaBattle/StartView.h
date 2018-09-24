#pragma once

#include "View.h"

using namespace std;

class StartView : public View
{
	enum class Action
	{
		START,
		OPTIONS,
		HIGH_SCORES,
		EXIT
	};

	int menuCurrent;

	void drawMenu();
public:
	StartView();

	void draw();
	View* handle();
};
