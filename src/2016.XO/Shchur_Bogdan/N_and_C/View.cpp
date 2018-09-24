#include "View.h"

void View::draw()
{
	setCursor(0, 0);
	Printer head(ConsoleColor::LightGray, ConsoleColor::Red);
	Printer main(ConsoleColor::LightGray, ConsoleColor::DarkGray);
	string mainer = string(consoleWidth, ' ');
	for (int i = 0; i < consoleHeight; ++i)
	{
		main << mainer;
	}
	setCursor(0, 0);
	printTextOnTheCenter(0, "Noughts&Crosses", head);
	showCursor(false);
}