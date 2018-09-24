#include "Printer.h"
#include "Utils.h"
using namespace std;

Printer::Printer(Color m_words, Color m_back) : words(m_words), back(m_back) {}

void Printer::print(std::string s)
{
	int m_w = (int)words;  
	int m_b = (int)back;

	SetConsoleTextAttribute(hConsole, m_w + m_b * 16);

	cout << s << endl;

	SetConsoleTextAttribute(hConsole, 15);
}

void Printer::print(int num)
{
	int m_w = (int)words; 
	int m_b = (int)back;

	SetConsoleTextAttribute(hConsole, m_w + m_b * 16);

	cout << num << endl;

	SetConsoleTextAttribute(hConsole, 15);
}


void Printer::printOnCenter(int line, std::string text)
{
	int xPos = (consoleWidth - text.length()) / 2;

	moveCursorTo(xPos, line);
	print(text);


}