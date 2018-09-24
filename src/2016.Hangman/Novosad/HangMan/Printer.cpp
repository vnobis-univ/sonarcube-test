#include "Printer.h"
#include <iostream>
#include <windows.h>
using namespace std;

Printer::Printer() : color_of_text(Color::White), color_of_background(Color::Black) {}
Printer::Printer(Color color_of_text1, Color color_of_background1) : color_of_text(color_of_text1), color_of_background(color_of_background1) {}

void Printer::print(string text)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ((int)color_of_text + (int)color_of_background * 16));
	cout << text;
	SetConsoleTextAttribute(hConsole, (14 + 2 * 16));
}

void Printer::print(Word word)
{
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, ((int)color_of_text + (int)color_of_background * 16));
	cout << word;
	SetConsoleTextAttribute(hConsole, (14 + 2 * 16));
}