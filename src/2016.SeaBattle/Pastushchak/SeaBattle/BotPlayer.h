#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <conio.h>
#include <Windows.h>
#include "Color.h"
#include "LocateYourShips.h"
#include "Tile.h"
#include "Ship.h"
#include "SetConsoleSize.h"
#include <vector>
#include "InternetConnection.h"
#include "Game.h"
using namespace std;

class BotPlayer : public Game
{
public:
	void drawSecondPlayerShoot()
	{
		drawTilesSecondPlayerKnow();
		drawCheckIfSecondPlayerKill();
		if (!secondPlayerWin)
		{
			bool canBeShootedHere = false;
			int xCoordinate;
			int yCoordinate;

			while (!canBeShootedHere)
			{
				srand(time(NULL));
				canBeShootedHere = true;
				xCoordinate = rand() % 10;
				yCoordinate = rand() % 10;

				for (size_t i = 0; i < goodTilesSecondPlayerKnow.size(); ++i)
				{
					vector<Tile> v = goodTilesSecondPlayerKnow[i].adjancedTiles();
					for (size_t j = 0; j < v.size(); ++j)
					{
						bool isGood = false;
						bool isBad = false;
						for (size_t k = 0; k < goodTilesSecondPlayerKnow.size(); ++k)
						{
							if (v[j] == goodTilesSecondPlayerKnow[k])
							{
								isGood = true;
								break;
							}
						}
						for (size_t k = 0; k < badTilesSecondPlayerKnow.size(); ++k)
						{
							if (v[j] == badTilesSecondPlayerKnow[k])
							{
								isBad = true;
								break;
							}
						}

						if (!isGood && !isBad)
						{
							xCoordinate = goodTilesSecondPlayerKnow[i].adjancedTiles()[j].firstCoordinate;
							yCoordinate = goodTilesSecondPlayerKnow[i].adjancedTiles()[j].secondCoordinate;
							break;
						}
					}
				}

				Tile t(xCoordinate, yCoordinate);

				for (size_t i = 0; i < goodTilesSecondPlayerKnow.size(); ++i)
				{
					if (t == goodTilesSecondPlayerKnow[i])
					{
						canBeShootedHere = false;
						break;
					}
				}
				for (size_t i = 0; i < badTilesSecondPlayerKnow.size(); ++i)
				{
					if (t == badTilesSecondPlayerKnow[i])
					{
						canBeShootedHere = false;
						break;
					}
				}

				if (canBeShootedHere)
				{
					bool land = false;
					for (size_t i = 0; i < firstPlayerShips.size(); ++i)
					{
						for (size_t j = 0; j < firstPlayerShips[i].numberOfDecks; ++j)
						{
							if (t == firstPlayerShips[i].tiles[j])
							{
								goodTilesSecondPlayerKnow.push_back(t);
								t.drawInColor(t.firstCoordinate * TileSize + 100, t.secondCoordinate * TileSize + 100, "green");
								canBeShootedHere = false;
								drawCheckIfSecondPlayerKill();
								land = true;
								break;
							}
						}
					}

					if (!land)
					{
						badTilesSecondPlayerKnow.push_back(t);
					}
				}
			}

			drawCheckIfSecondPlayerKill();
		}
	}

	void drawFirstPlayerShoot()
	{
		drawCheckIfSecondPlayerKill();
		drawCheckIfFirstPlayerKill();
		if (!firstPlayerWin)
		{
			int xCoord = previousShoot.firstCoordinate;
			int yCoord = previousShoot.secondCoordinate;

			drawOnlySidesOfSquare(700, 100, TileSize * xCoord, TileSize * yCoord);

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
					case 72: yCoord--; break;
					case 77: xCoord++; break;
					case 80: yCoord++; break;
					case 75: xCoord--; break;
					}

					if (xCoord < 0) xCoord += 10;
					if (xCoord > 9) xCoord -= 10;
					if (yCoord < 0) yCoord += 10;
					if (yCoord > 9) yCoord -= 10;

					drawFields();
					drawOnlySidesOfSquare(700, 100, xCoord * TileSize, yCoord * TileSize);
				}

				Tile t(xCoord, yCoord);
				for (size_t i = 0; i < goodTilesFirstPlayerKnow.size(); ++i)
				{
					if (t == goodTilesFirstPlayerKnow[i])
					{
						pressedEnter = false;
						break;
					}
				}

				for (size_t i = 0; i < badTilesFirstPlayerKnow.size(); ++i)
				{
					if (t == badTilesFirstPlayerKnow[i])
					{
						pressedEnter = false;
						break;
					}
				}
			}

			Tile goodOrBadTile(xCoord, yCoord);
			previousShoot = goodOrBadTile;
			bool isEnemyShip = false;
			for (size_t i = 0; i < secondPlayersField.size(); ++i)
			{
				if (goodOrBadTile == secondPlayersField[i])
				{
					isEnemyShip = true;
					break;
				}
			}

			system("cls");
			if (isEnemyShip)
			{
				goodTilesFirstPlayerKnow.push_back(goodOrBadTile);
				drawSquare(700 + xCoord * TileSize, 100 + yCoord * TileSize, "green");
				drawFirstPlayerShoot();
			}

			else
			{
				bool thereWasSuchTile = false;
				for (size_t j = 0; j < badTilesFirstPlayerKnow.size(); ++j)
				{
					if (goodOrBadTile == badTilesFirstPlayerKnow[j])
					{
						thereWasSuchTile = true;
						break;
					}
				}

				if (!thereWasSuchTile)
				{
					badTilesFirstPlayerKnow.push_back(goodOrBadTile);
				}

				drawSquare(700 + xCoord * TileSize, 100 + yCoord * TileSize, "blue");
			}

			++counterTurns;
		}
	}
};