#pragma once
#include "View.h"

class HelpView : public View
{
public:
	void print();
	void draw();
	View *handle();
};
