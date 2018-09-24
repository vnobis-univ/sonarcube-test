#pragma once
#include <windows.h>

enum class State { EMPTY, SHIP, DAMAGED, KILLED, DOT };

class Cell
{
	static const int size = 18;
	int x;
	int y;
	State state;
public:

	Cell(int _x = 0, int _y = 0, State = State::EMPTY);
	void draw(int FieldX, int FieldY, HPEN pen);
	
	int getX();
	int getY();
	void setY(int _y);
	void setX(int _x);
	int getSize();

	void drawDot(int FieldX, int FieldY, HPEN pen);
	void drawCross(int FieldX, int FieldY, HPEN pen);

	State getState();
	void setState(State my_state);


	bool isValid();
};