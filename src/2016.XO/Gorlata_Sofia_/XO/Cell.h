#pragma once

struct Cell
{
	enum class State { empty, cross, zero };
	int x;
	int y;
	State state;

	Cell(int _x = 0, int _y = 0, State s = State::empty);
	bool operator ==(const Cell& obj) const;
	

	void draw(bool selected = false);
	void drawCross(bool selected);
	void drawZero(bool selected);
};

