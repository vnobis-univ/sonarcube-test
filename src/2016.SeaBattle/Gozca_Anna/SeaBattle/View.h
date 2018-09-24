#pragma once
#include <iostream>
#include <Windows.h>
#include "ConsoleUtils.h"
#include "Printers.h"

class View
{
public:
	View();
	void clean();
	virtual void printLogo() = 0;
	virtual void draw() = 0;
	virtual View * handle() = 0;
};