#include <iostream>
#include <afxinet.h> 
#include "ConsoleUtils.h"
#include "Printer.h"

using namespace std;

int Printer::convertTextCol() const 
{ return (int)text; }

int Printer::convertBgrndCol() const
{ return (int)backgroung; }

Printer::Printer(Color txt, Color bg): text(txt), backgroung(bg) {}

void Printer::Print(string text) const
{
	SetConsoleTextAttribute(hConsole, convertTextCol() + convertBgrndCol() * 16);
	std::cout << text;
	SetConsoleTextAttribute(hConsole, 15);
}

void Printer::setColor() const
{ SetConsoleTextAttribute(hConsole, convertTextCol() + convertBgrndCol() * 16); }

void Printer::MidLinePrint(int line, string text) const
{
	int x_pos = (consoleWidth - text.length()) / 2;
	moveTo(x_pos, line);

	Print(text);
	std::cout << std::endl;
}