#include "Printer.h"
#include "Utils.h"

Printer::Printer(Color bg, Color txt) : text(bg), backgroung(txt){};

int Printer::convertTextCol() const
{
	return int(text);
}

int Printer::convertBgrndCol() const
{
	return int(backgroung);
}

void Printer::Print(string str) const
{
	SetConsoleTextAttribute(hConsole, convertTextCol() + convertBgrndCol() * 16);
	std::cout << str;
	SetConsoleTextAttribute(hConsole, 15);
}

void Printer::Print(int num) const
{
	SetConsoleTextAttribute(hConsole, convertTextCol() + convertBgrndCol() * 16);
	std::cout << num;
	SetConsoleTextAttribute(hConsole, 15);
}

void Printer::SetConsoleAttribute() const
{
	SetConsoleTextAttribute(hConsole, convertTextCol() + convertBgrndCol() * 16);
}

void Printer::MidLinePrint(int line, string text, unsigned i) const
{
	int x_pos = (consoleWidth - text.length()) / 2;

	moveCursorTo(x_pos, line);

	Print(text);
	if (i != -1) 
		Print(i);

	std::cout << std::endl;
}
