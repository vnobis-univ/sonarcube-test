#pragma once
#include <string>
#include "Printer.h"

class View
{
public:
	virtual void draw();

	virtual View* handle() = 0;

protected:
	void drawAtCenter(std::string str, Printer printer);

	void drawLeftPadding(int);

	void drawEmptyLines(int) const;

	void drawBackground();

	void clean();
};

