#pragma once
#include "ConsoleUtils.h"


class View
{
protected:
	Difficulty lvl;
public:
	View(Difficulty _lvl = Difficulty::Normal) : lvl(_lvl) {}
	virtual ~View() {}

	virtual void draw() = 0;
	virtual View* handle() = 0;
};
