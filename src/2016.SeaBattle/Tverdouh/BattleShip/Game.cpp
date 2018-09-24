#include "GameView.h"
#include "MenuView.h"


GameView::GameView(EndStatus** matrix, WarShip* _navy) :selectX(0), selectY(0), counterOfYourShips(20),
counterOfEnemyShips(20), lines_x(consoleW * 14.5 / 8), lines_y(consoleH * 34 / 5), counter(0), score(100)
{
	navy = new WarShip[10];
	for (int i = 0; i < 10; ++i)
	{
		navy[i] = _navy[i];
		for (int j = 0; j < 10; ++j)
		{
			if (matrix[i][j] == Ship)
			{
				playerField[i][j] = ShipF;
			}
			else
			{
				playerField[i][j] = EmptyF;
			}
			computerPort[i][j] = EmptyField;
			computerField[i][j] = EmptyF;
		}
	}
	enemyNavyInitializer();
}

void GameView::drawMenu()
{
	printField();
	printAllYourCells();
	placeComputerShips();
	printAllEnemyCells(false);
}

void GameView::draw()
{

	bool choise = false;
	while ((counterOfYourShips > 0 && counterOfEnemyShips > 0) && !choise)
	{
		switch (_getch())
		{

		case Right:
			if (selectX < 9)
			{
				++selectX;
				printAllEnemyCells(false);
			}
			break;
		case Left:
			if (selectX > 0)
			{
				--selectX;
				printAllEnemyCells(false);
			}
			break;
		case Down:
			if (selectY < 9)
			{
				++selectY;
				printAllEnemyCells(false);
			}
			break;
		case Up:
			if (selectY > 0)
			{
				--selectY;
				printAllEnemyCells(false);
			}
			break;
		case Enter:
			if (isThereEnemyShip(selectX, selectY))
			{
				computerField[selectX][selectY] = Hit;
				killedEnemyShips();
				--counterOfEnemyShips;
				--score;
			}
			else if (computerPort[selectX][selectY] != Ship && computerField[selectX][selectY] != Pass)
			{
				computerField[selectX][selectY] = Pass;
				enemyTurn();
				--score;
			}
			if (counterOfYourShips == 0)
			{
				printAllEnemyCells(true);
			}
			else
			{
				printAllEnemyCells(false);
			}
			printAllYourCells();
			break;
		}
	}
	if (counterOfYourShips > 0 && counterOfEnemyShips == 0)
	{
		congratulations();
		choise = false;
		clean();
		Menu menu;
		menu.draw();
	}
	else if (!choise)
	{
		loseSign();
		choise = false;
		while (!choise)
		{
			switch (_getch())
			{
			case Enter:
				clean();
				Menu menu;
				menu.draw();
				choise = true;
				break;
			}
		}
	}

}

void GameView::printAllYourCells()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			FightStatus fieldCell = getYourFieldStatus(i, j);
			printYourCell(fieldCell, isSelected(i, j), i, j);
		}
	}
}

void GameView::printAllEnemyCells(bool isEnd)
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			FightStatus fieldCell = getEnemyFightStatus(i, j);
			EndStatus endCell = getEnemyFieldStatus(i, j);
			isEnd ? revealEnemyCell(fieldCell, endCell, i, j) : printEnemyCell(fieldCell, isSelected(i, j), i, j);
		}
	}
}

void GameView::printYourCell(FightStatus fstat, bool isSel, short x, short y)
{
	int posX = x * lines + lines_x;
	int posY = y * lines + lines_y;
	switch (fstat)
	{
	case EmptyF:
		drawRectangle(bluePenSmaller, PenWhite, posX, posY);
		break;
	case ShipF:
		drawRectangle(bluePenSmaller, PenBlue, posX, posY);
		break;
	case Pass:
		drawPoint(false, posX, posY);
		break;
	case Hit:
		drawCross(false, posX, posY);
		break;
	}
}

void GameView::printEnemyCell(FightStatus fstat, bool isSel, short x, short y)
{
	int posX = x * lines + lines_x + 533;
	int posY = y * lines + lines_y;
	if (fstat == EmptyF)
	{
		isSel ? drawRectangle(bluePenSmaller, PenLightBlue, posX, posY) : drawRectangle(bluePenSmaller, PenWhite, posX, posY);
	}
	else if (fstat == Pass)
	{
		drawPoint(isSel, posX, posY);
	}
	else if (fstat == Hit)
	{
		drawCross(isSel, posX, posY);
	}
}

void GameView::revealEnemyCell(FightStatus fstat, EndStatus stat, short x, short y)
{
	int posX = x * lines + lines_x + 533;
	int posY = y * lines + lines_y;
	if (stat == ShipF & fstat != Hit)
	{
		drawRectangle(bluePenSmaller, PenBlue, posX, posY);
	}
	else if (fstat == Pass)
	{
		drawPoint(false, posX, posY);
	}
	else if (fstat == Hit)
	{
		drawCross(false, posX, posY);
	}
	else
	{
		drawRectangle(bluePenSmaller, PenWhite, posX, posY);
	}
}

bool GameView::isSelected(int x, int y)
{
	return x == selectX && y == selectY;
}

FightStatus GameView::getYourFieldStatus(int x, int y) const
{
	return playerField[x][y];
}

EndStatus GameView::getEnemyFieldStatus(int x, int y) const
{
	return computerPort[x][y];
}

FightStatus GameView::getEnemyFightStatus(int x, int y) const
{
	return computerField[x][y];
}

void GameView::enemyNavyInitializer()
{
	enemyNavy = new WarShip[10];
	enemyNavy[0].size(4);
	enemyNavy[0].name("Battleship");
	enemyNavy[0].setDeath(false);
	for (int i = 1; i < 3; ++i)
	{
		enemyNavy[i].size(3);
		enemyNavy[i].name("Cruiser");
		enemyNavy[i].setDeath(false);
	}
	for (int i = 3; i < 6; ++i)
	{
		enemyNavy[i].size(2);
		enemyNavy[i].name("Destroyer");
		enemyNavy[i].setDeath(false);
	}
	for (int i = 6; i < 10; ++i)
	{
		enemyNavy[i].size(1);
		enemyNavy[i].name("Submarine");
		enemyNavy[i].setDeath(false);
	}
}

bool GameView::isThereEnemyShip(int x, int y)
{
	bool toReturn = false;
	if (getEnemyFieldStatus(x, y) == Ship)
	{
		toReturn = true;
	}
	return toReturn;
}

void GameView::enemyTurn()
{
	int randX;
	int randY;
	srand(time(NULL));
	do
	{
		randX = rand() % 10;
		randY = rand() % 10;
	} while (playerField[randX][randY] == Pass || playerField[randX][randY] == Hit);
	if (playerField[randX][randY] == EmptyF)
	{
		playerField[randX][randY] = Pass;
	}
	else
	{
		playerField[randX][randY] = Hit;
		killedYourShips();
		--counterOfYourShips;
		if (counterOfYourShips > 0)
		{
			againEnemyTurn(randX, randY);
		}
	}
}

void GameView::againEnemyTurn(int x, int y)
{
	bool isEnd = false;
	srand(time(NULL));
	while (!isEnd)
	{
		int again = rand() % 4;
		if (again == 0 && x > 0)
		{
			if (playerField[x - 1][y] == ShipF)
			{
				playerField[x - 1][y] = Hit;
				killedYourShips();
				--counterOfYourShips;
				againEnemyTurn(x - 1, y);
			}
			else if (playerField[x - 1][y] == EmptyF)
			{
				playerField[x - 1][y] = Pass;
			}
			else
			{
				enemyTurn();
			}
			isEnd = true;
		}
		else if (again == 1 && y > 0)
		{
			if (playerField[x][y - 1] == ShipF)
			{
				playerField[x][y - 1] = Hit;
				killedYourShips();
				--counterOfYourShips;
				againEnemyTurn(x, y - 1);
				isEnd = true;
			}
			else if (playerField[x][y - 1] == EmptyF)
			{
				playerField[x][y - 1] = Pass;
				isEnd = true;
			}
			else
			{
				enemyTurn();
			}
			isEnd = true;
		}
		else if (again == 2 && x < 9)
		{
			if (playerField[x + 1][y] == ShipF)
			{
				playerField[x + 1][y] = Hit;
				killedYourShips();
				--counterOfYourShips;
				againEnemyTurn(x + 1, y);
				isEnd = true;
			}
			else if (playerField[x + 1][y] == EmptyF)
			{
				playerField[x + 1][y] = Pass;
				isEnd = true;
			}
			else
			{
				enemyTurn();
			}
			isEnd = true;
		}
		else if (again == 3 && y < 9)
		{
			if (playerField[x][y + 1] == ShipF)
			{
				playerField[x][y + 1] = Hit;
				killedYourShips();
				--counterOfYourShips;
				againEnemyTurn(x, y + 1);
				isEnd = true;
			}
			else if (playerField[x][y + 1] == EmptyF)
			{
				playerField[x][y + 1] = Pass;
				isEnd = true;
			}
			else
			{
				enemyTurn();
			}
			isEnd = true;
		}
	}
	printAllYourCells();
}

bool GameView::canPlaceComputerShip(int isHoriz, int x, int y)
{
	bool toReturn = true;
	if (isHoriz == 1)
	{
		if (x < 10 - enemyNavy[counter].getSize() + 1)
		{
			for (int i = x; i < x + enemyNavy[counter].getSize(); ++i)
			{
				if (computerPort[i][y] == Ship || computerPort[i][y] == Buffer)
				{
					toReturn = false;
					break;
				}
			}
		}
		else
		{
			toReturn = false;
		}
	}
	else
	{
		if (y < 10 - enemyNavy[counter].getSize() + 1)
		{
			for (int i = y; i < y + enemyNavy[counter].getSize(); ++i)
			{
				if (computerPort[x][i] == Ship || computerPort[x][i] == Buffer)
				{
					toReturn = false;
					break;
				}
			}
		}
		else
		{
			toReturn = false;
		}
	}
	return toReturn;
}

void GameView::placeComputerShip()
{
	bool isPlaced = false;
	srand(time(NULL));
	while (!isPlaced)
	{
		int isHorizontal = rand() % 2;
		int x = rand() % 10;
		int y = rand() % 10;
		if (canPlaceComputerShip(isHorizontal, x, y))
		{
			enemyNavy[counter].setX(x);
			enemyNavy[counter].setY(y);
			if (isHorizontal == 1)
			{
				enemyNavy[counter].setVector(true);
				for (int i = x; i < x + enemyNavy[counter].getSize(); ++i)
				{
					computerPort[i][y] = Ship;
					if (y > 0 && computerPort[i][y - 1] != Ship)
					{
						computerPort[i][y - 1] = Buffer;
					}
					if (y < 9 && computerPort[i][y + 1] != Ship)
					{
						computerPort[i][y + 1] = Buffer;
					}
				}
				if (x > 0)
				{
					if (computerPort[x - 1][y] != Ship)
					{
						computerPort[x - 1][y] = Buffer;
					}
					if (y > 0 && computerPort[x - 1][y - 1] != Ship)
					{
						computerPort[x - 1][y - 1] = Buffer;
					}
					if (y < 9 && computerPort[x - 1][y + 1] != Ship)
					{
						computerPort[x - 1][y + 1] = Buffer;
					}
				}
				if (x + enemyNavy[counter].getSize() < 10)
				{
					if (computerPort[x + enemyNavy[counter].getSize()][y] != Ship)
					{
						computerPort[x + enemyNavy[counter].getSize()][y] = Buffer;
					}
					if (y > 0 && computerPort[x + enemyNavy[counter].getSize()][y - 1] != Ship)
					{
						computerPort[x + enemyNavy[counter].getSize()][y - 1] = Buffer;
					}
					if (y < 9 && computerPort[x + enemyNavy[counter].getSize()][y + 1] != Ship)
					{
						computerPort[x + enemyNavy[counter].getSize()][y + 1] = Buffer;
					}
				}
			}
			else
			{
				enemyNavy[counter].setVector(false);
				for (int i = y; i < y + enemyNavy[counter].getSize(); ++i)
				{
					computerPort[x][i] = Ship;
					if (x > 0 && computerPort[x - 1][i] != Ship)
					{
						computerPort[x - 1][i] = Buffer;
					}
					if (x < 9 && computerPort[x + 1][i] != Ship)
					{
						computerPort[x + 1][i] = Buffer;
					}
				}
				if (y > 0)
				{
					if (computerPort[x][y - 1] != Ship)
					{
						computerPort[x][y - 1] = Buffer;
					}
					if (x > 0 && computerPort[x - 1][y - 1] != Ship)
					{
						computerPort[x - 1][y - 1] = Buffer;
					}
					if (x < 9 && computerPort[x + 1][y - 1] != Ship)
					{
						computerPort[x + 1][y - 1] = Buffer;
					}
				}
				if (y + enemyNavy[counter].getSize() < 10)
				{
					if (computerPort[x][y + enemyNavy[counter].getSize()] != Ship)
					{
						computerPort[x][y + enemyNavy[counter].getSize()] = Buffer;
					}
					if (x > 0 && computerPort[x - 1][y + enemyNavy[counter].getSize()] != Ship)
					{
						computerPort[x - 1][y + enemyNavy[counter].getSize()] = Buffer;
					}
					if (x < 9 && computerPort[x + 1][y + enemyNavy[counter].getSize()] != Ship)
					{
						computerPort[x + 1][y + enemyNavy[counter].getSize()] = Buffer;
					}
				}
			}
			isPlaced = true;
		}
	}
}

void GameView::placeComputerShips()
{
	for (counter = 0; counter < 10; ++counter)
	{
		placeComputerShip();
	}
}

void GameView::killedYourShips()
{
	for (int i = 0; i < 10; ++i)
	{
		wasShipKilled(navy[i], playerField);
	}
}

void GameView::killedEnemyShips()
{
	for (int i = 0; i < 10; ++i)
	{
		wasShipKilled(enemyNavy[i], computerField);
	}
}

void GameView::wasShipKilled(WarShip navy, FightStatus fstat[10][10])
{
	bool isShipKilled = true;
	if (navy.Horizontal)
	{
		for (int j = navy.Xcoord; j < navy.Xcoord + navy.Size; ++j)
		{
			if (fstat[j][navy.Ycoord] != Hit)
			{
				isShipKilled = false;
				break;
			}
		}
	}
	else
	{
		for (int j = navy.Ycoord; j < navy.Ycoord + navy.Size; ++j)
		{
			if (fstat[navy.Xcoord][j] != Hit)
			{
				isShipKilled = false;
				break;
			}
		}
	}
	if (isShipKilled && navy.Horizontal)
	{
		navy.setDeath(true);
		for (int i = navy.Xcoord; i < navy.Xcoord + navy.Size; ++i)
		{
			if (navy.Ycoord > 0 && fstat[i][navy.Ycoord - 1] != ShipF)
			{
				fstat[i][navy.Ycoord - 1] = Pass;
			}
			if (navy.Ycoord < 9 && fstat[i][navy.Ycoord + 1] != ShipF)
			{
				fstat[i][navy.Ycoord + 1] = Pass;
			}
		}
		if (navy.Xcoord > 0)
		{
			if (fstat[navy.Xcoord - 1][navy.Ycoord] != ShipF)
			{
				fstat[navy.Xcoord - 1][navy.Ycoord] = Pass;
			}
			if (navy.Ycoord > 0 && fstat[navy.Xcoord - 1][navy.Ycoord - 1] != ShipF)
			{
				fstat[navy.Xcoord - 1][navy.Ycoord - 1] = Pass;
			}
			if (navy.Ycoord < 9 && fstat[navy.Xcoord - 1][navy.Ycoord + 1] != ShipF)
			{
				fstat[navy.Xcoord - 1][navy.Ycoord + 1] = Pass;
			}
		}
		if (navy.Xcoord + navy.Size < 10)
		{
			if (fstat[navy.Xcoord + navy.Size][navy.Ycoord] != ShipF)
			{
				fstat[navy.Xcoord + navy.Size][navy.Ycoord] = Pass;
			}
			if (navy.Ycoord > 0 && fstat[navy.Xcoord + navy.Size][navy.Ycoord - 1] != ShipF)
			{
				fstat[navy.Xcoord + navy.Size][navy.Ycoord - 1] = Pass;
			}
			if (navy.Ycoord < 9 && fstat[navy.Xcoord + navy.Size][navy.Ycoord + 1] != ShipF)
			{
				fstat[navy.Xcoord + navy.Size][navy.Ycoord + 1] = Pass;
			}
		}
	}
	else if (isShipKilled && !navy.Horizontal)
	{
		navy.setDeath(true);
		for (int i = navy.Ycoord; i < navy.Ycoord + navy.Size; ++i)
		{
			if (navy.Xcoord > 0 && fstat[navy.Xcoord - 1][i] != ShipF)
			{
				fstat[navy.Xcoord - 1][i] = Pass;
			}
			if (navy.Xcoord < 9 && fstat[navy.Xcoord + 1][i] != ShipF)
			{
				fstat[navy.Xcoord + 1][i] = Pass;
			}
		}
		if (navy.Ycoord > 0)
		{
			if (fstat[navy.Xcoord][navy.Ycoord - 1] != ShipF)
			{
				fstat[navy.Xcoord][navy.Ycoord - 1] = Pass;
			}
			if (navy.Xcoord > 0 && fstat[navy.Xcoord - 1][navy.Ycoord - 1] != ShipF)
			{
				fstat[navy.Xcoord - 1][navy.Ycoord - 1] = Pass;
			}
			if (navy.Xcoord < 9 && fstat[navy.Xcoord + 1][navy.Ycoord - 1] != ShipF)
			{
				fstat[navy.Xcoord + 1][navy.Ycoord - 1] = Pass;
			}
		}
		if (navy.Ycoord + navy.Size < 10)
		{
			if (fstat[navy.Xcoord][navy.Ycoord + navy.Size] != ShipF)
			{
				fstat[navy.Xcoord][navy.Ycoord + navy.Size] = Pass;
			}
			if (navy.Xcoord > 0 && fstat[navy.Xcoord - 1][navy.Ycoord + navy.Size] != ShipF)
			{
				fstat[navy.Xcoord - 1][navy.Ycoord + navy.Size] = Pass;
			}
			if (navy.Xcoord < 9 && fstat[navy.Xcoord + 1][navy.Ycoord + navy.Size] != ShipF)
			{
				fstat[navy.Xcoord + 1][navy.Ycoord + navy.Size] = Pass;
			}
		}
	}
}

void GameView::congratulations()
{
	setCursor(50, 13);
	cout<<"Congratulations!!!";
	setCursor(50, 14);
	cout<<"You have destroyed enemy navy!";
	setCursor(50, 15);
	cout<<"Press Enter to exit";
}

void GameView::loseSign()
{
	setCursor(50, 13);
	cout << "You lose!!!";
	setCursor(50, 14);
	cout << "Press Enter to exit";

}

