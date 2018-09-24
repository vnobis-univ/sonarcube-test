#pragma once
#include "Console.h"
#include "Printer.h"

class View
{
public:
	virtual void draw();
	virtual View* handle() = 0;
};