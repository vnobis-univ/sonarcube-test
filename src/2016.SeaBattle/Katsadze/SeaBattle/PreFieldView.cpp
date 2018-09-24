#include "PreFieldView.h"
#include "FieldView.h"

Printer mainPann(ConsoleColor::White, ConsoleColor::Black);
Printer eEmpty(ConsoleColor::LightGray, ConsoleColor::White);
Printer almostEmpty(ConsoleColor::LightGreen, ConsoleColor::White);
Printer shipo(ConsoleColor::Cyan, ConsoleColor::White);
Printer notEmpty(ConsoleColor::Blue, ConsoleColor::White);

PreFieldView::PreFieldView() : 
shipCounter(0), horizontal(true), selectedX(0), selectedY(0)
{
	field = new FinalStatus*[10];
	for (int i = 0; i < 10; ++i)
	{
		field[i] = new FinalStatus[10];
		for (int j = 0; j < 10; ++j)
		{
			matrix[i][j] = Empty;
			field[i][j] = EmptyField;
		}
	}
	createShips();
	
}

void PreFieldView::draw()
{
	View::draw();

	printInCenter(3, "Place your ships", mainPann);
	setCursor(5, 5);
	mainPann << "Your field";
	setCursor(50, 5);
	mainPann << "Enemy field";
	
	drawNumeration();
	printField();
	help();
	horizontal = true;
	changePosition();
}

View * PreFieldView::handle()
{
	View* nextView = this;
	bool chosen = false;
	bool isPlaced = false;

	while (!chosen)
	{
		switch (_getch())
		{
		case Enter:
		{
			bool placed = false;
			if (!horizontal && isPlaceForShip())
			{
				placeShip();
				placed = true;
				printAllPlacementCell();
			}
			else if (horizontal && isPlaceForShip())
			{
				placeShip();
				placed = true;
				printAllPlacementCell();
			}
			if (placed)
			{
				if (shipCounter < 9)
				{
					++shipCounter;
				}
				else
				{
					isPlaced = true;
					chosen = true;
					beginGame();
				}
			}
			break;
		}
		case ESCAPE:
			nextView = new StartView();
			chosen = true;
			break;
		case Up:
			if (selectedY > 0)
			{
				deletePlace(72);
				--selectedY;
			}
			changePosition();
			break;
		case Left:
		{
			if (selectedX > 0)
			{
				deletePlace(75);
				--selectedX;
			}
			changePosition();
			break;
		}
		case Right:
		{
			if (selectedX < 10 - ship[shipCounter].getSize() && horizontal || selectedX < 9 && !horizontal)
			{
				deletePlace(77);
				++selectedX;
			}
			changePosition();
			break;
		}
		case Down:

			if (selectedY < 9 && horizontal || selectedY < 10 - ship[shipCounter].getSize() && !horizontal)
			{
				deletePlace(80);
				++selectedY;
			}
			changePosition();
			break;

		case Wrap:
			if (horizontal && selectedY < 10 - ship[shipCounter].getSize() + 1)
			{
				deletePlace(114);
				horizontal = !horizontal;
			}
			else if (!horizontal && selectedX < 10 - ship[shipCounter].getSize() + 1)
			{
				deletePlace(144);
				horizontal = !horizontal;
			}
			changePosition();
			break;
		}
	}
		bool battleStarted = false;
		while (!battleStarted && isPlaced)
		{
			switch (_getch())
			{
			case Enter:
				nextView = new FieldView(field, ship);
				battleStarted = true;
			}
		}
		
	return nextView;
}

void PreFieldView::printField()
{
	drawNet();
}

void PreFieldView::drawNumeration()
{
	for (int i = 0; i < 10; ++i)
	{
		short posX1 = 6 + i * 4;
		short posX2 = 51 + i * 4;
		setCursor(posX1, 7);
		mainPann << numerationString[i];
		setCursor(posX2, 7);
		mainPann << numerationString[i];
	}
	for (int i = 0; i < 10; ++i)
	{
		short posY1 = 9 + i*2 ;
		short posY2 = 9 + i*2;
		setCursor(3, posY1);
		mainPann << numerationInt[i];
		setCursor(48, posY2);
		mainPann << numerationInt[i];
	}
	

}


void PreFieldView::help()
{
	printInCenter(consoleHeight - 2, "Press 'space' to wrap ship", mainPann);
}

PlacementStatus PreFieldView::getStatus(short i, short j) const
{
	return matrix[i][j];
}

void PreFieldView::printAllPlacementCell()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			PlacementStatus matrixCell = getStatus(i, j);
			FinalStatus fieldCell = getFieldStatus(i, j);
			printPlacementCell(matrixCell, fieldCell, i, j);
		}
	}
}

bool PreFieldView::isSelected(short x, short y)
{
	return selectedX == x && selectedY == y;
}

void PreFieldView::printPlacementCell(PlacementStatus stat, FinalStatus estat, short x, short y)
{
	int posX = 5+x*4;
	int posY = 9+y*2;
	if (stat == Empty && estat == EmptyField)
	{
		setCursor(posX,posY);
		eEmpty << "    ";
		setCursor(posX, posY+1);
		eEmpty << "    ";
	}
	else if (stat == TempShip && estat == EmptyField)
	{
		setCursor(posX,posY);
		almostEmpty << "    ";
		setCursor(posX, posY+1);
		almostEmpty << "    ";
	}
	else if ((stat == TempShip && estat == Ship) || (stat == TempShip && estat == Around))
	{
		setCursor(posX,posY);
		notEmpty << "    ";
		setCursor(posX, posY+1);
		notEmpty << "    ";
	}
	if(estat == Ship && stat != TempShip)
	{
		setCursor(posX,posY);
		almostEmpty << "    ";
		setCursor(posX, posY+1);
		almostEmpty << "    ";
	}
	else if(estat == Around && stat != TempShip)
	{
		setCursor(posX,posY);
		shipo << "    ";
		setCursor(posX, posY+1);
		shipo << "    ";
	}
}

void PreFieldView::createShips()
{
	ship = new WarShip[10];
	ship[0].size(4);
	ship[0].name("Ship4");
	for (int i = 1; i < 3; ++i)
	{
		ship[i].size(3);
		ship[i].name("Ship3");
	}
	for (int i = 3; i < 6; ++i)
	{
		ship[i].size(2);
		ship[i].name("Ship2");
	}
	for (int i = 6; i < 10; ++i)
	{
		ship[i].size(1);
		ship[i].name("Ship1");
	}
}

void PreFieldView::changePosition()
{
	if (!horizontal)
	{
		for (int i = selectedY; i < ship[shipCounter].getSize() + selectedY; ++i)
		{
			matrix[selectedX][i] = TempShip;
		}
		
	}
	else
	{
		for (int i = selectedX; i < ship[shipCounter].getSize() + selectedX; ++i)
		{
			matrix[i][selectedY] = TempShip;
		}
	}
	printAllPlacementCell();
}

void PreFieldView::placeShip()
{
	ship[shipCounter].setX(selectedX);
	ship[shipCounter].setY(selectedY);
	if (horizontal)
	{
		ship[shipCounter].setVector(true);
		for (int i = selectedX; i < selectedX + ship[shipCounter].getSize(); ++i)
		{
			field[i][selectedY] = Ship;
			matrix[i][selectedY] = Empty;
			if (selectedY > 0 && field[i][selectedY - 1] != Ship)
			{
				field[i][selectedY - 1] = Around;
			}
			if (selectedY < 9 && field[i][selectedY + 1] != Ship)
			{
				field[i][selectedY + 1] = Around;
			}
		}
		if (selectedX > 0)
		{
			if (field[selectedX - 1][selectedY] != Ship)
			{
				field[selectedX - 1][selectedY] = Around;
			}
			if (selectedY > 0 && field[selectedX - 1][selectedY - 1] != Ship)
			{
				field[selectedX - 1][selectedY - 1] = Around;
			}
			if (selectedY < 9 && field[selectedX - 1][selectedY + 1] != Ship)
			{
				field[selectedX - 1][selectedY + 1] = Around;
			}
		}
		if (selectedX + ship[shipCounter].getSize() < 9)
		{
			if (field[selectedX + ship[shipCounter].getSize()][selectedY] != Ship)
			{
				field[selectedX + ship[shipCounter].getSize()][selectedY] = Around;
			}
			if (selectedY > 0)
			{
				field[selectedX + ship[shipCounter].getSize()][selectedY - 1] = Around;
			}
			if (selectedY < 9)
			{
				field[selectedX + ship[shipCounter].getSize()][selectedY + 1] = Around;
			}
		}
	}
	else
	{
		ship[shipCounter].setVector(false);
		for (int i = selectedY; i < selectedY + ship[shipCounter].getSize(); ++i)
		{
			field[selectedX][i] = Ship;
			matrix[selectedX][i] = Empty;
			if (selectedX > 0 && field[selectedX - 1][i] != Ship)
			{
				field[selectedX - 1][i] = Around;
			}
			if (selectedX < 9 && field[selectedX + 1][i] != Ship)
			{
				field[selectedX + 1][i] = Around;
			}
		}
		if (selectedY > 0)
		{
			if (field[selectedX][selectedY - 1] != Ship)
			{
				field[selectedX][selectedY - 1] = Around;
			}
			if (selectedX > 0 && field[selectedX - 1][selectedY - 1] != Ship)
			{
				field[selectedX - 1][selectedY - 1] = Around;
			}
			if (selectedX < 9 && field[selectedX + 1][selectedY - 1] != Ship)
			{
				field[selectedX + 1][selectedY - 1] = Around;
			}
		}
		if (selectedY + ship[shipCounter].getSize() < 9)
		{
			if (field[selectedX][selectedY + ship[shipCounter].getSize()] != Ship)
			{
				field[selectedX][selectedY + ship[shipCounter].getSize()] = Around;
			}
			if (selectedX > 0 && field[selectedX - 1][selectedY + ship[shipCounter].getSize()] != Ship)
			{
				field[selectedX - 1][selectedY + ship[shipCounter].getSize()] = Around;
			}
			if (selectedX < 9 && field[selectedX + 1][selectedY + ship[shipCounter].getSize()] != Ship)
			{
				field[selectedX + 1][selectedY + ship[shipCounter].getSize()] = Around;
			}
		}
	}
}

bool PreFieldView::isPlaceForShip()
{
	bool result = true;
	if (horizontal)
	{
		for (int i = selectedX; i < selectedX + ship[shipCounter].getSize(); ++i)
		{
			if (field[i][selectedY] == Ship || field[i][selectedY] == Around)
			{
				result = false;
				break;
			}
		}
	}
	else
	{
		for (int i = selectedY; i < selectedY + ship[shipCounter].getSize(); ++i)
		{
			if (field[selectedX][i] == Ship || field[selectedX][i] == Around)
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

FinalStatus PreFieldView::getFieldStatus(short i, short j) const
{
	return field[i][j];
}

void PreFieldView::beginGame()
{
	printInCenter(consoleHeight - 2, "*Press 'Enter' to Start Game*", mainPann);
}

void PreFieldView::deletePlace(unsigned short button)
{
	switch (button)
	{
	case 77:
		if (horizontal)
		{
			if (matrix[selectedX][selectedY] == TempShip)
			{
				matrix[selectedX][selectedY] = Empty;
			}
		}
		else
		{
			for (int i = selectedY; i < selectedY + ship[shipCounter].getSize(); ++i)
			{
				if (matrix[selectedX][i] == TempShip)
				{
					matrix[selectedX][i] = Empty;
				}
			}
		}
		break;
	case 75:
		if (horizontal)
		{
			if (matrix[selectedX + ship[shipCounter].getSize() - 1][selectedY] == TempShip)
			{
				matrix[selectedX + ship[shipCounter].getSize() - 1][selectedY] = Empty;
			}
		}
		else
		{
			for (int i = selectedY; i < selectedY + ship[shipCounter].getSize(); ++i)
			{
				if (matrix[selectedX][i] == TempShip)
				{
					matrix[selectedX][i] = Empty;
				}
			}
		}
		break;
	case 80:
		if (horizontal)
		{
			for (int i = selectedX; i < selectedX + ship[shipCounter].getSize(); ++i)
			{
				if (matrix[i][selectedY] == TempShip)
				{
					matrix[i][selectedY] = Empty;
				}
			}
		}
		else
		{
			if (matrix[selectedX][selectedY] == TempShip)
			{
				matrix[selectedX][selectedY] = Empty;
			}
		}
	case 72:
		if (horizontal)
		{
			for (int i = selectedX; i < selectedX + ship[shipCounter].getSize(); ++i)
			{
				if (matrix[i][selectedY] == TempShip)
				{
					matrix[i][selectedY] = Empty;
				}
			}
		}
		else
		{
			if (matrix[selectedX][selectedY + ship[shipCounter].getSize() - 1] == TempShip)
			{
				matrix[selectedX][selectedY + ship[shipCounter].getSize() - 1] = Empty;
			}
		}
		break;
	case 114:
		if (horizontal)
		{
			unsigned short k = selectedY;
			for (int i = selectedX; i < selectedX + ship[shipCounter].getSize(); ++i)
			{
				matrix[i][selectedY] = Empty;
				matrix[selectedX][k] = TempShip;
				++k;
			}
		}
		else
		{
			unsigned short k = selectedX;
			for (int i = selectedY; i < selectedY + ship[shipCounter].getSize(); ++i)
			{
				matrix[selectedX][i] = Empty;
				matrix[k][selectedY] = TempShip;
				++k;
			}
		}
	}
}
