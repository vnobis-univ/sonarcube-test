#include "Cell.h"
#include "Utils.h"
#include "Printer.h"



using namespace std;

Cell::Cell(int _x, int _y, State s):
	x(_x),
	y(_y),
	state(s)
	{}
bool Cell::operator==(const Cell & obj) const
{
	return state == obj.state && state != Cell::State::empty;
}
void Cell::draw(bool selected)
{
	selected ? SetConsoleTextAttribute(hConsole, 7 + 1 * 16) : SetConsoleTextAttribute(hConsole, 7 + 9 * 16);

	if (y != 0)
	{
		moveCursorTo(topLeftX + cellSize*x - 1, topLeftY + cellSize*y - 1);
		cout << "######";
	}
	for (int i = 0; i < 4; ++i)
	{
		moveCursorTo(topLeftX + cellSize*x - 1, topLeftY + cellSize*y +i);
		x == 1 ? cout << "#    #" : (x == 2 ? cout << "#     " : cout << "     #");
	}
	
	/*moveCursorTo(topLeftX + cellSize*x - 1, topLeftY + cellSize*y + 1);
	x == 1 ? cout << "#    #" : (x == 2 ? cout << "#     " : cout << "     #");
	moveCursorTo(topLeftX + cellSize*x - 1, topLeftY + cellSize*y + 2);
	x == 1 ? cout << "#    #" : (x == 2 ? cout << "#     " : cout << "     #");
	moveCursorTo(topLeftX + cellSize*x - 1, topLeftY + cellSize*y + 3);
	x == 1 ? cout << "#    #" : (x == 2 ? cout << "#     " : cout << "     #");*/

	if (y != 2)
	{
		moveCursorTo(topLeftX + cellSize*x - 1, topLeftY + cellSize*y + 4);
		cout << "######";
	}

	if (state == State::cross)
		drawCross(selected);
	if (state == State::zero)
		drawZero(selected);

};

void Cell::drawCross(bool selected)
{
	//Printer crossPrint;
	selected ? SetConsoleTextAttribute(hConsole, 12 + 1 * 16) :
		SetConsoleTextAttribute(hConsole, 12 + 9 * 16);

	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y);
	cout << "\\  /";
	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y + 1);
	cout << " \\/ ";
	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y + 2);
	cout << " /\\ ";
	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y + 3);
	cout << "/  \\";
	SetConsoleTextAttribute(hConsole, 15);
}

void Cell::drawZero(bool selected)
{
	selected ? SetConsoleTextAttribute(hConsole, 12 + 1 * 16) :
		SetConsoleTextAttribute(hConsole, 12 + 9 * 16);

	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y);
	cout << " /\\ ";
	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y + 1);
	cout << "/  \\";
	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y + 2);
	cout << "\\  /";
	moveCursorTo(topLeftX + cellSize*x, topLeftY + cellSize*y + 3);
	cout << " \\/ ";
	SetConsoleTextAttribute(hConsole, 15);
}
