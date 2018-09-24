#include "Printer.h"

HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);

Printer::Printer(Color b, Color t) : background(b), text(t){}

int Printer::getColor() const
{
	return intColor(background) * 16 + intColor(text);
}

const Printer & Printer::operator<<(string line)
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(&hconsole, &info);
	SetConsoleTextAttribute(hconsole, getColor());
	cout << line;
	return *this;
}