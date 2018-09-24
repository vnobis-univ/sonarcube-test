#pragma once
#include "Printer.h"
#include "Utils.h"
#include <Windows.h>

class View
{
public:
	virtual void draw() = 0;
	virtual View* handle() = 0;
};
