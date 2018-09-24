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

class HumanPlayer : public Game
{
public:
	void drawSecondPlayerShoot()
	{
		cleanScreen();
		cout << "                          SECOND PLAYER'S TURN" << endl;
		drawStartSecondPlayerYellowShips();
		drawFields();

		drawTilesFirstPlayerKnow();
		drawTilesSecondPlayerKnow();

		drawCheckIfSecondPlayerKill();
		drawCheckIfFirstPlayerKill();

		if (!secondPlayerWin)
		{
			int xCoord = secondPreviousShoot.firstCoordinate;
			int yCoord = secondPreviousShoot.secondCoordinate;

			drawOnlySidesOfSquare(100, 100, TileSize * xCoord, TileSize * yCoord);

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
					drawOnlySidesOfSquare(100, 100, xCoord * TileSize, yCoord * TileSize);
				}


				Tile t(xCoord, yCoord);
				if (pressedEnter)
				{
					for (size_t i = 0; i < goodTilesSecondPlayerKnow.size(); ++i)
					{
						if (t == goodTilesSecondPlayerKnow[i])
						{
							pressedEnter = false;
							break;
						}
					}

					for (size_t i = 0; i < badTilesSecondPlayerKnow.size(); ++i)
					{
						if (t == badTilesSecondPlayerKnow[i])
						{
							pressedEnter = false;
							break;
						}
					}
				}
			}

			Tile goodOrBadTile(xCoord, yCoord);
			secondPreviousShoot = goodOrBadTile;
			bool isEnemyShip = false;
			for (size_t i = 0; i < firstPlayersField.size(); ++i)
			{
				if (goodOrBadTile == firstPlayersField[i])
				{
					isEnemyShip = true;
					break;
				}
			}

			system("cls");
			if (isEnemyShip)
			{
				goodTilesSecondPlayerKnow.push_back(goodOrBadTile);
				drawSquare(100 + xCoord * TileSize, 100 + yCoord * TileSize, "green");
				drawSecondPlayerShoot();
			}

			else
			{
				bool thereWasSuchTile = false;
				for (size_t j = 0; j < badTilesSecondPlayerKnow.size(); ++j)
				{
					if (goodOrBadTile == badTilesSecondPlayerKnow[j])
					{
						thereWasSuchTile = true;
						break;
					}
				}

				if (!thereWasSuchTile)
				{
					badTilesSecondPlayerKnow.push_back(goodOrBadTile);
				}

				drawSquare(100 + xCoord * TileSize, 100 + yCoord * TileSize, "blue");
			}
		}
	}

	void drawFirstPlayerShoot()
	{
		cleanScreen();
		cout << "                          FIRST PLAYER'S TURN" << endl;
		drawFields();
		drawStartFirstPlayerYellowShips();

		drawTilesFirstPlayerKnow();
		drawTilesSecondPlayerKnow();

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
				if (pressedEnter)
				{
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
		}
	}
};