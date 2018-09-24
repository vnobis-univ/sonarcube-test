#include "GameView.h"
#include "ResultView.h"
#include "GlobalVars.h"
#include "StartView.h"
#include "ConsoleUtils.h"
#include <conio.h>
#include <time.h>

void GameView::drawMyShip(Ship myShip)
{
	HPEN yellowPen = CreatePen(PS_SOLID, 2, RGB(210, 255, 250));
	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HGDIOBJ currentPen = SelectObject(hdc, yellowPen);
	MoveToEx(hdc, (myShip.getCoordinateYOfTopOfShip() + 3) * 20 - 30, (myShip.getCoordinateXOfTopOfShip() + 10) * 16, NULL);
	if (myShip.getPosition() == PositionOfShip::Horizontal)
	{
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 3) * 20 - 30 + myShip.getSize() * 20, (myShip.getCoordinateXOfTopOfShip() + 10) * 16);
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 3) * 20 - 30 + myShip.getSize() * 20, (myShip.getCoordinateXOfTopOfShip() + 11) * 16);
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 3) * 20 - 30, (myShip.getCoordinateXOfTopOfShip() + 11) * 16);
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 3) * 20 - 30, (myShip.getCoordinateXOfTopOfShip() + 10) * 16);
	}
	else
	{
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 4) * 20 - 30, (myShip.getCoordinateXOfTopOfShip() + 10) * 16);
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 4) * 20 - 30, (myShip.getCoordinateXOfTopOfShip() + 10 + myShip.getSize()) * 16);
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 3) * 20 - 30, (myShip.getCoordinateXOfTopOfShip() + 10 + myShip.getSize()) * 16);
		LineTo(hdc, (myShip.getCoordinateYOfTopOfShip() + 3) * 20 - 30, (myShip.getCoordinateXOfTopOfShip() + 10) * 16);

	}
	DeleteObject(yellowPen);
	DeleteObject(currentPen);
	ReleaseDC(hwnd, hdc);
}

bool GameView::isPossibleToPutShipHere(int x, int y, int size, PositionOfShip pos, vector<Ship> temp)
{
	Ship ship(x, y, size, static_cast<PositionOfShip>(pos));
	bool isPossible = true;
	if (size == 4)
	{
		if (pos == PositionOfShip::Horizontal)
		{
			if (y + size - 1 > 9)
			{
				return false;
			}
		}
		else
		{
			if (x + size - 1 > 9)
			{
				return false;
			}
		}
	}
	for (size_t k = 0; k < ship.getSize(); k++)
	{
		for (size_t i = 0; i < temp.size(); i++)
		{
			for (size_t j = 0; j < temp[i].getSize(); j++)
			{
				if (temp[i].getPosition() == PositionOfShip::Horizontal)
				{
					if (ship.getPosition() == PositionOfShip::Horizontal)
					{
						if ((y + ship.getSize() - 1 > 9) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j && x == temp[i].getCoordinateXOfTopOfShip()) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j + 1 && x == temp[i].getCoordinateXOfTopOfShip()) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j - 1 && x == temp[i].getCoordinateXOfTopOfShip()) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j && x == temp[i].getCoordinateXOfTopOfShip() + 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j && x == temp[i].getCoordinateXOfTopOfShip() - 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j + 1 && x == temp[i].getCoordinateXOfTopOfShip() + 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j - 1 && x == temp[i].getCoordinateXOfTopOfShip() - 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j + 1 && x == temp[i].getCoordinateXOfTopOfShip() - 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + j - 1 && x == temp[i].getCoordinateXOfTopOfShip() + 1))
						{
							isPossible = false;
							break;
						}
					}
					else
					{
						if ((x + ship.getSize() - 1 > 9) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j && x + k == temp[i].getCoordinateXOfTopOfShip()) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j + 1 && x + k == temp[i].getCoordinateXOfTopOfShip()) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j - 1 && x + k == temp[i].getCoordinateXOfTopOfShip()) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j && x + k == temp[i].getCoordinateXOfTopOfShip() + 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j && x + k == temp[i].getCoordinateXOfTopOfShip() - 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j + 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j - 1 && x + k == temp[i].getCoordinateXOfTopOfShip() - 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j + 1 && x + k == temp[i].getCoordinateXOfTopOfShip() - 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + j - 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + 1)
							)
						{
							isPossible = false;
							break;
						}
					}
				}
				else
				{
					if (ship.getPosition() == PositionOfShip::Horizontal)
					{
						if ((y + ship.getSize()  > 10) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() && x == temp[i].getCoordinateXOfTopOfShip() + j) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + 1 && x == temp[i].getCoordinateXOfTopOfShip() + j) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() - 1 && x == temp[i].getCoordinateXOfTopOfShip() + j) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() && x == temp[i].getCoordinateXOfTopOfShip() + j + 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() && x == temp[i].getCoordinateXOfTopOfShip() + j - 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + 1 && x == temp[i].getCoordinateXOfTopOfShip() + j + 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() - 1 && x == temp[i].getCoordinateXOfTopOfShip() + j - 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() + 1 && x == temp[i].getCoordinateXOfTopOfShip() + j - 1) ||
							(y + k == temp[i].getCoordinateYOfTopOfShip() - 1 && x == temp[i].getCoordinateXOfTopOfShip() + j + 1))
						{
							isPossible = false;
							break;
						}
					}
					else
					{
						if ((x + ship.getSize()  > 10) ||
							(y == temp[i].getCoordinateYOfTopOfShip() && x + k == temp[i].getCoordinateXOfTopOfShip() + j) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + j) ||
							(y == temp[i].getCoordinateYOfTopOfShip() - 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + j) ||
							(y == temp[i].getCoordinateYOfTopOfShip() && x + k == temp[i].getCoordinateXOfTopOfShip() + j + 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() && x + k == temp[i].getCoordinateXOfTopOfShip() + j - 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + j + 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() - 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + j - 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() + 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + j - 1) ||
							(y == temp[i].getCoordinateYOfTopOfShip() - 1 && x + k == temp[i].getCoordinateXOfTopOfShip() + j + 1)
							)
						{
							isPossible = false;
							break;
						}
					}
				}
			}
		}
	}
	return isPossible;
}
void GameView::setRandomEnemyShips()
{
	srand(time(NULL));
	vector<Ship> temp;
	int size = 4;
	for (int d = 0; d < amountOfShips; d++)
	{
		if (d == 1)
		{
			size = 3;
		}
		if (d == 3)
		{
			size = 2;
		}
		if (d == 6)
		{
			size = 1;
		}
		while (true)
		{
			int x = rand() % amountOfShips;
			int y = rand() % amountOfShips;
			int position = rand() % 2;
			if (isPossibleToPutShipHere(x, y, size, static_cast<PositionOfShip>(position), temp))
			{
				Ship ship(x, y, size, static_cast<PositionOfShip>(position));
				temp.push_back(ship);
				break;
			}
		}
	}
	for (size_t i = 0; i < amountOfShips; i++)
	{
		enemyShips.push_back(temp[i]);
	}

}
bool GameView::isShipHit(int x, int y, vector<Ship> ships, int& indexOfShip, int& indexOfCellOfShip)
{
	bool result = false;
	for (size_t i = 0; i < ships.size(); i++)
	{
		for (size_t j = 0; j < ships[i].getSize(); j++)
		{
			if (ships[i].getPosition() == PositionOfShip::Horizontal)
			{
				if (x == ships[i].getCoordinateXOfTopOfShip() && y == ships[i].getCoordinateYOfTopOfShip() + j && ships[i].getStateOfShipCell(j) == StateOfShipCell::NotKilled)
				{
					indexOfShip = i;
					indexOfCellOfShip = j;
					result = true;
					break;
				}
			}
			else
			{
				if (x == ships[i].getCoordinateXOfTopOfShip() + j && y == ships[i].getCoordinateYOfTopOfShip() && ships[i].getStateOfShipCell(j) == StateOfShipCell::NotKilled)
				{
					indexOfShip = i;
					indexOfCellOfShip = j;
					result = true;
					break;
				}
			}
		}
	}
	return result;
}
int GameView::getSizeOfCurrShip()
{
	if (counter == 0)
	{
		return 4;
	}
	else if (counter == 1 || counter == 2)
	{
		return 3;
	}
	else if (counter >= 3 && counter <= 5)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}

bool GameView::needsToFinishShip(int& indexOfShip)
{
	bool result = false;
	for (size_t i = 0; i < myShips.size(); i++)
	{
		for (size_t j = 0; j < myShips[i].getSize(); j++)
		{
			if (myShips[i].getStateOfShipCell(j) == StateOfShipCell::Killed && myShips[i].isNotKilled())
			{
				indexOfShip = i;
				result = true;
				break;
			}
		}
		if (result)
		{
			break;
		}
	}
	return result;
}

void GameView::changeStatesAroundKilledShip(Ship ship, Field& field)
{
	if (ship.getPosition() == PositionOfShip::Horizontal)
	{
		if (ship.getCoordinateYOfTopOfShip() - 1 >= 0)
		{
			if (ship.getCoordinateXOfTopOfShip() - 1 >= 0)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() - 1, ship.getCoordinateYOfTopOfShip() - 1, StateOfFieldCell::NotEmpty);
			}
			if (ship.getCoordinateXOfTopOfShip() + 1 <= 9)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + 1, ship.getCoordinateYOfTopOfShip() - 1, StateOfFieldCell::NotEmpty);
			}
			field.setStateOfCell(ship.getCoordinateXOfTopOfShip(), ship.getCoordinateYOfTopOfShip() - 1, StateOfFieldCell::NotEmpty);
		}
		if (ship.getCoordinateXOfTopOfShip() - 1 >= 0)
		{
			for (size_t i = 0; i < ship.getSize(); i++)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() - 1, ship.getCoordinateYOfTopOfShip() + i, StateOfFieldCell::NotEmpty);
			}
		}
		if (ship.getCoordinateXOfTopOfShip() + 1 <= 9)
		{
			for (size_t i = 0; i < ship.getSize(); i++)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + 1, ship.getCoordinateYOfTopOfShip() + i, StateOfFieldCell::NotEmpty);
			}
		}
		if (ship.getCoordinateYOfTopOfShip() + ship.getSize() <= 9)
		{
			if (ship.getCoordinateXOfTopOfShip() - 1 >= 0)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() - 1, ship.getCoordinateYOfTopOfShip() + ship.getSize(), StateOfFieldCell::NotEmpty);
			}
			if (ship.getCoordinateXOfTopOfShip() + 1 <= 9)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + 1, ship.getCoordinateYOfTopOfShip() + ship.getSize(), StateOfFieldCell::NotEmpty);
			}
			field.setStateOfCell(ship.getCoordinateXOfTopOfShip(), ship.getCoordinateYOfTopOfShip() + ship.getSize(), StateOfFieldCell::NotEmpty);
		}
	}
	else
	{
		if (ship.getCoordinateXOfTopOfShip() - 1 >= 0)
		{
			if (ship.getCoordinateYOfTopOfShip() - 1 >= 0)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() - 1, ship.getCoordinateYOfTopOfShip() - 1, StateOfFieldCell::NotEmpty);
			}
			if (ship.getCoordinateYOfTopOfShip() + 1 <= 9)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() - 1, ship.getCoordinateYOfTopOfShip() + 1, StateOfFieldCell::NotEmpty);
			}
			field.setStateOfCell(ship.getCoordinateXOfTopOfShip() - 1, ship.getCoordinateYOfTopOfShip(), StateOfFieldCell::NotEmpty);
		}
		if (ship.getCoordinateXOfTopOfShip() + ship.getSize() <= 9)
		{
			if (ship.getCoordinateYOfTopOfShip() - 1 >= 0)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + ship.getSize(), ship.getCoordinateYOfTopOfShip() - 1, StateOfFieldCell::NotEmpty);
			}
			if (ship.getCoordinateYOfTopOfShip() + 1 <= 9)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + ship.getSize(), ship.getCoordinateYOfTopOfShip() + 1, StateOfFieldCell::NotEmpty);
			}
			field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + ship.getSize(), ship.getCoordinateYOfTopOfShip(), StateOfFieldCell::NotEmpty);
		}
		if (ship.getCoordinateYOfTopOfShip() - 1 >= 0)
		{
			for (size_t i = 0; i < ship.getSize(); i++)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + i, ship.getCoordinateYOfTopOfShip() - 1, StateOfFieldCell::NotEmpty);
			}
		}
		if (ship.getCoordinateYOfTopOfShip() + 1 <= 9)
		{
			for (size_t i = 0; i < ship.getSize(); i++)
			{
				field.setStateOfCell(ship.getCoordinateXOfTopOfShip() + i, ship.getCoordinateYOfTopOfShip() + 1, StateOfFieldCell::NotEmpty);
			}
		}
	}

}
void GameView::computerMakesMove()
{
	srand(time(NULL));
	int x;
	int y;
	int indexOfShip = 0;
	int indexOfFirst = 0;
	int indexOfLast = 0;
	while (true)
	{
		if (needsToFinishShip(indexOfShip))
		{
			myShips[indexOfShip].getIndexOfFirstAndLastKilledCell(indexOfFirst, indexOfLast);
			if (indexOfFirst == indexOfLast)
			{
				int number = rand() % 4; 
				if (myShips[indexOfShip].getPosition() == PositionOfShip::Horizontal)
				{
					switch (number)
					{
					case 0: // left
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip();
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() + indexOfFirst - 1;
						break;
					case 1: // right
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip();
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() + indexOfFirst + 1;
						break;
					case 2: // up
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() - 1;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() + indexOfFirst;
						break;
					case 3: // down
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() + 1;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() + indexOfFirst;
						break;
					}
				}
				else
				{
					switch (number)
					{
					case 0:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() + indexOfFirst;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() - 1;
						break;
					case 1:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() + indexOfFirst;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() + 1;
						break;
					case 2:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() - 1 + indexOfFirst;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip();
						break;
					case 3:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() + 1 + indexOfFirst;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip();
						break;
					}
				}
			}
			else
			{
				int number = rand() % 2; 
				if (myShips[indexOfShip].getPosition() == PositionOfShip::Horizontal)
				{
					switch (number)
					{
					case 0:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip();
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() + indexOfFirst - 1;
						break;
					case 1:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip();
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip() + indexOfLast + 1;
						break;
					}
				}
				else
				{
					switch (number)
					{
					case 0:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() + indexOfFirst - 1;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip();
						break;
					case 1:
						x = myShips[indexOfShip].getCoordinateXOfTopOfShip() + indexOfLast + 1;
						y = myShips[indexOfShip].getCoordinateYOfTopOfShip();
						break;
					}
				}
			}
		}
		else
		{
			x = rand() % amountOfShips;
			y = rand() % amountOfShips;
		}
		if (x >= 0 && x <= 9 && y >= 0 && y <= 9 && myField.getStateOfCell(x, y) != StateOfFieldCell::NotEmpty)
		{
			int indexOfCellOfShip = 0;
			if (isShipHit(x, y, myShips, indexOfShip, indexOfCellOfShip))
			{
				myShips[indexOfShip].setStateOfShipCell(indexOfCellOfShip, StateOfShipCell::Killed);
				if (!myShips[indexOfShip].isNotKilled())
				{
					changeStatesAroundKilledShip(myShips[indexOfShip], myField);
				}
			}
			else
			{
				myField.setStateOfCell(x, y, StateOfFieldCell::NotEmpty);
				break;
			}
		}
	}
}

bool GameView::playerWon(vector<Ship> ships)
{
	bool result = true;
	for (size_t i = 0; i < ships.size(); i++)
	{
		for (int j = 0; j < ships[i].getSize(); j++)
		{
			if (ships[i].getStateOfShipCell(j) == StateOfShipCell::NotKilled)
			{
				result = false;
			}
		}
		if (!result)
		{
			break;
		}
	}
	return result;
}

int GameView::getExtraPointsForKillingShip(int indexOfShip)
{
	if (indexOfShip == 0)
	{
		return 30;
	}
	else if (indexOfShip == 1 || indexOfShip == 2)
	{
		return 40;
	}
	else if (indexOfShip >= 3 && indexOfShip <= 5)
	{
		return 50;
	}
	else
	{
		return 70;
	}
}

void GameView::printLogo()
{
	string gameLine;
	if (language == Language::ENGLISH)
	{
		gameLine = "SEA BATTLE";
	}
	else
	{
		gameLine = "Морський бій";
	}
	printAtCenter(0, gameLine, redTextYellowBG);
}


GameView::GameView()
{
}

GameView::GameView(Language _language, int _score) : language(_language), score(_score)
{
	currentShip = Ship();
	setRandomEnemyShips();
}

void GameView::draw()
{
	if (language == Language::ENGLISH)
	{
		printAtCenter(22, "SCORE : " + to_string(score), redTextWhiteBG);
		moveCursorTo(8, 7);
		redTextWhiteBG << "YOUR FIELD";
		moveCursorTo(30, 7);
		redTextWhiteBG << "ENEMY FIELD";
		printAtCenter(25, "PRESS SPACE TO ROTATE SHIP", redTextWhiteBG);
		printAtCenter(27, "PRESS ESCAPE TO RETURN TO MENU", redTextWhiteBG);
	}
	else
	{
		printAtCenter(22, "Рахунок : " + to_string(score), redTextWhiteBG);
		moveCursorTo(8, 7);
		redTextWhiteBG << "Ваше поле";
		moveCursorTo(30, 7);
		redTextWhiteBG << "Поле ворога";
		printAtCenter(25, "Натисність SPACE, щоб повернути кораблик", redTextWhiteBG);
		printAtCenter(27, "Натисність ESCAPE, щоб повернутися в меню", redTextWhiteBG);
	}

	for (size_t i = 0; i < amountOfShips; i++)
	{
		moveCursorTo(3 + i * 2, 9);
		redTextWhiteBG << (char)('A' + i);
	}
	myField.drawEmptyField(3, 10);
	for (size_t i = 0; i < amountOfShips; i++)
	{
		if (i != amountOfShips - 1)
		{
			moveCursorTo(1, 10 + i);
		}
		else
		{
			moveCursorTo(0, 10 + i);
		}
		redTextWhiteBG << to_string(i + 1);
	}
	for (size_t i = 0; i < amountOfShips; i++)
	{
		moveCursorTo(27 + i * 2, 9);
		redTextWhiteBG << (char)('A' + i);
	}
	enemyField.drawEmptyField(27, 10);
	for (size_t i = 0; i < amountOfShips; i++)
	{
		if (i != amountOfShips - 1)
		{
			moveCursorTo(25, 10 + i);
		}
		else
		{
			moveCursorTo(24, 10 + i);
		}
		redTextWhiteBG << to_string(i + 1);
	}
	
	myField.draw(3, 10);
	enemyField.draw(27, 10);
	Printer forShip(Color::LIGHT_BLUE, Color::LIGHT_BLUE);

	if (!areMyShipsSet)
	{
		moveCursorTo(3 + currentX * 2, 10 + currentY);
		if (currentShip.getPosition() == PositionOfShip::Horizontal)
		{
			for (size_t i = 0; i < currentShip.getSize(); i++)
			{
				forShip << "  ";
			}
		}
		else
		{
			for (size_t i = 0; i < currentShip.getSize(); i++)
			{
				forShip << "  ";
				moveCursorTo(3 + currentX * 2, 10 + currentY + i + 1);
			}
		}
	}
	else
	{
		moveCursorTo(27 + currentX * 2, 10 + currentY);
		forShip << "  ";
	}

	for (size_t i = 0; i < myShips.size(); i++)
	{
		myShips[i].draw(3, 10);
	}

	for (size_t i = 0; i < amountOfShips; i++)
	{
		enemyShips[i].draw(27, 10);
	}

	for (size_t i = 0; i < amountOfShips; i++)
	{
		if (shipIsPlaced[i])
		{
			drawMyShip(myShips[i]);
		}
	}
}


View* GameView::handle()
{
	View* newView = this;
	int key = _getch();
	if (!areMyShipsSet)
	{
		switch (key)
		{
		case KEY_RIGHT:
		{
			if (currentShip.getPosition() == PositionOfShip::Horizontal && currentX + currentShip.getSize() - 1 == 9)
			{
				currentX = 0; 
			}
			else if (currentShip.getPosition() == PositionOfShip::Vertical && currentX == 9)
			{
				currentX = 0;
			}
			else
			{
				currentX++;
			}
		}
		break;
		case KEY_LEFT:
		{
			if (currentShip.getPosition() == PositionOfShip::Horizontal && currentX == 0)
			{
				currentX = 9 - currentShip.getSize() + 1;
			}
			else if (currentShip.getPosition() == PositionOfShip::Vertical && currentX == 0)
			{
				currentX = 9;
			}
			else
			{
				currentX--;
			}
		}
		break;
		case KEY_DOWN:
		{
			if (currentShip.getPosition() == PositionOfShip::Horizontal && currentY == 9)
			{
				currentY = 0;
			}
			else if (currentShip.getPosition() == PositionOfShip::Vertical && currentY + currentShip.getSize() - 1 == 9)
			{
				currentY = 0;
			}
			else
			{
				currentY++;
			}
		}
		break;
		case KEY_UP:
		{
			if (currentShip.getPosition() == PositionOfShip::Horizontal && currentY == 0)
			{
				currentY = 9;
			}
			else if (currentShip.getPosition() == PositionOfShip::Vertical && currentY == 0)
			{
				currentY = 9 - currentShip.getSize() + 1;
			}
			else
			{
				currentY--;
			}
		}
		break;
		case KEY_SPACE:
		{
			if (currentShip.getPosition() == PositionOfShip::Horizontal)
			{
				if (currentY + currentShip.getSize() - 1 <= 9)
				{
					currentShip.setPosition(PositionOfShip::Vertical);
				}
			}
			else
			{
				if (currentX + currentShip.getSize() - 1 <= 9)
				{
					currentShip.setPosition(PositionOfShip::Horizontal);
				}
			}
		}
		break;
		case KEY_ENTER:
		{
			if (isPossibleToPutShipHere(currentY, currentX, currentShip.getSize(), currentShip.getPosition(), myShips))
			{
				currentShip.setX(currentY);
				currentShip.setY(currentX);
				shipIsPlaced[counter] = true;
				counter++;
				myShips.push_back(currentShip);
				currentX = 0;
				currentY = 0;
				currentShip = Ship(getSizeOfCurrShip());
				if (counter == 10)
				{
					areMyShipsSet = true;
				}
			}
		}
		break;
		case KEY_ESCAPE:
		{
			newView = new StartView(language);
		}
		break;
		}
	}
	else
	{
		if (playerWon(enemyShips))
		{
			newView = new GameView(language, score);
		}
		else if (playerWon(myShips))
		{
			newView = new ResultView(score, language);
		}
		else
		{
			switch (key)
			{
			case KEY_LEFT:
			{
				if (currentX == 0)
				{
					currentX = 9;
				}
				else
				{
					currentX--;
				}
			}
			break;
			case KEY_RIGHT:
			{
				if (currentX == 9)
				{
					currentX = 0;
				}
				else
				{
					currentX++;
				}
			}
			break;
			case KEY_UP:
			{
				if (currentY == 0)
				{
					currentY = 9;
				}
				else
				{
					currentY--;
				}
			}
			break;
			case KEY_DOWN:
			{
				if (currentY == 9)
				{
					currentY = 0;
				}
				else
				{
					currentY++;
				}
			}
			break;
			case KEY_ENTER:
			{
				if (enemyField.getStateOfCell(currentY, currentX) != StateOfFieldCell::NotEmpty)
				{
					int indexOfShip = 0;
					int indexOfCellOfShip = 0;
					if (isShipHit(currentY, currentX, enemyShips, indexOfShip, indexOfCellOfShip))
					{
						score += 10;
						enemyShips[indexOfShip].setStateOfShipCell(indexOfCellOfShip, StateOfShipCell::Killed);
						if (!enemyShips[indexOfShip].isNotKilled())
						{
							score += getExtraPointsForKillingShip(indexOfShip);
							changeStatesAroundKilledShip(enemyShips[indexOfShip], enemyField);
						}
					}
					else
					{
						enemyField.setStateOfCell(currentY, currentX, StateOfFieldCell::NotEmpty);
						computerMakesMove();
					}
				}
			}
			break;
			case KEY_ESCAPE:
			{
				newView = new StartView(language);
			}
			break;
			}
		}
	}
	return newView;
}