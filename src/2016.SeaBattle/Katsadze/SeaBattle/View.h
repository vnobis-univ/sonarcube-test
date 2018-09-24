#pragma once
#include <conio.h>
#include "Console.h"
#include "Printer.h"
#include "Buttons.h"

class View
{
public:
	virtual void draw();
	virtual View* handle() = 0;
};