#pragma once

#include <string>
#include "Colors.h"
#include "Console.h"

using namespace std;

class View
{
public:
	virtual void draw();
	virtual View*handle() = 0;
};