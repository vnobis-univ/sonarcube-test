#include "Printer.h"
#include <iostream>
#include <windows.h>

using namespace std;

Printer::Printer() : colorOfText(Color::White), colorOfBackground(Color::Black)
{
}

Printer::Printer(Color text, Color background) : colorOfText(text), colorOfBackground(background)
{
}

void Printer::print(string text)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<int>(colorOfText) + static_cast<int>(colorOfBackground) * 16);
	cout << text << endl;
}