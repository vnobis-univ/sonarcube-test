#include "Printer.h"

Printer::Printer() : background(ConsoleColor::Black), text(ConsoleColor::White) {}
Printer::Printer(ConsoleColor b, ConsoleColor t) : background(b), text(t) {}
int Printer::getTextColors()const
{
	return convertColToInt(background) * 16 + convertColToInt(text);
}
const Printer& Printer::operator<<(string tex)
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(&hconsole, &info);
	SetConsoleTextAttribute(hconsole, getTextColors());
	cout << tex;
	return *this;
}