#pragma once
#include "View.h"
#include "ResulView.h"
#include <string>

extern int o ;
//extern int a; 
extern int counterOfMoves;
extern int score;
void printInTheCentre(string str, int numberOfLine, int consoleWidth);
enum statusOfCell
{
	Empty,
	Cross,
	Zero
};

enum PossibleEndOfGame
{
	Win,
	Lose,
	Friendship
};
struct Cell
{
	unsigned x;
	unsigned y;
	statusOfCell status;
	Cell();
	Cell(unsigned x1, unsigned y1, statusOfCell status1);
	bool operator == (const Cell &c);
	Cell operator = (const Cell &c);
};

class FieldView: public View
{
	Cell selectedCell;
	void drawCell(Cell cell);
	PossibleEndOfGame upDownLeftRight(int);
	PossibleEndOfGame enterKey(int key);
	PossibleEndOfGame win();
	void array(Cell **&arrOfCells);
public:
	FieldView();
	//void drawCell(Cell cell);
    void draw();
	View* handle();
	/*PossibleEndOfGame upDownLeftRight(int);
	PossibleEndOfGame enterKey(int key);
	PossibleEndOfGame win();
	void array(Cell **&arrOfCells);*/
};

