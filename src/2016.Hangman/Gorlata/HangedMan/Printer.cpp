#include "Printer.h"
#include "Utils.h"
#include "HighScore.h"

using namespace std;

Printer::Printer(Color m_words, Color m_background):
	words(m_words),
	background(m_background)
	{}

template void Printer::print(int);
template void Printer::print(string);
template void Printer::print(char);
template void Printer::print(Row);

template<typename T>
void Printer::print(T text)
{
	int m_w = (int)words;
	int m_b = (int)background;

	SetConsoleTextAttribute(hConsole, m_w + m_b * 16);

	cout << text << endl;

	SetConsoleTextAttribute(hConsole, 15);
}
void Printer::printOnCenter(int line, std::string text)
{
	int xPos = (consoleWidth - text.length()) / 2;

	moveCursorTo(xPos, line);
	print(text);
};