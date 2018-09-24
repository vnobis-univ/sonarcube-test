#include "Printer.h"

Printer::Printer():background(Color::Black),font(Color::White){}
Printer::Printer(Color _background, Color _font) : background(_background), font(_font){}

int Printer::ConvertColorsToInt()const
{
	return ColToInt(background) * 16 + ColToInt(font);
}
const Printer& Printer::operator<<(string text)
{
	HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(&hconsole, &info);
	SetConsoleTextAttribute(hconsole, ConvertColorsToInt());
	cout << text;
	return *this;
}