#include "FieldView.h"

Printer mainPan(ConsoleColor::White, ConsoleColor::Black);
Printer _EmptyMyField(ConsoleColor::LightGray, ConsoleColor::White);
Printer sShip(ConsoleColor::LightRed, ConsoleColor::White);
Printer hit(ConsoleColor::Red, ConsoleColor::White);
Printer pass(ConsoleColor::Yellow, ConsoleColor::White);
Printer _EmptyBotField(ConsoleColor::DarkGray, ConsoleColor::White);
Printer tempPen(ConsoleColor::Blue, ConsoleColor::White);

void FieldView::printYourCell(FightStatus fstat, bool isSel, short x, short y)
{
	short posX = 5+x*4 ;
	short posY = 9+y*2 ;
	switch (fstat)
	{
	case EmptyF:
	{
		setCursor(posX, posY);
		_EmptyMyField << "    ";
		setCursor(posX, posY+1);
		_EmptyMyField << "    ";
		break;
	}
	case ShipF:
	{
		setCursor(posX,posY);
		sShip << "    ";
		setCursor(posX, posY+1);
		sShip << "    ";
		break;
	}
	case Pass:
	{
		setCursor(posX,posY);
		pass << "    ";
		setCursor(posX, posY+1);
		pass << "    ";
		break;
	}
	case Hit:
	{
		setCursor(posX, posY);
		hit << "    ";
		setCursor(posX, posY+1);
		hit << "    ";
		break;
	}
	}
}

FieldView::FieldView( FinalStatus** matrix, WarShip* _navy) : selectedX(0), selectedY(0), counterOfYourShips(20),
counterOfEnemyShips(20),counter(0), score(100)
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
	createBotShips();
}

void FieldView::createBotShips()
{
	botNavy= new WarShip[10];
	botNavy[0].size(4);
	botNavy[0].name("Ship4");
	botNavy[0].setReady(false);
	for (int i = 1; i < 3; ++i)
	{
		botNavy[i].size(3);
		botNavy[i].name("Ship3");
		botNavy[i].setReady(false);
	}
	for (int i = 3; i < 6; ++i)
	{
		botNavy[i].size(2);
		botNavy[i].name("Ship2");
		botNavy[i].setReady(false);
	}
	for (int i = 6; i < 10; ++i)
	{
		botNavy[i].size(1);
		botNavy[i].name("Ship1");
		botNavy[i].setReady(false);
	}
}

void FieldView::draw()
{
	View::draw();
	
	setCursor(5, 5);
	mainPan<< "Your field";
	setCursor(50, 5);
	mainPan << "Enemy field";
	
	drawNumeration();
	printField();
	printAllYourCells();
	placeBotShips();
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
			nextView = new StartView();
			choise = true;
			break;
		case Right:
			if (selectedX < 9)
			{
				++selectedX;
				printAllEnemyCells(false);
			}
			break;
		case Left:
			if (selectedX > 0)
			{
				--selectedX;
				printAllEnemyCells(false);
			}
			break;
		case Down:
			if (selectedY < 9)
			{
				++selectedY;
				printAllEnemyCells(false);
			}
			break;
		case Up:
			if (selectedY > 0)
			{
				--selectedY;
				printAllEnemyCells(false);
			}
			break;
		case Enter:
			if (isThereEnemyShip(selectedX, selectedY))
			{
				computerField[selectedX][selectedY] = Hit;
				killedEnemyShips();
				--counterOfEnemyShips;
				--score;
			}
			else if(computerPort[selectedX][selectedY] != Ship && computerField[selectedX][selectedY] != Pass)
			{
				computerField[selectedX][selectedY] = Pass; 
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
		nextView = new HighscoresView();
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
				nextView = new StartView();
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
			FinalStatus endCell = getEnemyFieldStatus(i, j);
			isEnd ? revealEnemyCell(fieldCell, endCell, i, j) : printEnemyCell(fieldCell, isSelected(i, j), i, j);

		}
	}
}
FightStatus FieldView::getEnemyFightStatus(int x, int y) const
{
	return computerField[x][y];
}


void FieldView::printEnemyCell(FightStatus fstat, bool isSel, short x, short y)
{
	int posX = 50 + x * 4;
	int posY = 9 + y * 2;
	if (fstat == EmptyF)
	{
		if (isSel)
		{
			setCursor(posX, posY);
			_EmptyBotField << "    ";
			setCursor(posX, posY + 1);
			_EmptyBotField << "    ";
		}
		else
		{
			setCursor(posX, posY);
			_EmptyMyField << "    ";
			setCursor(posX, posY + 1);
			_EmptyMyField << "    ";
		}
	}
	else if (fstat == Pass)
	{
		setCursor(posX, posY);
		pass << "    ";
		setCursor(posX, posY + 1);
		pass << "    ";
	}
	else if (fstat == Hit)
	{
		setCursor(posX, posY);
		hit << "    ";
		setCursor(posX, posY+1);
		hit << "    ";
	}
}

void FieldView::revealEnemyCell(FightStatus fstat, FinalStatus stat, short x, short y)
{
	int posX = 50 + x * 4;
	int posY = 9 + y * 2;
	if (stat == ShipF & fstat != Hit)
	{
		setCursor(posX, posY);
		sShip << "    ";
		setCursor(posX, posY+1);
		sShip << "    ";
	}
	else if (fstat == Pass)
	{
		setCursor(posX, posY);
		tempPen << "    ";
		setCursor(posX, posY + 1);
		tempPen << "    ";
	}
	else if (fstat == Hit)
	{
		setCursor(posX, posY);
		hit << "    ";
		setCursor(posX, posY + 1);
		hit << "    ";
	}
	else
	{
		drawRectangle(posX, posY);
	}
}

bool FieldView::isSelected(int x, int y) 
{
	return x == selectedX && y == selectedY;
}

FightStatus FieldView::getYourFieldStatus(int x, int y) const
{
	return playerField[x][y];
}

FinalStatus FieldView::getEnemyFieldStatus(int x, int y) const
{
	return computerPort[x][y];
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
		cout << "Enter your name: ";
		string name = getName();
		showCursor(false);
		bool exit = false;
		if (name.size() >= 12)
		{
			printInCenter(consoleHeight - 3, "Continue", mainPan);
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



bool FieldView::isThereEnemyShip(int x, int y)
{
	bool toReturn = false;
	if (getEnemyFieldStatus(x, y) == Ship)
	{
		toReturn = true;
	}
	return toReturn;
}

void FieldView::killedYourShips()
{
	for (int i = 0; i < 10; ++i)
	{
		wasShipKilled(navy[i], playerField);
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

bool FieldView::canplaceBotShip(int isHoriz, int x, int y)
{
	bool toReturn = true;
	if (isHoriz == 1)
	{
		if (x < 10 - botNavy[counter].getSize() + 1)
		{
			for (int i = x; i < x + botNavy[counter].getSize(); ++i)
			{
				if (computerPort[i][y] == Ship || computerPort[i][y] == Around)
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
		if (y < 10 - botNavy[counter].getSize() + 1)
		{
			for (int i = y; i < y + botNavy[counter].getSize(); ++i)
			{
				if (computerPort[x][i] == Ship || computerPort[x][i] == Around)
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

void FieldView::placeBotShip()
{
	bool isPlaced = false;
	srand(time(NULL));
	while (!isPlaced)
	{
		int isHorizontal = rand() % 2;
		int x = rand() % 10;
		int y = rand() % 10;
		if (canplaceBotShip(isHorizontal, x, y))
		{
			botNavy[counter].setX(x);
			botNavy[counter].setY(y);
			if (isHorizontal == 1) 
			{
				botNavy[counter].setVector(true);
				for (int i = x; i < x + botNavy[counter].getSize(); ++i)
				{
					computerPort[i][y] = Ship;
					if (y > 0 && computerPort[i][y - 1] != Ship)
					{
						computerPort[i][y - 1] = Around;
					}
					if (y < 9 && computerPort[i][y + 1] != Ship)
					{
						computerPort[i][y + 1] = Around;
					}
				}
				if (x > 0)
				{
					if (computerPort[x - 1][y] != Ship)
					{
						computerPort[x - 1][y] = Around;
					}
					if (y > 0 && computerPort[x - 1][y - 1] != Ship)
					{
						computerPort[x - 1][y - 1] = Around;
					}
					if (y < 9 && computerPort[x - 1][y + 1] != Ship)
					{
						computerPort[x - 1][y + 1] = Around;
					}
				}
				if (x + botNavy[counter].getSize() < 10)
				{
					if (computerPort[x + botNavy[counter].getSize()][y] != Ship)
					{
						computerPort[x + botNavy[counter].getSize()][y] = Around;
					}
					if (y > 0 && computerPort[x + botNavy[counter].getSize()][y - 1] != Ship)
					{
						computerPort[x + botNavy[counter].getSize()][y - 1] = Around;
					}
					if (y < 9 && computerPort[x + botNavy[counter].getSize()][y + 1] != Ship)
					{
						computerPort[x + botNavy[counter].getSize()][y + 1] = Around;
					}
				}
			}
			else
			{
				botNavy[counter].setVector(false);
				for (int i = y; i < y + botNavy[counter].getSize(); ++i)
				{
					computerPort[x][i] = Ship;
					if (x > 0 && computerPort[x - 1][i] != Ship)
					{
						computerPort[x - 1][i] = Around;
					}
					if (x < 9 && computerPort[x + 1][i] != Ship)
					{
						computerPort[x + 1][i] = Around;
					}
				}
				if (y > 0)
				{
					if (computerPort[x][y - 1] != Ship)
					{
						computerPort[x][y - 1] = Around;
					}
					if (x > 0 && computerPort[x - 1][y - 1] != Ship)
					{
						computerPort[x - 1][y - 1] = Around;
					}
					if (x < 9 && computerPort[x + 1][y - 1] != Ship)
					{
						computerPort[x + 1][y - 1] = Around;
					}
				}
				if (y + botNavy[counter].getSize() < 10)
				{
					if (computerPort[x][y + botNavy[counter].getSize()] != Ship)
					{
						computerPort[x][y + botNavy[counter].getSize()] = Around;
					}
					if (x > 0 && computerPort[x - 1][y + botNavy[counter].getSize()] != Ship)
					{
						computerPort[x - 1][y + botNavy[counter].getSize()] = Around;
					}
					if (x < 9 && computerPort[x + 1][y + botNavy[counter].getSize()] != Ship)
					{
						computerPort[x + 1][y + botNavy[counter].getSize()] = Around;
					}
				}
			}
			isPlaced = true;
		}
	}
}

void FieldView::placeBotShips()
{
	for (counter = 0; counter < 10; ++counter)
	{
		placeBotShip();
	}
}



void FieldView::killedEnemyShips()
{
	for (int i = 0; i < 10; ++i)
	{
		wasShipKilled(botNavy[i], computerField);
	}
}

void FieldView::wasShipKilled(WarShip navy, FightStatus fstat[10][10])
{
		bool isShipKilled = true;
		if (navy.isHorizontal)
		{
			for (int j = navy.XPos; j < navy.XPos + navy.Size; ++j)
			{
				if (fstat[j][navy.YPos] != Hit)
				{
					isShipKilled = false;
					break;
				}
			}
		}
		else
		{
			for (int j = navy.YPos; j < navy.YPos + navy.Size; ++j)
			{
				if (fstat[navy.XPos][j] != Hit)
				{
					isShipKilled = false;
					break;
				}
			}
		}
		if (isShipKilled && navy.isHorizontal)
		{
			navy.setReady(true);
			for (int i = navy.XPos; i < navy.XPos + navy.Size; ++i)
			{
				if (navy.YPos > 0 && fstat[i][navy.YPos - 1] != ShipF)
				{
					fstat[i][navy.YPos - 1] = Pass;
				}
				if (navy.YPos < 9 && fstat[i][navy.YPos + 1] != ShipF)
				{
					fstat[i][navy.YPos + 1] = Pass;
				}
			}
			if (navy.XPos > 0)
			{
				if (fstat[navy.XPos - 1][navy.YPos] != ShipF)
				{
					fstat[navy.XPos - 1][navy.YPos] = Pass;
				}
				if (navy.YPos > 0 && fstat[navy.XPos - 1][navy.YPos - 1] != ShipF)
				{
					fstat[navy.XPos - 1][navy.YPos - 1] = Pass;
				}
				if (navy.YPos < 9 && fstat[navy.XPos - 1][navy.YPos + 1] != ShipF)
				{
					fstat[navy.XPos - 1][navy.YPos + 1] = Pass;
				}
			}
			if (navy.XPos + navy.Size < 10)
			{
				if (fstat[navy.XPos + navy.Size][navy.YPos] != ShipF)
				{
					fstat[navy.XPos + navy.Size][navy.YPos] = Pass;
				}
				if (navy.YPos > 0 && fstat[navy.XPos + navy.Size][navy.YPos - 1] != ShipF)
				{
					fstat[navy.XPos + navy.Size][navy.YPos - 1] = Pass;
				}
				if (navy.YPos < 9 && fstat[navy.XPos + navy.Size][navy.YPos + 1] != ShipF)
				{
					fstat[navy.XPos + navy.Size][navy.YPos + 1] = Pass;
				}
			}
		}
		else if (isShipKilled && !navy.isHorizontal)
		{
			navy.setReady(true);
			for (int i = navy.YPos; i < navy.YPos + navy.Size; ++i)
			{
				if (navy.XPos > 0 && fstat[navy.XPos - 1][i] != ShipF)
				{
					fstat[navy.XPos - 1][i] = Pass;
				}
				if (navy.XPos < 9 && fstat[navy.XPos + 1][i] != ShipF)
				{
					fstat[navy.XPos + 1][i] = Pass;
				}
			}
			if (navy.YPos > 0)
			{
				if (fstat[navy.XPos][navy.YPos - 1] != ShipF)
				{
					fstat[navy.XPos][navy.YPos - 1] = Pass;
				}
				if (navy.XPos > 0 && fstat[navy.XPos - 1][navy.YPos - 1] != ShipF)
				{
					fstat[navy.XPos - 1][navy.YPos - 1] = Pass;
				}
				if (navy.XPos < 9 && fstat[navy.XPos + 1][navy.YPos - 1] != ShipF)
				{
					fstat[navy.XPos + 1][navy.YPos - 1] = Pass;
				}
			}
			if (navy.YPos + navy.Size < 10)
			{
				if (fstat[navy.XPos][navy.YPos + navy.Size] != ShipF)
				{
					fstat[navy.XPos][navy.YPos + navy.Size] = Pass;
				}
				if (navy.XPos > 0 && fstat[navy.XPos - 1][navy.YPos + navy.Size] != ShipF)
				{
					fstat[navy.XPos - 1][navy.YPos + navy.Size] = Pass;
				}
				if (navy.XPos < 9 && fstat[navy.XPos + 1][navy.YPos + navy.Size] != ShipF)
				{
					fstat[navy.XPos + 1][navy.YPos + navy.Size] = Pass;
				}
			}
		}
}

void FieldView::congratulations()
{
	printInCenter(consoleHeight - 7, "Victory! Your scored: " + to_string(score), mainPan);
	printInCenter(consoleHeight - 5, "Press Enter to continue", mainPan);
}

void FieldView::loseSign()
{
	printInCenter(consoleHeight - 4, "Defeat! Your score: " + to_string(score), mainPan);
	printInCenter(consoleHeight - 2, "Press Enter to continue", mainPan);
}

string FieldView::getName()
{
	string name;
	char symbol = 0;
	short counter = 0;
	while (counter < 12 && symbol != 13)
	{
		symbol = _getch();
		if (symbol == 8 && counter > 0)
		{
			name.pop_back();
			
			setCursor(consoleWidth / 3 + 16 + counter, consoleHeight - 4);
			cout << " ";
			setCursor(consoleWidth / 3 + 16 + counter, consoleHeight - 4);
		
			if (counter != 0)
			{
				--counter;
			}
		}
		if (symbol == Enter && name.size() == 0)
		{
			name = "Unknown";
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

