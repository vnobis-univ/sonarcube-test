#include <windows.h>
#include <iostream>
#include <string>
#include "Printer.h"

Printer::Printer(): clFont(Color::white), clBackground(Color::black) {}

Printer::Printer(Color clFont, Color clBackground) :clFont(clFont), clBackground(clBackground) {}

void Printer::setClFont(Color newCl)
{
	clFont = newCl;
}

void Printer::print(std::string stringToPrint) {
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	int color = (int)clFont + 16 * (int)clBackground;
	SetConsoleTextAttribute(hConsole, color);

	std::cout << stringToPrint;

	//setting default
	SetConsoleTextAttribute(hConsole, 15); 
}
