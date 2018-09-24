#pragma once
#include "Printer.h"

class View
{
protected:
	static int whereLogoEnds;
	static Printer mainPrinter;

public:
	virtual void draw() = 0;

	virtual View* handle() = 0;

protected:
	void drawEmptyLines(int) const;

	void clean();

	void drawLogo(int) const;
};



