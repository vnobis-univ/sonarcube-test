#include "View.h"

void View::draw()
{
	setCursor(0, 0);
	Printer back(Color::LightGray, Color::Green);
	Printer body(Color::LightGray, Color::Black);
	string main = string(consoleWidth, ' ');
	for (int i = 0; i < consoleHeight; ++i)
	{
		body << main;
	}
	setCursor(0, 0);
	printInCenter(0, "X vs O", back);
	showCursor(false);
}