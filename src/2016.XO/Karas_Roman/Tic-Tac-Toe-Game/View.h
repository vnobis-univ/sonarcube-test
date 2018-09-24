#pragma once

#include "Printer.h"
#include <string>

using namespace std;

class View
{
	void drawBackground();
public:
	virtual void draw();
	virtual View* handle() = 0;
	void clean();
};

