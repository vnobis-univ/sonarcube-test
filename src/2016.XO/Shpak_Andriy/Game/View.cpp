#include <iostream>
#include "View.h"
#include "ConsoleManipulators.h"

void View::draw()
{
	clean();
	setCursorState(false);

	// here can call drawBackground() if wabt bacground in each view
}

void View::drawBackground()
{
	int height = getConsoleHeight();
	int width = getConsoleWidth();

	//system("COLOR") can be used in case when you want another background color(needed for last character);
	int counter = 0;

	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width; ++j)
			if (i == height - 1 && j == width - 1)
				break;
			else if ((i + j) % 2 == 1 && (i == 0 || j == 0 || i == height - 1 || j == width - 1 || i + j < 7 || width - j - 1 + i < 7))
				if (counter++ % 2)
					Printer(Color::blue, Color::black).print("O");
				else
					Printer(Color::blue, Color::black).print("X");
			else 
				Printer(Color::white, Color::black).print(" ");

	setCursoreAtPosition(0, 0);

	std::string gameName = "  TIC-TAC-TOE  ";

	drawLeftPadding(gameName.size());

	Printer(Color::purple, Color::black).print(gameName);

	setCursoreAtPosition(0, 0);
}

void View::drawAtCenter(std::string str, Printer printer)
{
	// printint centered str

	drawLeftPadding(str.length());

	printer.print(str);

	std::cout << std::endl;
}

void View::drawLeftPadding(int sizeOfLine)
{
	int leftPadding = (getConsoleWidth() - sizeOfLine) / 2;

	int currentX;
	int currentY;

	getCursorPosition(currentX, currentY);

	setCursoreAtPosition(currentX + leftPadding, currentY);
		
}

void View::drawEmptyLines(int numberLines) const
{
	for (size_t i = 0; i < numberLines; ++i)
		std::cout << std::endl;
}

void View::clean()
{
	system("cls");
}



