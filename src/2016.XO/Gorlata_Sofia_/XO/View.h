#pragma once
#include "Utils.h"


class View
{
public:
	View::View() {
		showConsoleCursor(false);
	}

	virtual void draw() = 0;
	virtual View* handle() = 0;
};