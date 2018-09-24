#pragma once
#include "View.h"
#include "ConsoleUtils.h"

struct Coords {
	int x;
	int y;
	Coords(int _x = 0, int _y = 0) : x(_x), y(_y) {};
};

class HangedManDrawer
{
	const View* view;
	double k; // size koeficient
	Coords head;
	Coords gallows;

	HPEN draw;
	HPEN erase;

	void drawHead();
	void drawEyes();
	void drawSmile();
	void drawBody();
	void drawHands();
	void drawLegs();

	void drawGallows(int step);
public:
	HangedManDrawer(const View*, HPEN drawer, HPEN eraser, int headX, int headY, double = 1);

	void drawByStep(int step);
	void drawAll();
	void hang(int howLong = 800);
};