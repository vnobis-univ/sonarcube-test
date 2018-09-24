#pragma once

using namespace std;

class Cell
{
	int x;
	int y;
	int side;
	char state;

	void drawX(int coordX, int coordY, COLORREF);
	void drawO(int coordX, int coordY, COLORREF, COLORREF);

public:
	Cell(int = 0, int = 0, int = 50);

	bool empty() const;
	int getX() const;
	int getY() const;
	int getSide() const;
	char getState() const;


	void draw(COLORREF, COLORREF);
	void activate();
	void disactivate();
	void fill(const char);
};