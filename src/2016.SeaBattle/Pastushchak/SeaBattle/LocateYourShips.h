#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "Color.h"
#include "Ship.h"
#include "Tile.h"
#include "SetConsoleSize.h"
#include <ctime>
#include <vector>
using namespace std;

class LocateYourShips
{
private:
	Ship yourShips[10];
	Ship rightShips[10];
	bool isAlreadyChoosen[10];
public:
	LocateYourShips()
	{
		Ship s2(2);
		Ship s3(3);
		Ship s4(4);

		for (size_t i = 0; i < 10; ++i)
		{
			yourShips[i] = defaultShips()[i];
		}

		rightShips[4] = s2;
		rightShips[5] = s2;
		rightShips[6] = s2;
		rightShips[7] = s3;
		rightShips[8] = s3;
		rightShips[9] = s4;

		for (size_t i = 0; i < 10; ++i)
		{
			isAlreadyChoosen[i] = false;
		}
	}

	void writeShipsInFile(ofstream& write)
	{
		for (size_t i = 0; i < 10; ++i)
		{
			write << yourShips[i];
		}
	}

	vector<Ship> getShips()
	{
		vector<Ship> vec;
		for (size_t i = 0; i < 10; ++i)
		{
			vec.push_back(yourShips[i]);
		}

		return vec;
	}

	vector<Ship> defaultShips()
	{
		vector<Ship> vec;
		srand(time(NULL));
		Tile arr[10][10];
		bool isBad[10][10];

		for (size_t i = 0; i < 10; ++i)
		{
			for (size_t j = 0; j < 10; ++j)
			{
				arr[i][j].firstCoordinate = i;
				arr[i][j].secondCoordinate = j;
				isBad[i][j] = false;
			}
		}
		Ship s[10];

		s[0] = Ship(1);
		s[1] = Ship(1);
		s[2] = Ship(1);
		s[3] = Ship(1);
		s[4] = Ship(2);
		s[5] = Ship(2);
		s[6] = Ship(2);
		s[7] = Ship(3);
		s[8] = Ship(3);
		s[9] = Ship(4);

		int x, y;
		bool horizont;
		for (size_t i = 0; i < 10; ++i)
		{
			bool canBePlacedHere = false;

			while (!canBePlacedHere)
			{
				canBePlacedHere = true;
				x = rand() % 10;
				y = rand() % 10;
				horizont = rand() % 2;
				s[i] = Ship(s[i].numberOfDecks, horizont, x, y);

				if (horizont)
				{
					if (x > 10 - s[i].numberOfDecks)
					{
						canBePlacedHere = false;
					}
				}
				else
				{
					if (y > 10 - s[i].numberOfDecks)
					{
						canBePlacedHere = false;
					}
				}

				for (size_t j = 0; j < s[i].numberOfDecks; ++j)
				{
					if (isBad[s[i].tiles[j].firstCoordinate][s[i].tiles[j].secondCoordinate])
					{
						canBePlacedHere = false;
						break;
					}
				}
			}

			vec.push_back(s[i]);

			for (size_t j = 0; j < 10; ++j)
			{
				for (size_t k = 0; k < 10; ++k)
				{
					for (size_t shipsI = 0; shipsI < s[i].numberOfDecks; ++shipsI)
					{
						int xDif = s[i].tiles[shipsI].firstCoordinate - j;
						int yDif = s[i].tiles[shipsI].secondCoordinate - k;

						if (abs(xDif) <= 1 && abs(yDif) <= 1)
						{
							isBad[j][k] = true;
						}
					}
				}
			}
		}

		return vec;
	}

	void draw()
	{
		SelectObject(hDC, hPenBLUE);
		for (size_t i = 0; i < 11; ++i)
		{
			MoveToEx(hDC, 100 + TileSize * i, 100, &op);
			LineTo(hDC, 100 + TileSize * i, 600);

			MoveToEx(hDC, 100, 100 + TileSize * i, &op);
			LineTo(hDC, 600, 100 + TileSize * i);
		}

		for (size_t i = 0; i < 10; ++i)
		{
			if (isAlreadyChoosen[i])
			{
				yourShips[i].drawShipInColor(yourShips[i].tiles[0].firstCoordinate * TileSize + 100, yourShips[i].tiles[0].secondCoordinate * TileSize + 100);
			}
		}

		drawStartShips();
	}

	void drawThisIndexWithColor(size_t index, string color = "green")
	{
		switch (index)
		{
		case 0: rightShips[0].drawShip(700, 100, color); break;
		case 1: rightShips[1].drawShip(800, 100, color); break;
		case 2: rightShips[2].drawShip(900, 100, color); break;
		case 3:	rightShips[3].drawShip(1000, 100, color); break;
		case 4:	rightShips[4].drawShip(700, 200, color); break;
		case 5:	rightShips[5].drawShip(850, 200, color); break;
		case 6: rightShips[6].drawShip(1000, 200, color); break;
		case 7:	rightShips[7].drawShip(700, 300, color); break;
		case 8:	rightShips[8].drawShip(900, 300, color); break;
		case 9:	rightShips[9].drawShip(700, 400, color); break;
		}
	}

	void drawStartShips(string color = "green")
	{
		string c[10];
		for (size_t i = 0; i < 10; ++i)
		{
			c[i] = color;
		}

		for (size_t i = 0; i < 10; ++i)
		{
			if (isAlreadyChoosen[i])
			{
				c[i] = "yellow";
			}
		}

		rightShips[0].drawShip(700, 100, c[0]);
		rightShips[1].drawShip(800, 100, c[1]);
		rightShips[2].drawShip(900, 100, c[2]);
		rightShips[3].drawShip(1000, 100, c[3]);
		rightShips[4].drawShip(700, 200, c[4]);
		rightShips[5].drawShip(850, 200, c[5]);
		rightShips[6].drawShip(1000, 200, c[6]);
		rightShips[7].drawShip(700, 300, c[7]);
		rightShips[8].drawShip(900, 300, c[8]);
		rightShips[9].drawShip(700, 400, c[9]);
	}

	void drawSettingShips()
	{
		Ship s1(1);
		Ship s2(2);
		Ship s3(3);
		Ship s4(4);

		yourShips[0] = s1;
		yourShips[1] = s1;
		yourShips[2] = s1;
		yourShips[3] = s1;
		yourShips[4] = s2;
		yourShips[5] = s2;
		yourShips[6] = s2;
		yourShips[7] = s3;
		yourShips[8] = s3;
		yourShips[9] = s4;

		bool allIsChosed = false;
		while (!allIsChosed)
		{
			allIsChosed = true;

			drawChoosingShip();
			for (size_t i = 0; i < 10; ++i)
			{
				if (!isAlreadyChoosen[i])
				{
					allIsChosed = false;
					break;
				}
			}
		}
	}

	void drawChoosingShip()
	{
		int choosedShip;
		for (size_t i = 0; i < 10; ++i)
		{
			if (!isAlreadyChoosen[i])
			{
				choosedShip = i;
				break;
			}
		}

		for (size_t i = 0; i < 10; ++i)
		{
			if (isAlreadyChoosen[i])
			{
				drawThisIndexWithColor(i, "yellow");
			}
		}

		drawThisIndexWithColor(choosedShip, "red");

		bool thisShipWasSetted = true;
		int counter = 0;

		while (thisShipWasSetted)
		{
			thisShipWasSetted = false;
			bool pressedEnter = false;
			while (!pressedEnter)
			{
				char c = _getch();
				if (c == 13)
				{
					pressedEnter = true;
				}
				else
				{
					switch (_getch())
					{
					case 80: ++choosedShip; break;
					case 72: --choosedShip; break;
					case 75: --choosedShip; break;
					case 77: ++choosedShip; break;
					case 13: pressedEnter = true; break;
					default: break;
					}

					if (choosedShip < 0) choosedShip += 10;
					if (choosedShip > 9) choosedShip -= 10;
				}

				draw();
				for (size_t i = 0; i < 10; ++i)
				{
					if (isAlreadyChoosen[i])
					{
						drawThisIndexWithColor(i, "yellow");
					}
				}

				drawThisIndexWithColor(choosedShip, "red");

				if (isAlreadyChoosen[choosedShip])
				{
					thisShipWasSetted = true;
				}

				++counter;
			}
		}

		yourShips[choosedShip] = setInThisPlase(yourShips[choosedShip]);

		isAlreadyChoosen[choosedShip] = true;
	}

	Ship setInThisPlase(Ship s)
	{
		s.drawShip(s.tiles[0].firstCoordinate * TileSize + 100, s.tiles[0].secondCoordinate * TileSize + 100);

		bool pressedEnter = false;
		while (!pressedEnter)
		{
			char c = _getch();
			if (c == 13)
			{
				pressedEnter = true;
			}
			else
			{
				if (c == 32)
				{
					s.isHorizontal = !s.isHorizontal;
				}
				else
				{
					switch (_getch())
					{
					case 80: s.tiles[0].secondCoordinate++; break;
					case 72: s.tiles[0].secondCoordinate--; break;
					case 75: s.tiles[0].firstCoordinate--; break;
					case 77: s.tiles[0].firstCoordinate++; break;
					case 13: pressedEnter = true; break;
					}
				}

				if (s.isHorizontal)
				{
					if (s.tiles[0].firstCoordinate > 10 - s.numberOfDecks) s.tiles[0].firstCoordinate = 0;
					if (s.tiles[0].firstCoordinate < 0) s.tiles[0].firstCoordinate = 10 - s.numberOfDecks;
					if (s.tiles[0].secondCoordinate > 9) s.tiles[0].secondCoordinate = 0;
					if (s.tiles[0].secondCoordinate < 0) s.tiles[0].secondCoordinate = 9;
				}
				else
				{
					if (s.tiles[0].secondCoordinate > 10 - s.numberOfDecks) s.tiles[0].secondCoordinate = 0;
					if (s.tiles[0].secondCoordinate < 0) s.tiles[0].secondCoordinate = 10 - s.numberOfDecks;
					if (s.tiles[0].firstCoordinate > 9) s.tiles[0].firstCoordinate = 0;
					if (s.tiles[0].firstCoordinate < 0) s.tiles[0].firstCoordinate = 9;
				}

				draw();
			}
			s.drawShip(s.tiles[0].firstCoordinate * TileSize + 100, s.tiles[0].secondCoordinate* TileSize + 100);

			if (pressedEnter)
			{
				if (s.isHorizontal)
				{
					for (size_t i = 0; i < s.numberOfDecks; ++i)
					{
						s.tiles[i].firstCoordinate = s.tiles[0].firstCoordinate + i;
						s.tiles[i].secondCoordinate = s.tiles[0].secondCoordinate;
					}
				}
				else
				{
					for (size_t i = 0; i < s.numberOfDecks; ++i)
					{
						s.tiles[i].firstCoordinate = s.tiles[0].firstCoordinate;
						s.tiles[i].secondCoordinate = s.tiles[0].secondCoordinate + i;
					}
				}

				for (size_t j = 0; j < 10; ++j)
				{
					if (isAlreadyChoosen[j])
					{
						for (size_t i = 0; i < s.numberOfDecks; ++i)
						{
							for (size_t k = 0; k < 3 * yourShips[j].numberOfDecks + 7; ++k)
							{
								if (s.tiles[i] == yourShips[j].adjancedTiles()[k])
								{
									pressedEnter = false;
								}
							}
						}
					}
				}
			}
		}

		s.drawShipInColor(s.tiles[0].firstCoordinate * TileSize + 100, s.tiles[0].secondCoordinate * TileSize + 100);
		return s;
	}
};

LocateYourShips field;