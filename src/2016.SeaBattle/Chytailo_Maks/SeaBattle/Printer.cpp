#include "Printer.h"


Printer::Printer() :frontColor(WHITE), backgroundColor(LIGHT_AQUA)
{
}

Printer::Printer(Color f, Color b) : frontColor(f), backgroundColor(b)
{
}

void Printer::print(string text)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ((int)frontColor + (int)backgroundColor * 16));
	cout << text << " ";
}