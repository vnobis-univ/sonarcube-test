#pragma once

#include "View.h"

struct SideBar: public View
{
	int life;
	int score;
	int numOfCells;
	int width;
	int height;
	int left;
	int top;

	View* handle();

	SideBar(int = 0, int = 0, int = 0, int = 27 * FONT_WIDTH, int = 5 * FONT_HEIGHT);

	void setLeft(int);
	int getLeft() const;

	void setTop(int);
	int getTop() const;

	void setWidth(int);
	int getWidth() const;

	void setHeight(int);
	int getHeight() const;

	void draw();
};