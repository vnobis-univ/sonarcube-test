#pragma once
#include "Console_.h"
#include "Printer.h"

class View
{
public:
	virtual void draw();
	virtual View* handle() = 0;
};