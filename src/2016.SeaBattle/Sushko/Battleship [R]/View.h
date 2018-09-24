#pragma once

class View
{
public:
	View() {}
	virtual ~View() {}

	virtual void draw() = 0;
	virtual View* handle() = 0;
};
