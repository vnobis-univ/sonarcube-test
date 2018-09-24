#pragma once

enum class StateOfFieldCell
{
	Empty,
	NotEmpty
};

class Field
{
private:
	StateOfFieldCell field[10][10];
public:
	Field();
	void drawEmptyField(int x, int y);
	StateOfFieldCell getStateOfCell(int i, int j);
	void  setStateOfCell(int i, int j, StateOfFieldCell state);
	void draw(int x, int y);
};

