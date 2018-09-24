#include "Printer.h"

HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

Printer::Printer(ConsoleColor b, ConsoleColor t): background(b), text(t){}

int Printer::getTextColor() const
{
	return convertColToInt(background) * 16 + convertColToInt(text);
}

const Printer & Printer::operator<<(string line)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(&hconsole, &info);
	SetConsoleTextAttribute(hconsole, getTextColor());
	cout << line;
	return *this;
}
