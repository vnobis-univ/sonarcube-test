#include "StartGameView.h"
#include "GameView.h"
#include "MenuView.h"


void printInTheCentre(string str, int numberOfLine, int consoleWidt);
void setCursor(int xx, int yy);

StartGameView::StartGameView() : lines_x(consoleW * 14.5 / 8), lines_y(consoleH * 34 / 5),
counterOfShip(0), horizontal(true), selectX(0), selectY(0)
{
	field = new EndStatus*[10];
	for (int i = 0; i < 10; ++i)
	{
		field[i] = new EndStatus[10];
		for (int j = 0; j < 10; ++j)
		{
			pole[i][j] = Empty;
			field[i][j] = EmptyField;
		}
	}
	shipsInitialiser();
}

void StartGameView::drawMenu()
{

	setCursor(22,10);
	cout << "Your field";
	setCursor(88, 10);
	cout << "Enemy field";

	printField();
	horizontal = true;
	changeShipPlace();
}

void StartGameView::draw()
{

	bool choise = false;
	bool isPlaced = false;
	while (!choise)
	{
		switch (_getch())
		{

		case Right:
			if (selectX < 10 - ship[counterOfShip].getSize() && horizontal || selectX < 9 && !horizontal)
			{
				deleteTrace(Right);
				++selectX;
			}
			changeShipPlace();
			break;
		case Left:
			if (selectX > 0)
			{
				deleteTrace(Left);
				--selectX;
			}
			changeShipPlace();
			break;
		case Down:
			if (selectY < 9 && horizontal || selectY < 10 - ship[counterOfShip].getSize() && !horizontal)
			{
				deleteTrace(Down);
				++selectY;
			}
			changeShipPlace();
			break;
		case Up:
			if (selectY > 0)
			{
				deleteTrace(Up);
				--selectY;
			}
			changeShipPlace();
			break;
		case Wrap:
			if (horizontal && selectY < 10 - ship[counterOfShip].getSize() + 1)
			{
				deleteTrace(Wrap);
				horizontal = !horizontal;
			}
			else if (!horizontal && selectX < 10 - ship[counterOfShip].getSize() + 1)
			{
				deleteTrace(Wrap);
				horizontal = !horizontal;
			}
			changeShipPlace();
			break;
		case Enter:
			bool is = false;
			if (horizontal && canPlaceShip())
			{
				placeShip();
				is = true;
				printAllPlacementCell();
			}
			else if (!horizontal && canPlaceShip())
			{
				placeShip();
				is = true;
				printAllPlacementCell();
			}
			if (is)
			{
				if (counterOfShip < 9)
				{
					++counterOfShip;
				}
				else
				{
					startOfGame();
					choise = true;
					isPlaced = true;
				}
			}
			break;
		}
	}
	bool startBattle = false;
	while (!startBattle && isPlaced)
	{
		switch (_getch())
		{
		case Enter:
			GameView menu(field, ship);
			menu.drawMenu();
			menu.draw();
			startBattle = true;
		}
	}
}

void StartGameView::printField()
{
	drawNet(lines_x, lines_y);
	drawNet(lines_x + 533, lines_y);
}


PoleStatus StartGameView::getpoleStatus(short i, short j) const
{
	return pole[i][j];
}

void StartGameView::printAllPlacementCell()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			PoleStatus poleCell = getpoleStatus(i, j);
			EndStatus fieldCell = getFieldStatus(i, j);
			printPlacementCell(poleCell, fieldCell, i, j);
		}
	}
}

bool StartGameView::isSelected(short x, short y)
{
	return selectX == x && selectY == y;
}

void StartGameView::printPlacementCell(PoleStatus stat, EndStatus estat, short x, short y)
{
	int posX = x * lines + lines_x;
	int posY = y * lines + lines_y;
	if (stat == Empty && estat == EmptyField)
	{
		drawRectangle(bluePenSmaller, PenWhite, posX, posY);
	}
	else if (stat == TempShip && estat == EmptyField)
	{
		drawRectangle(bluePenSmaller, PenLightBlue, posX, posY);
	}
	else if ((stat == TempShip && estat == Ship) || (stat == TempShip && estat == Buffer))
	{
		drawRectangle(redPenSmaller, PenLightBlue, posX, posY);
	}
	if (estat == Ship && stat != TempShip)
	{
		drawRectangle(bluePenSmaller, PenBlue, posX, posY);
	}
	else if (estat == Buffer && stat != TempShip)
	{
		drawRectangle(bluePenSmaller, PenDarkerWhite, posX, posY);
	}
}

void StartGameView::shipsInitialiser()
{
	ship = new WarShip[10];
	ship[0].size(4);
	ship[0].name("4");
	for (int i = 1; i < 3; ++i)
	{
		ship[i].size(3);
		ship[i].name("3");
	}
	for (int i = 3; i < 6; ++i)
	{
		ship[i].size(2);
		ship[i].name("2");
	}
	for (int i = 6; i < 10; ++i)
	{
		ship[i].size(1);
		ship[i].name("1");
	}
}

void StartGameView::changeShipPlace()
{
	if (horizontal)
	{
		for (int i = selectX; i < ship[counterOfShip].getSize() + selectX; ++i)
		{
			pole[i][selectY] = TempShip;
		}
	}
	else
	{
		for (int i = selectY; i < ship[counterOfShip].getSize() + selectY; ++i)
		{
			pole[selectX][i] = TempShip;
		}
	}
	printAllPlacementCell();
}

bool StartGameView::canPlaceShip()
{
	bool toReturn = true;
	if (horizontal)
	{
		for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
		{
			if (field[i][selectY] == Ship || field[i][selectY] == Buffer)
			{
				toReturn = false;
				break;
			}
		}
	}
	else
	{
		for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
		{
			if (field[selectX][i] == Ship || field[selectX][i] == Buffer)
			{
				toReturn = false;
				break;
			}
		}
	}
	return toReturn;
}

void StartGameView::placeShip()
{
	ship[counterOfShip].setX(selectX);
	ship[counterOfShip].setY(selectY);
	if (horizontal)
	{
		ship[counterOfShip].setVector(true);
		for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
		{
			field[i][selectY] = Ship;
			pole[i][selectY] = Empty;
			if (selectY > 0 && field[i][selectY - 1] != Ship)
			{
				field[i][selectY - 1] = Buffer;
			}
			if (selectY < 9 && field[i][selectY + 1] != Ship)
			{
				field[i][selectY + 1] = Buffer;
			}
		}
		if (selectX > 0)
		{
			if (field[selectX - 1][selectY] != Ship)
			{
				field[selectX - 1][selectY] = Buffer;
			}
			if (selectY > 0 && field[selectX - 1][selectY - 1] != Ship)
			{
				field[selectX - 1][selectY - 1] = Buffer;
			}
			if (selectY < 9 && field[selectX - 1][selectY + 1] != Ship)
			{
				field[selectX - 1][selectY + 1] = Buffer;
			}
		}
		if (selectX + ship[counterOfShip].getSize() < 9)
		{
			if (field[selectX + ship[counterOfShip].getSize()][selectY] != Ship)
			{
				field[selectX + ship[counterOfShip].getSize()][selectY] = Buffer;
			}
			if (selectY > 0)
			{
				field[selectX + ship[counterOfShip].getSize()][selectY - 1] = Buffer;
			}
			if (selectY < 9)
			{
				field[selectX + ship[counterOfShip].getSize()][selectY + 1] = Buffer;
			}
		}
	}
	else
	{
		ship[counterOfShip].setVector(false);
		for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
		{
			field[selectX][i] = Ship;
			pole[selectX][i] = Empty;
			if (selectX > 0 && field[selectX - 1][i] != Ship)
			{
				field[selectX - 1][i] = Buffer;
			}
			if (selectX < 9 && field[selectX + 1][i] != Ship)
			{
				field[selectX + 1][i] = Buffer;
			}
		}
		if (selectY > 0)
		{
			if (field[selectX][selectY - 1] != Ship)
			{
				field[selectX][selectY - 1] = Buffer;
			}
			if (selectX > 0 && field[selectX - 1][selectY - 1] != Ship)
			{
				field[selectX - 1][selectY - 1] = Buffer;
			}
			if (selectX < 9 && field[selectX + 1][selectY - 1] != Ship)
			{
				field[selectX + 1][selectY - 1] = Buffer;
			}
		}
		if (selectY + ship[counterOfShip].getSize() < 9)
		{
			if (field[selectX][selectY + ship[counterOfShip].getSize()] != Ship)
			{
				field[selectX][selectY + ship[counterOfShip].getSize()] = Buffer;
			}
			if (selectX > 0 && field[selectX - 1][selectY + ship[counterOfShip].getSize()] != Ship)
			{
				field[selectX - 1][selectY + ship[counterOfShip].getSize()] = Buffer;
			}
			if (selectX < 9 && field[selectX + 1][selectY + ship[counterOfShip].getSize()] != Ship)
			{
				field[selectX + 1][selectY + ship[counterOfShip].getSize()] = Buffer;
			}
		}
	}
}

void StartGameView::deleteTrace(Buttons button)
{
	switch (button)
	{
	case Right:
		if (horizontal)
		{
			if (pole[selectX][selectY] == TempShip)
			{
				pole[selectX][selectY] = Empty;
			}
		}
		else
		{
			for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
			{
				if (pole[selectX][i] == TempShip)
				{
					pole[selectX][i] = Empty;
				}
			}
		}
		break;
	case Left:
		if (horizontal)
		{
			if (pole[selectX + ship[counterOfShip].getSize() - 1][selectY] == TempShip)
			{
				pole[selectX + ship[counterOfShip].getSize() - 1][selectY] = Empty;
			}
		}
		else
		{
			for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
			{
				if (pole[selectX][i] == TempShip)
				{
					pole[selectX][i] = Empty;
				}
			}
		}
		break;
	case Down:
		if (horizontal)
		{
			for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
			{
				if (pole[i][selectY] == TempShip)
				{
					pole[i][selectY] = Empty;
				}
			}
		}
		else
		{
			if (pole[selectX][selectY] == TempShip)
			{
				pole[selectX][selectY] = Empty;
			}
		}
	case Up:
		if (horizontal)
		{
			for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
			{
				if (pole[i][selectY] == TempShip)
				{
					pole[i][selectY] = Empty;
				}
			}
		}
		else
		{
			if (pole[selectX][selectY + ship[counterOfShip].getSize() - 1] == TempShip)
			{
				pole[selectX][selectY + ship[counterOfShip].getSize() - 1] = Empty;
			}
		}
		break;
	case Wrap:
		if (horizontal)
		{
			int k = selectY;
			for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
			{
				pole[i][selectY] = Empty;
				pole[selectX][k] = TempShip;
				++k;
			}
		}
		else
		{
			int k = selectX;
			for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
			{
				pole[selectX][i] = Empty;
				pole[k][selectY] = TempShip;
				++k;
			}
		}
	}
}

void StartGameView::startOfGame()
{
	setCursor(50, 10);
	cout<<"Press Enter to start...";

}

EndStatus StartGameView::getFieldStatus(short i, short j) const
{
	return field[i][j];
}
