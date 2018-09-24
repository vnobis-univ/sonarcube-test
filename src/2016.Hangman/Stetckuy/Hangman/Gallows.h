#pragma once

#include <string>
#include "ConsoleProperties.h"

using namespace std;

class Gallows
{

	int left;
	int top;
	int width;
	int height;
	string convictName;
	int currStep;
	vector<string> comments;
	COLORREF backgroundColor;
	COORD speechTopLeft;
	COORD speechBottomRight;

	void drawElement(int);

	void makeEmpty();

	void configure();
public:
	Gallows(int = 0, int = 0,
		int = FONT_WIDTH*CONSOLE_WIDTH / 2,
		int = FONT_HEIGHT*CONSOLE_HEIGHT / 2, string = "Sheldon",
		COLORREF = RGB(0, 0, 200));

	void setStep(int);

	void setName(string);

	void draw();

};