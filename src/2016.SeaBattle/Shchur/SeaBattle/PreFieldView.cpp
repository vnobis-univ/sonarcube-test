#include "PreFieldView.h"
#include "FieldView.h"

Printer penPreBat(ConsoleColor::White, ConsoleColor::Red);
Printer brownPenPreBat(ConsoleColor::White, ConsoleColor::Brown);

PreFieldView::PreFieldView() : language(Lokalization::En), landslide_x(consoleWidth * 14.5 / 8), landslide_y(consoleHeight * 34 / 5),
counterOfShip(0), horizontal(true), selectX(0), selectY(0)
{
	field = new EndStatus*[10];
	for (int i = 0; i < 10; ++i)
	{
		field[i] = new EndStatus[10];
		for (int j = 0; j < 10; ++j)
		{
			scheme[i][j] = Empty;
			field[i][j] = EmptyField;
		}
	}
	shipsInitialiser();
	
}
PreFieldView::PreFieldView(Lokalization lang) : language(lang), landslide_x(consoleWidth * 14.5 / 8), landslide_y(consoleHeight * 34 / 5),
counterOfShip(0), horizontal(true), selectX(0), selectY(0)
{
	field = new EndStatus*[10];
	for (int i = 0; i < 10; ++i)
	{
		field[i] = new EndStatus[10];
		for (int j = 0; j < 10; ++j)
		{
			scheme[i][j] = Empty;
			field[i][j] = EmptyField;
		}
	}
	shipsInitialiser();
}

void PreFieldView::draw()
{
	View::draw();
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(3, "Place your ships", penPreBat);
		setCursor(consoleWidth / 5, 5);
		penPreBat << "Your field";
		setCursor(consoleWidth / 1.5, 5);
		penPreBat << "Enemy field";
	}
	else
	{
		printTextOnTheCenter(3, "Розмістіть кораблі", penPreBat);
		setCursor(consoleWidth / 5, 5);
		penPreBat << "Ваше поле";
		setCursor(consoleWidth / 1.5, 5);
		penPreBat << "Вороже поле";
	}
	drawAlphabet();
	printField();
	help();
	horizontal = true;
	changeShipPlace();
}

View * PreFieldView::handle()
{
	View* nextView = this;
	bool choise = false;
	bool isPlaced = false;
	while (!choise)
	{
		switch (_getch())
		{
		case ESCAPE:
			nextView = new StartView(language);
			choise = true;
			break;
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
			nextView = new FieldView(language, field, ship);
			startBattle = true;
		}
	}
	return nextView;
}

void PreFieldView::printField()
{
	drawNet(landslide_x, landslide_y);
	drawNet(landslide_x + 533, landslide_y);
}

void PreFieldView::drawAlphabet()
{
	if (language == Lokalization::En)
	{
		for (int i = 0; i < 10; ++i)
		{
			short posX = 11 + i * 2;
			setCursor(posX, 7);
			brownPenPreBat << alphabetEn[i];
		}
		for (int i = 0; i < 10; ++i)
		{
			short posX = 49 + i * 2;
			setCursor(posX, 7);
			brownPenPreBat << alphabetEn[i];
		}
	}
	else
	{
		for (int i = 0; i < 10; ++i)
		{
			short posX = 11 + i * 2;
			setCursor(posX, 7);
			brownPenPreBat << alphabetUa[i];
		}
		for (int i = 0; i < 10; ++i)
		{
			short posX = 49 + i * 2;
			setCursor(posX, 7);
			brownPenPreBat << alphabetUa[i];
		}
	}
	drawNumbers(landslide_x, landslide_y);
	drawNumbers(landslide_x + 533, landslide_y);
}

PlacementStatus PreFieldView::getSchemeStatus(short i, short j) const
{
	return scheme[i][j];
}

void PreFieldView::printAllPlacementCell()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			PlacementStatus schemeCell = getSchemeStatus(i, j);
			EndStatus fieldCell = getFieldStatus(i, j);
			printPlacementCell(schemeCell, fieldCell, i, j);
		}
	}
}

bool PreFieldView::isSelected(short x, short y)
{
	return selectX == x && selectY == y;
}

void PreFieldView::printPlacementCell(PlacementStatus stat, EndStatus estat, short x, short y)
{
	int posX = x * landslide + landslide_x;
	int posY = y * landslide + landslide_y;
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
	if(estat == Ship && stat != TempShip)
	{
		drawRectangle(bluePenSmaller, PenBlue, posX, posY);
	}
	else if(estat == Buffer && stat != TempShip)
	{
		drawRectangle(bluePenSmaller, PenDarkerWhite, posX, posY);
	}
}

void PreFieldView::shipsInitialiser()
{
	ship = new WarShip[10];
	ship[0].size(4);
	ship[0].name("Battleship");
	for (int i = 1; i < 3; ++i)
	{
		ship[i].size(3);
		ship[i].name("Cruiser");
	}
	for (int i = 3; i < 6; ++i)
	{
		ship[i].size(2);
		ship[i].name("Destroyer");
	}
	for (int i = 6; i < 10; ++i)
	{
		ship[i].size(1);
		ship[i].name("Submarine");
	}
}

void PreFieldView::changeShipPlace()
{
	if (horizontal)
	{
		for (int i = selectX; i < ship[counterOfShip].getSize() + selectX; ++i)
		{
			scheme[i][selectY] = TempShip;
		}
	}
	else
	{
		for (int i = selectY; i < ship[counterOfShip].getSize() + selectY; ++i)
		{
			scheme[selectX][i] = TempShip;
		}
	}
	printAllPlacementCell();
}

bool PreFieldView::canPlaceShip()
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

void PreFieldView::placeShip()
{
	ship[counterOfShip].setX(selectX);
	ship[counterOfShip].setY(selectY);
	if (horizontal)
	{
		ship[counterOfShip].setVector(true);
		for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
		{
			field[i][selectY] = Ship;
			scheme[i][selectY] = Empty;
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
			scheme[selectX][i] = Empty;
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

void PreFieldView::deleteTrace(Buttons button)
{
	switch (button)
	{
	case Right:
		if (horizontal)
		{
			if (scheme[selectX][selectY] == TempShip)
			{
				scheme[selectX][selectY] = Empty;
			}
		}
		else
		{
			for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
			{
				if (scheme[selectX][i] == TempShip)
				{
					scheme[selectX][i] = Empty;
				}
			}
		}
		break;
	case Left:
		if (horizontal)
		{
			if (scheme[selectX + ship[counterOfShip].getSize() - 1][selectY] == TempShip)
			{
				scheme[selectX + ship[counterOfShip].getSize() - 1][selectY] = Empty;
			}
		}
		else
		{
			for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
			{
				if (scheme[selectX][i] == TempShip)
				{
					scheme[selectX][i] = Empty;
				}
			}
		}
		break;
	case Down:
		if (horizontal)
		{
			for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
			{
				if (scheme[i][selectY] == TempShip)
				{
					scheme[i][selectY] = Empty;
				}
			}
		}
		else
		{
			if (scheme[selectX][selectY] == TempShip)
			{
				scheme[selectX][selectY] = Empty;
			}
		}
	case Up:
		if (horizontal)
		{
			for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
			{
				if (scheme[i][selectY] == TempShip)
				{
					scheme[i][selectY] = Empty;
				}
			}
		}
		else
		{
			if (scheme[selectX][selectY + ship[counterOfShip].getSize() - 1] == TempShip)
			{
				scheme[selectX][selectY + ship[counterOfShip].getSize() - 1] = Empty;
			}
		}
		break;
	case Wrap:
		if (horizontal)
		{
			int k = selectY;
			for (int i = selectX; i < selectX + ship[counterOfShip].getSize(); ++i)
			{
				scheme[i][selectY] = Empty;
				scheme[selectX][k] = TempShip;
				++k;
			}
		}
		else
		{
			int k = selectX;
			for (int i = selectY; i < selectY + ship[counterOfShip].getSize(); ++i)
			{
				scheme[selectX][i] = Empty;
				scheme[k][selectY] = TempShip;
				++k;
			}
		}
	}
}

void PreFieldView::startOfGame()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(consoleHeight - 2, "-> Start a battle <-", brownPenPreBat);
	}
	else
	{
		printTextOnTheCenter(consoleHeight - 2, "->  Почати битву <-", brownPenPreBat);
	}
}

void PreFieldView::help()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(consoleHeight - 5, "Press r to wrap ship", penPreBat);
	}
	else
	{
		printTextOnTheCenter(consoleHeight - 5, "Натисніть r щоб повернути корабель", penPreBat);
	}
}

EndStatus PreFieldView::getFieldStatus(short i, short j) const
{
	return field[i][j];
}
