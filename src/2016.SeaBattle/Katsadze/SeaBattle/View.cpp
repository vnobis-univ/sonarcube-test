#include "View.h"

void View::draw()
{
	Printer viewPen(ConsoleColor::White, ConsoleColor::Red);
	setCursor(0, 0);
	string symb = " ";
	for (int i = 0; i < consoleHeight; ++i)
	{
		for (int j = 0; j < consoleWidth; ++j)
		{
			viewPen << symb;
		}
	}
	printInCenter(0, "*  Ship Wars *", viewPen);
	showCursor(false);
}