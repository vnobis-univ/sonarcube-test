#include "View.h"

void View::draw()
{
	setCursor(0, 0);
	Printer pan(ConsoleColor::Black, ConsoleColor::LightGreen);
	//drawFrame(greenPan, PanBlack, 278, 5, 464, 58);
	printTextOnTheCenter(1, "*  Hangman  *", pan);
	showCursor(false);
}