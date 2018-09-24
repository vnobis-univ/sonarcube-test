#pragma once
#include "Utils.h"

struct Cell
{
	enum class State { empty, filledX, filledO };

	int x;
	int y;
	State state;

	void drawCell(HPEN pen);
	void drawX(HPEN pen);
	void drawO(HPEN pen);

	void operator++();
	bool operator == (const Cell& obj) const;

	Cell(int m_x = 0, int m_y = 0, State st = State::empty);
};