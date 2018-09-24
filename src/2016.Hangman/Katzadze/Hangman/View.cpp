#include "View.h"

void View::draw()
{
	setCursor(0, 0);
	Printer title(Color::LightGray, Color::DarkGray);
	printInCenter(0, "Hangman", title);

	showCursor(false);
}