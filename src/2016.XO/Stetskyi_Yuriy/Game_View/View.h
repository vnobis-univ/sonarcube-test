#pragma once

#include "Printer.h"

using namespace std;

enum class Options {
	START,
	HIGH_SCORE,
	EXIT
};

enum class Result { RECORD, VICTORY, DEFEAT };

class View
{
public:
	View() {}
	virtual void draw() = 0;
	void clear();
	virtual ~View() {}
};
