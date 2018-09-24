#include "Printer.h"

Printer::Printer() : background(ConsoleColor::Black), text(ConsoleColor::White) {}
Printer::Printer(ConsoleColor b, ConsoleColor t) : background(b), text(t) {}
int Printer::getTextColors()const
{
	return convertColToInt(background) * 16 + convertColToInt(text);
}
void Printer::print(char symb) const
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(&hconsole, &info);
	SetConsoleTextAttribute(hconsole, getTextColors());
	cout << symb;
	SetConsoleTextAttribute(hconsole, info.wAttributes);
}
const Printer& Printer::operator<<(string text)
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(&hconsole, &info);
	SetConsoleTextAttribute(hconsole, getTextColors());
	cout << text;
	SetConsoleTextAttribute(hconsole, info.wAttributes);
	return *this;
}
