#include "FieldView.h"

Printer penBat(ConsoleColor::White, ConsoleColor::Red);
Printer brownPenBat(ConsoleColor::White, ConsoleColor::Brown);

FieldView::FieldView(Lokalization lang, EndStatus** matrix, WarShip* _navy) : language(lang), selectX(0), selectY(0), counterOfYourShips(20),
counterOfEnemyShips(20), landslide_x(consoleWidth * 14.5 / 8), landslide_y(consoleHeight * 34 / 5), counter(0), score(100)
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

void FieldView::draw()
{
	View::draw();
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(3, "Destroy enemy navy", penBat);
		setCursor(consoleWidth / 5, 5);
		penBat << "Your field";
		setCursor(consoleWidth / 1.5, 5);
		penBat << "Enemy field";
	}
	else
	{
		printTextOnTheCenter(3, "Знищіть ворожий флот", penBat);
		setCursor(consoleWidth / 5, 5);
		penBat << "Ваше поле";
		setCursor(consoleWidth / 1.5, 5);
		penBat << "Вороже поле";
	}
	drawAlphabet();
	printField();
	printAllYourCells();
	placeComputerShips();
	printAllEnemyCells(false);
}

View * FieldView::handle()
{
	View* nextView = this;
	bool choise = false;
	while ((counterOfYourShips > 0 && counterOfEnemyShips > 0) && !choise)
	{
		switch (_getch())
		{
		case ESCAPE:
			nextView = new StartView(language);
			choise = true;
			break;
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
			else if(computerPort[selectX][selectY] != Ship && computerField[selectX][selectY] != Pass)
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
		scoreHandler();
		choise = false;
		nextView = new HighscoresView(language);
	}
	else if(!choise)
	{
		loseSign();
		choise = false;
		while (!choise)
		{
			switch (_getch())
			{
			case Enter:
				nextView = new StartView(language);
				choise = true;
				break;
			}
		}
	}
	return nextView;
}

void FieldView::printAllYourCells()
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

void FieldView::printAllEnemyCells(bool isEnd)
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

void FieldView::printYourCell(FightStatus fstat, bool isSel, short x, short y)
{
	int posX = x * landslide + landslide_x;
	int posY = y * landslide + landslide_y;
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

void FieldView::printEnemyCell(FightStatus fstat, bool isSel, short x, short y)
{
	int posX = x * landslide + landslide_x + 533;
	int posY = y * landslide + landslide_y;
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

void FieldView::revealEnemyCell(FightStatus fstat, EndStatus stat, short x, short y)
{
	int posX = x * landslide + landslide_x + 533;
	int posY = y * landslide + landslide_y;
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

bool FieldView::isSelected(int x, int y) 
{
	return x == selectX && y == selectY;
}

FightStatus FieldView::getYourFieldStatus(int x, int y) const
{
	return playerField[x][y];
}

EndStatus FieldView::getEnemyFieldStatus(int x, int y) const
{
	return computerPort[x][y];
}

FightStatus FieldView::getEnemyFightStatus(int x, int y) const
{
	return computerField[x][y];
}

void FieldView::enemyNavyInitializer()
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

bool FieldView::isThereEnemyShip(int x, int y)
{
	bool toReturn = false;
	if (getEnemyFieldStatus(x, y) == Ship)
	{
		toReturn = true;
	}
	return toReturn;
}

void FieldView::enemyTurn()
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

void FieldView::againEnemyTurn(int x, int y)
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
			else if(playerField[x - 1][y] == EmptyF)
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

bool FieldView::canPlaceComputerShip(int isHoriz, int x, int y)
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

void FieldView::placeComputerShip()
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

void FieldView::placeComputerShips()
{
	for (counter = 0; counter < 10; ++counter)
	{
		placeComputerShip();
	}
}

void FieldView::killedYourShips()
{
	for (int i = 0; i < 10; ++i)
	{
		wasShipKilled(navy[i], playerField);
	}
}

void FieldView::killedEnemyShips()
{
	for (int i = 0; i < 10; ++i)
	{
		wasShipKilled(enemyNavy[i], computerField);
	}
}

void FieldView::wasShipKilled(WarShip navy, FightStatus fstat[10][10])
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

void FieldView::congratulations()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(consoleHeight - 7, "Congratulations!!!", penBat);
		printTextOnTheCenter(consoleHeight - 6, "You have destroyed enemy navy!", penBat);
		printTextOnTheCenter(consoleHeight - 5, "Your score: " + to_string(score), penBat);
		printTextOnTheCenter(consoleHeight - 2, "Press Enter to exit", penBat);
	}
	else
	{
		printTextOnTheCenter(consoleHeight - 7, "Вітання!!!", penBat);
		printTextOnTheCenter(consoleHeight - 6, "Ви знищили ворожий флот!", penBat);
		printTextOnTheCenter(consoleHeight - 5, "Ваш рахунок: " + to_string(score), penBat);
		printTextOnTheCenter(consoleHeight - 2, "Натисніть Enter для виходу", penBat);
	}
}

void FieldView::loseSign()
{
	if (language == Lokalization::En)
	{
		printTextOnTheCenter(consoleHeight - 5, "You losed!", penBat);
		printTextOnTheCenter(consoleHeight - 4, "Your score: " + to_string(score), penBat);
		printTextOnTheCenter(consoleHeight - 2, "Press Enter to exit", penBat);
	}
	else
	{
		printTextOnTheCenter(consoleHeight - 5, "Ви програли!", penBat);
		printTextOnTheCenter(consoleHeight - 4, "Ваш рахунок: " + to_string(score), penBat);
		printTextOnTheCenter(consoleHeight - 2, "Натисніть Enter для виходу", penBat);
	}
}

string FieldView::getName()
{
	string name;
	char symbol = 0;
	short counter = 0;
	while (counter < 12 && symbol != 13)
	{
		symbol = _getch();
		if (symbol == 8 && counter > 0)//Backspace
		{
			name.pop_back();
			if (language == Lokalization::En)
			{
				setCursor(consoleWidth / 3 + 16 + counter, consoleHeight - 4);
				cout << " ";
				setCursor(consoleWidth / 3 + 16 + counter, consoleHeight - 4);
			}
			else
			{
				setCursor(consoleWidth / 3 + 18 + counter, consoleHeight - 4);
				cout << " ";
				setCursor(consoleWidth / 3 + 18 + counter, consoleHeight - 4);
			}
			if (counter != 0)
			{
				--counter;
			}
		}
		if (symbol == 13 && name.size() == 0)//Enter
		{
			name = "Stranger";
		}
		if (symbol != 13 && symbol != 8)
		{
			name += symbol;
			cout << symbol;
			++counter;
		}
	}
	return name;
}

void FieldView::scoreHandler()
{
	Result result[10];
	ifstream in("Highscore.txt");
	for (int i = 0; i < 10; ++i)
	{
		in >> result[i];
	}
	bool isAchieve = isInTable(score);
	if (isAchieve)
	{
		ofstream out("Highscore.txt");
		showCursor(true);
		setCursor(consoleWidth / 3, consoleHeight - 4);
		language == Lokalization::En ? cout << "Enter your name: " : cout << "Введіть ваше ім'я: ";
		string name = getName();
		showCursor(false);
		bool exit = false;
		if (name.size() >= 12)
		{
			language == Lokalization::En ? printTextOnTheCenter(consoleHeight - 3, "-> Continue <-", brownPenBat) :
				printTextOnTheCenter(consoleHeight - 3, "-> Продовжити <-", brownPenBat);
			while (!exit)
			{
				switch (_getch())
				{
				case Enter:
					exit = true;
					break;
				}
			}
		}
		Result newResult;
		newResult.name = name;
		newResult.score = score;
		putInTable(newResult, result, out);
	}
}
