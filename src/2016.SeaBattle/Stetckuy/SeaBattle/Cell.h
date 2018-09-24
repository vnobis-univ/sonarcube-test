#pragma once

#include <Windows.h>

using namespace std;

enum class State
{
	ACTIVE = 1,
	PASSIVE
};

class Cell
{
	int x; // column
	int y; // row
	int sideX; // length
	int sideY; // height
	bool empty;  // contains a ship frame or not
	bool hidden; // is data hidden from user or not
	bool marked; // was it already hit or not yet

public:
	Cell(int = 0, int = 0, int = 30, int = 30, bool = false, bool = false);

	bool isEmpty();
	bool isHidden() const;
	bool isMarked() const;

	int getX() const;
	int getY() const;
	int getSideX() const;
	int getSideY() const;

	void setX(int);
	void setY(int);
	void setSideX(int);
	void setSideY(int);

	void hide();
	void reveal();
	void draw(); // draws the cells when it was hit by user
	void drawOutline(State); // draws a "X"

	void activate(); // make non-empty
	void disactivate(); // make empty
	void mark();
};