#include "GreetingView.h"
#include "ConsoleManipulators.h"
#include "Printer.h"
#include "MenuView.h"
#include "FilesManipulator.h"
#include <time.h>
#include <fstream>
#include <vector>

GreetingView::GreetingView(){}

void GreetingView::draw()
{
	setCursoreAtPosition(13, 18);

	Printer classicPrinter;

	classicPrinter << "Welcome to..." << "\n";

	drawLogo(19);

	drawAuthor();
}

void GreetingView::drawAuthor() const
{
	Printer classicPrinter;
	std::string author = "Coded by Andriy Shpak. 2016. ";

	setCursoreAtPosition(getConsoleWidth() - author.length(), getConsoleHeight() - 1);

	classicPrinter << author;
}

void GreetingView::waitBlinking() const
{
	Printer classicPrinter;
	std::string pressKey = "PRESS ANY KEY TO START";
	std::string empty(pressKey.length(), ' ');

	while (!checkIfKeyPressed())
	{
		setCursoreAtPosition(0, 27);
		classicPrinter.printAtCenter(pressKey);

		if (timer(0.7)) break;

		setCursoreAtPosition(0, 27);
		classicPrinter.printAtCenter(empty);

		if (timer(0.6)) break;
	}
}

bool GreetingView::timer(double timeToCount) const
{
	clock_t begin = clock();

	while(((unsigned long)clock() - begin) / CLOCKS_PER_SEC < timeToCount)
	{
		if (checkIfKeyPressed())
			return true;
	}

	return false;
}

View* GreetingView::handle()
{
	waitBlinking();

	return new MenuView;
}
