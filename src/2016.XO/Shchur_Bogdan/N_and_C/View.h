#pragma once
#include <string>
#include "Console.h"
#include "Color.h"

using namespace std;

class View
{
public:
	virtual void draw();
	virtual View* handle() = 0;
};