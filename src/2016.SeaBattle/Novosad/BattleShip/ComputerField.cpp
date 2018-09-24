#include "ComputerField.h"
#include <ctime>
#include "Ship.h"

ComputerField::ComputerField(
	int locationX,
	int locationY,
	int cell_width,
	int cell_height) :
	Field(locationX, locationY, cell_width, cell_height)
{
	setRandomEnemyShips();
	toggleShipFrame();
}

void ComputerField::submitFire(FireDetails details)
{
	last_details_ = details;
}

void ComputerField::setRandomEnemyShips()
{
	srand(time(NULL));
	int shipSizes[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

	for (int i = 0; i < 10; i++)
	{
		// if 0 - horizontal, 1 - vertical
		int orientation = rand() % 2;
		Ship ship(shipSizes[i], static_cast<ShipOrientation>(orientation));

		while (true)
		{
			// if 0 - horizontal, 1 - vertical
			orientation = rand() % 2;
			int x = rand() % 10;
			int y = rand() % 10;

			ship.setLocationX(x);
			ship.setLocationY(y);
			ship.setOrientation(static_cast<ShipOrientation>(orientation));

			if (canPlace(ship))
			{
				if (ship.getOrientation() == ShipOrientation::Vertical && y + ship.getSize() - 1 > 9 ||
					ship.getOrientation() == ShipOrientation::Horizontal && x + ship.getSize() - 1 > 9)
				{
					continue;
				}

				place(ship);
				break;
			}
		}
	}
}

FireDetails ComputerField::waitForFire()
{
	// set seed for random and wait 100ms
	srand(time(NULL));
	Sleep(100);

	int x = 0;
	int y = 0;

	if (last_details_.X < 0 ||
		last_details_.Y < 0 ||
		last_details_.Result != FireResult::Hit)
	{
		// generate random coordinates
		x = rand() % 10;
		y = rand() % 10;
	}

	if (last_details_.X >= 0 ||
		last_details_.Y >= 0 ||
		last_details_.Result == FireResult::Hit)
	{
		//0 - left, 1 - right, 2 - up, 3 - down
		while (true)
		{
			int side = rand() % 4;
			switch (side)
			{
			case 0:
				x = last_details_.X - 1;
				y = last_details_.Y;
				break;
			case 1:
				x = last_details_.X + 1;
				y = last_details_.Y;
				break;
			case 2:
				x = last_details_.X;
				y = last_details_.Y - 1;
				break;
			case 3:
				x = last_details_.X;
				y = last_details_.Y + 1;
				break;
			}

			if (x >= 0 && x <= 9 && y >= 0 && y <= 9)
			{
				break;
			}
		}
	}

	// create fire action message request
	FireDetails details;
	details.X = x;
	details.Y = y;
	details.Result = FireResult::Miss;
	details.ShipSize = -1;

	return details;
}

bool ComputerField::needsToFinishShip(int& indexOfShip, vector<Ship> myShips)
{
	bool result = false;
	for (int i = 0; i < myShips.size(); i++)
	{
		for (int j = 0; j < myShips[i].getSize(); j++)
		{
			if (myShips[i].getCellState(j) == CellState::Hit && myShips[i].isNotKilled())
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

FireDetails ComputerField::waitForComputer(Field* field)
{
	vector<Ship> enemiesShips = field->getShips();
	srand(time(NULL));
	Sleep(100);
	int x = 0;
	int y = 0;
	int indexOfShip = 0;
	int indexOfFirst = 0;
	int indexOfLast = 0;
	while (true)
	{
		if (needsToFinishShip(indexOfShip, enemiesShips))
		{
			enemiesShips[indexOfShip].getIndexOfFirstAndLastKilledCell(indexOfFirst, indexOfLast);
			if (indexOfFirst == indexOfLast)
			{
				int number = rand() % 4; // 0 - left, 1- right, 2 - up, 3- down
				if (enemiesShips[indexOfShip].getOrientation() == ShipOrientation::Horizontal)
				{
					switch (number)
					{
					case 0:
						x = enemiesShips[indexOfShip].getLocationX() + indexOfFirst - 1;
						y = enemiesShips[indexOfShip].getLocationY();
						break;
					case 1:
						x = enemiesShips[indexOfShip].getLocationX() + indexOfFirst + 1;
						y = enemiesShips[indexOfShip].getLocationY();
						break;
					case 2:
						x = enemiesShips[indexOfShip].getLocationX() + indexOfFirst;
						y = enemiesShips[indexOfShip].getLocationY() - 1;
						break;
					case 3:
						x = enemiesShips[indexOfShip].getLocationX() + indexOfFirst;
						y = enemiesShips[indexOfShip].getLocationY() + 1;
						break;
					}
				}
				else
				{
					switch (number)
					{
					case 0:
						x = enemiesShips[indexOfShip].getLocationX() - 1;
						y = enemiesShips[indexOfShip].getLocationY() + indexOfFirst;
						break;
					case 1:
						x = enemiesShips[indexOfShip].getLocationX() + 1;
						y = enemiesShips[indexOfShip].getLocationY() + indexOfFirst;
						break;
					case 2:
						x = enemiesShips[indexOfShip].getLocationX();
						y = enemiesShips[indexOfShip].getLocationY() - 1 + indexOfFirst;
						break;
					case 3:
						x = enemiesShips[indexOfShip].getLocationX();
						y = enemiesShips[indexOfShip].getLocationY() + 1 + indexOfFirst;
						break;
					}
				}
			}
			else
			{
				int number = rand() % 2; // 0 - left, 1- right; 0 - up, 1- down
				if (enemiesShips[indexOfShip].getOrientation() == ShipOrientation::Horizontal)
				{
					switch (number)
					{
					case 0:
						x = enemiesShips[indexOfShip].getLocationX() + indexOfFirst - 1;
						y = enemiesShips[indexOfShip].getLocationY();
						break;
					case 1:
						x = enemiesShips[indexOfShip].getLocationX() + indexOfLast + 1;
						y = enemiesShips[indexOfShip].getLocationY();
						break;
					}
				}
				else
				{
					switch (number)
					{
					case 0:
						x = enemiesShips[indexOfShip].getLocationX();
						y = enemiesShips[indexOfShip].getLocationY() + indexOfFirst - 1;
						break;
					case 1:
						x = enemiesShips[indexOfShip].getLocationX();
						y = enemiesShips[indexOfShip].getLocationY() + indexOfLast + 1;
						break;
					}
				}
			}
		}
		else
		{
			x = rand() % 10;
			y = rand() % 10;
		}
		if (x >= 0 && x <= 9 && y >= 0 && y <= 9 &&
			field->getCellState(x, y) == CellState::Empty)
		{
			break;
		}
	}

	// create fire action message request
	FireDetails _details;
	_details.X = x;
	_details.Y = y;
	_details.Result = FireResult::Miss;
	_details.ShipSize = -1;

	return _details;
}
