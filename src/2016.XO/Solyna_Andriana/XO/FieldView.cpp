#include "FieldView.h"
#include "StartView.h"
#include "HighScoresView.h"
#include <iostream>
using namespace std;

extern const int consoleSize = 40;
extern const int startOfFieldX = 13;
extern const int startOfFieldY = 3;
extern const int sizeOfCell = 5;
int counterOfMoves = 0;
int score = 0;
int o = 0;
int x = startOfFieldX; 
int y = startOfFieldY;
Cell **arrOfCells;

void FieldView::array(Cell **&arrOfCells) // fills array with cells
{
	arrOfCells = new Cell*[3];
	for(size_t i = 0; i < 3; ++i)
	{
		arrOfCells[i] = new Cell[3];
	}
	for(size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			arrOfCells[j][i] = Cell(x,y,Empty);
			x = x + sizeOfCell;
		}
		x = startOfFieldX;
		y = y + sizeOfCell;
	}
	x = startOfFieldX;
	y = startOfFieldY;
}

Cell :: Cell(): x(startOfFieldX), y(startOfFieldY), status(Empty){}
Cell :: Cell(unsigned x1, unsigned y1, statusOfCell status1):
x(x1), y(y1), status(status1){}

bool Cell :: operator == (const Cell &c)
{
	return (c.x == x) && (c.y == y) && (c.status == status);
}

Cell Cell :: operator = (const Cell &c)
{
	if(&c == this)
	{
		return *this;
	}
	else
	{
		this->x = c.x;
		this->y = c.y;
		this->status = c.status;
	}
	return *this;
}

FieldView :: FieldView()
{
	selectedCell.x = startOfFieldX;
	selectedCell.y = startOfFieldY;
	selectedCell.status = Empty;
}

void FieldView :: drawCell(Cell cell) // draws the needed cell
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = cell.x;
	position.Y = cell.y;
	switch(cell.status)
	{
		case(Empty):
		{
			cell == selectedCell ?
				SetConsoleTextAttribute(hConsole, 14 + 9*16):
			    SetConsoleTextAttribute(hConsole, 0);
			for(size_t i = 0; i < 4; ++ i)
			{
				SetConsoleCursorPosition(hConsole, position);
				cout << "    ";
				++position.Y;
			}
		}
		break;

	case(Zero):
		{
			cell == selectedCell ?
				SetConsoleTextAttribute(hConsole, 14 + 9*16):
			    SetConsoleTextAttribute(hConsole, 14);
			SetConsoleCursorPosition(hConsole, position);
			cout << " /\\ ";
			++position.Y;
			SetConsoleCursorPosition(hConsole, position);
			cout << "/  \\";
			++position.Y;
			SetConsoleCursorPosition(hConsole, position);
			cout << "\\  /";
			++position.Y;
			SetConsoleCursorPosition(hConsole, position);
			cout << " \\/ ";
		}
		break;
	case(Cross):
		{
			
			cell == selectedCell ?
				SetConsoleTextAttribute(hConsole, 14 + 9*16):
				SetConsoleTextAttribute(hConsole, 14);
			SetConsoleCursorPosition(hConsole, position);
			cout << "\\  /";
			++position.Y;
			SetConsoleCursorPosition(hConsole, position);
			cout << " \\/ ";
			++position.Y;
			SetConsoleCursorPosition(hConsole, position);
			cout << " /\\ ";
			++position.Y;
			SetConsoleCursorPosition(hConsole, position);
			cout << "/  \\";
		}
	}
}

PossibleEndOfGame FieldView :: upDownLeftRight(int key) // defines whether the player won or not
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int key1;
	PossibleEndOfGame end = enterKey(key);
	if(end == Win)
	{
		return Win;
	}
	else if (end == Lose)
	{
		return Lose;
	}
	else if(end == Friendship && counterOfMoves ==5)
	{
		return end;
	}
	else if (end == Friendship)
	{
		if (key == 13)
		{
		_getch();
		key1 = _getch();
		}
		else if (key == 224)
		{
			key1 = _getch();
		}
	}
	else
	{
		key1 = _getch();
	}
	/*if(key == 224)
	{*/
		switch(key1)
		{
			case (72): // up
				{
					if(selectedCell.y != startOfFieldY )
					{
						int x = (selectedCell.x - startOfFieldX) / sizeOfCell;
						int y = (selectedCell.y - startOfFieldY) / sizeOfCell - 1;
						selectedCell = arrOfCells[x][y];
					}
				}
				break;
			case(80):  // down
				{
					if(selectedCell.y != startOfFieldY + 2 * sizeOfCell)
					{
						int x = (selectedCell.x - startOfFieldX) / sizeOfCell;
						int y = (selectedCell.y - startOfFieldY) / sizeOfCell + 1;
						selectedCell = arrOfCells[x][y];
					}
				}
				break;
			case(75): //  left
				{
					if(selectedCell.x != startOfFieldX)
					{
						int x = (selectedCell.x - startOfFieldX) / sizeOfCell - 1;
						int y = (selectedCell.y - startOfFieldY) / sizeOfCell;
						selectedCell = arrOfCells[x][y];
					}
				}
				break;
			case (77):  // right
				{
 					if(selectedCell.x != startOfFieldX + 2 * sizeOfCell)
					{
						int x = (selectedCell.x - startOfFieldX) / sizeOfCell + 1;
						int y = (selectedCell.y - startOfFieldY) / sizeOfCell;
						selectedCell = arrOfCells[x][y];
					}
				}
				break;
		}
	//}
	return Friendship;
}


PossibleEndOfGame FieldView :: enterKey(int key) // puts Crosses and Zeros
{
	if(key == 13)
	{
		for(size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				if(arrOfCells[j][i] == selectedCell && arrOfCells[j][i].status != Zero && arrOfCells[j][i].status != Cross)				
				{
					arrOfCells[j][i].status = Cross;
					selectedCell.status = Cross;
					draw();
					break;
				}
			}
		}
		++counterOfMoves;
		if (counterOfMoves >= 3)
		{
			PossibleEndOfGame end = win();
			if(end == Win || end == Lose)
			{
				return end;
			}
		}
		if(counterOfMoves == 5)
		{
			PossibleEndOfGame end = win();
			return end;
		}
		while(counterOfMoves != 5)
		{
			unsigned zeroX = rand() % 3;
			unsigned zeroY = rand() % 3;
			if(arrOfCells[zeroX][zeroY].status != Cross && arrOfCells[zeroX][zeroY].status != Zero)
			{
				arrOfCells[zeroX][zeroY].status = Zero;
				draw();				
				if (counterOfMoves >= 3)
				{
					PossibleEndOfGame end = win();
					if(end == Win || end == Lose)
					{
						return end;
					}
				}
				break;
			}
		}
					
	}
	return Friendship;
}



PossibleEndOfGame FieldView :: win() // checks our field for win or lose
{
	PossibleEndOfGame end;
	statusOfCell helpStatus;
	Cell helpCell;
	bool help;
	// checking rows
	for(size_t i = 0; i < 3; ++i)
	{
		helpCell = arrOfCells[0][i];
		for (size_t j = 0; j < 3; ++j)
		{
			if(j > 0)
			{
				
				if(helpCell.status == arrOfCells[j][i].status && helpCell.status != Empty && arrOfCells[j][i].status != Empty)
				{
					help = true;
				}
				else
				{
					help = false;
					break;
				}
			}
		}
		if(help == true)
		{
			break;
		}
	}
		if(help)
		{
			helpStatus = helpCell.status;
			if(helpStatus == Cross)
			{
				end = Win;
				return end;
			}
			else if(helpStatus == Zero)
			{
				end = Lose;
				return end;
			}
			else
			{
				end = Friendship;
			}
		}
	
		//checking columns
	for(size_t i = 0; i < 3; ++i)
	{
		helpCell = arrOfCells[i][0];
		for (size_t j = 0; j < 3; ++j)
		{
			if(j > 0)
			{
				if(helpCell.status == arrOfCells[i][j].status && helpCell.status != Empty && arrOfCells[i][j].status != Empty)
				{
					help = true;
				}
				else
				{
					help = false;
					break;
				}

			}

		}
		if(help == true)
		{
			break;
		}
	}
		if(help)
		{
			helpStatus = helpCell.status;
			if(helpStatus == Cross)
			{
				end = Win;
				return end;
			}
			else if(helpStatus == Zero)
			{
				end = Lose;
				return end;
			}
			else
			{
				end = Friendship;
			}
		}
	
	
	//checking the firs diagonal
	for(size_t i = 1; i < 3; ++i)
	{
		helpCell = arrOfCells[0][0];
		if(helpCell.status == arrOfCells[i][i].status && helpCell.status != Empty && arrOfCells[i][i].status != Empty)
		{
			help = true;
		}
		else
		{
			help = false;
			break;
		}
	}
	if(help)
	{
		helpStatus = helpCell.status;
			
		if(helpStatus == Cross)
		{
			end = Win;
			return end;
		}
		else if(helpStatus == Zero)
		{
			end = Lose;
			return end;
		}
		else
		{
			end = Friendship;
		}
	}
	
	// checking the second diagonal
	for(size_t i = 1; i < 3; ++i)
	{
		helpCell = arrOfCells[2][0];
		if(helpCell.status == arrOfCells[2-i][i].status && helpCell.status != Empty && arrOfCells[2 - i][i].status != Empty)
		{
			help = true;
		}
		else
		{
			help = false;
			break;
		}
	}
	if(help)
	{
		helpStatus = helpCell.status;
		if(helpStatus == Cross)
		{
			end = Win;
			return end;
		}
		else if(helpStatus == Zero)
		{
			end = Lose;
			return end;
		}
		else
		{
			end = Friendship;
			return end;
		}
	}
	return Friendship;
}



void FieldView :: draw()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	printInTheCentre("Score:  ", 1, 40);
	cout << score;
	printInTheCentre("    |    |    ", 3, 40);
	printInTheCentre("    |    |    ", 4, 40);
	printInTheCentre("    |    |    ", 5, 40);
	printInTheCentre("    |    |    ", 6, 40);
	printInTheCentre("----+----+----", 7, 40);
	printInTheCentre("    |    |    ", 8, 40);
	printInTheCentre("    |    |    ", 9, 40);
	printInTheCentre("    |    |    ", 10, 40);
	printInTheCentre("    |    |    ", 11, 40);
	printInTheCentre("----+----+----", 12, 40);
	printInTheCentre("    |    |    ", 13, 40);
	printInTheCentre("    |    |    ", 14, 40);
	printInTheCentre("    |    |    ", 15, 40);
	printInTheCentre("    |    |    ", 16, 40);
	printInTheCentre("Press Esc to return to main menu", 19, 40);
	if(o == 0)
	{
	array(arrOfCells);
	++o;
	}
	for(size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 3; ++j)
		{
			{
				drawCell(arrOfCells[j][i]);
			}
		}
	}
}


View * FieldView :: handle()
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	View * newV = NULL;
	int key = _getch();
	while(key)
	{
		if(key == 27)
		{
			delete this;
			newV = new StartView;
			return newV;
		}
		else 
        if (key == 13)
		{
			PossibleEndOfGame end = upDownLeftRight(key);
			if (end == Win)
			{
				++ score;
				SetConsoleTextAttribute(hConsole, 14);
				printInTheCentre("Score:  ", 1, 40);
				cout << score;
				SetConsoleTextAttribute(hConsole, 9);
				printInTheCentre("Congratulations, you won!!!", 17, 40);
				int key2 = _getch();
				if(key2 == 13)
				{
					clean();
					draw();
					newV = this;
					counterOfMoves = 0;
					array(arrOfCells);
					SetConsoleTextAttribute(hConsole, 0 + 9*16);
					for(size_t i = 0; i < 3; ++i)
					{
						for (size_t j = 0; j < 3; ++j)
						{
							{
								drawCell(arrOfCells[j][i]);
							}
						}
					}
					selectedCell = arrOfCells[0][0];
					SetConsoleTextAttribute(hConsole, 14);
					printInTheCentre("          ", 18, 40);
					return newV;
				}
				else if(key2 == 27)
				{
					clean();
					score = 0;
					counterOfMoves = 0;
					array(arrOfCells);
					newV = new StartView;
			        return newV;
				}
			}
		    else
			if(end == Lose)
			{
				draw();
				SetConsoleTextAttribute(hConsole, 9);
				printInTheCentre("You lost(((", 17, 40);
				int key2 = _getch();
				if(key2 == 13)
				{
					counterOfMoves = 0;
					array(arrOfCells);
					newV = new ResulView();
					return newV;
				}
				else if(key2 == 27)
				{
					return newV;
				}
				else
				{
					continue;
				}
			}
			else if(end == Friendship && counterOfMoves == 5)
			{	
				SetConsoleTextAttribute(hConsole, 9);
				printInTheCentre("Friendship wins!!!", 17, 40);
				int key2 = _getch();
				if(key2 == 13)
				{
					newV = this;
					counterOfMoves = 0;
					array(arrOfCells);
					SetConsoleTextAttribute(hConsole, 0 + 9*16);
					for(size_t i = 0; i < 3; ++i)
					{
						for (size_t j = 0; j < 3; ++j)
						{
							{
								drawCell(arrOfCells[j][i]);
							}
						}
					}
					selectedCell = arrOfCells[0][0];
					SetConsoleTextAttribute(hConsole, 14);
					printInTheCentre("                  ", 17, 40);
					return newV;
				}
				else if(key2 == 27)
				{
					return newV;
				}
			}
		}
		else if(key == 224)
		{
			upDownLeftRight(key);
			draw();
        }
		
		draw();
		key = _getch();
	}
}	

