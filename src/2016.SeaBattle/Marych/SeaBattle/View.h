#pragma once

#include "Printer.h"
#include "Language.h"
#include "Button.h"
#include <string>

using namespace std;

class View
{
	void drawBackground();
protected:
	static Printer defaultPrinter;
	static Printer defaultPrinterBg;
public:
	virtual void draw();
	virtual View* handle() = 0;

	void clean();
};