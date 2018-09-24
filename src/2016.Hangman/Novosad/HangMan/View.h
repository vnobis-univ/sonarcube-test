#pragma once

class View
{
public:
	View();
	virtual void draw() = 0;
	virtual View* handle() = 0;
	virtual void clean();
};

