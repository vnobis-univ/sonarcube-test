#include "View.h"

void View::draw()
{
	setCursor(0, 0);
	Printer head(ConsoleColor::LightMagenta, ConsoleColor::Black);
	Printer main(ConsoleColor::LightMagenta, ConsoleColor::DarkGray);
	string mainer = string(consoleWidth, ' ');
	for (int i = 0; i < consoleHeight; ++i)
	{
		main << mainer;
	}
	setCursor(0, 0);
	head << "***************";
	printTextOnTheCenter(0, "Tic-Tac-Toe", head);
	head << "   **************************";
	head << "           \t\t\t****************\t\t\t\t\t    ******";
	head << "***\t\t\t\t\t       ***";
	head << "*\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t *";
	head << "*\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t *";
	head << "*\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t **\t\t\t\t\t\t *";
	head << "*************************************************";
	showCursor(false);
}
void View::drawBackground()
{
	setCursor(0, 0);
	Printer head(ConsoleColor::LightMagenta, ConsoleColor::Black);
	Printer main(ConsoleColor::LightMagenta, ConsoleColor::DarkGray);
	string mainer = string(consoleWidth, ' ');
	for (int i = 0; i < consoleHeight; ++i)
	{
		main << mainer;
	}
	showCursor(false);
}