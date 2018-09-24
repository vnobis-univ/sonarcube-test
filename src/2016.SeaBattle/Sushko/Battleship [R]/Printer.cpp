#include "Printer.h"
#include "ExternUtils.h"
#include "ConsoleUtils.h"
#include <Windows.h>
#include <iostream>

using namespace std;

int Printer::convertTextCol() const
{
	return (int)text;
}

int Printer::convertBgrndCol() const
{
	return (int)backgroung;
}

Printer::Printer(Color txt, Color bg) : text(txt), backgroung(bg) {}

void Printer::print(string text) const
{
	SetConsoleTextAttribute(hConsole, convertTextCol() + convertBgrndCol() * 16);
	cout << text;
	SetConsoleTextAttribute(hConsole, 15);
}

void Printer::setColor() const
{
	SetConsoleTextAttribute(hConsole, convertTextCol() + convertBgrndCol() * 16);
}

void Printer::midLinePrint(int line, string text) const
{
	int x_pos = (120 - text.length()) / 2;
	moveTo(x_pos, line);

	print(text);
	std::cout << std::endl;
}