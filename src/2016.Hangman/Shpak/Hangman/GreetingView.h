#pragma once
#include "View.h"
#include <vector>
#include <string>

class GreetingView: public View
{
public:
	GreetingView();

	void draw();

	View* handle();

private:
	void drawAuthor() const;

	void waitBlinking() const;

	bool timer(double) const;
};

