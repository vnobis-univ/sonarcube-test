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
using namespace std;

LocateYourShips firstPlayerLocate;
LocateYourShips secondPlayerLocate;

class Game
{
protected:
	InternetConnection connection;
	int gameOption;
	Tile previousShoot;
	Tile secondPreviousShoot;
	vector<Ship> firstPlayerShips;
	vector<Ship> secondPlayerShips;
	vector<Tile> firstPlayersField;
	vector<Tile> secondPlayersField;
	vector<Tile> goodTilesFirstPlayerKnow;
	vector<Tile> badTilesFirstPlayerKnow;
	vector<Tile> goodTilesSecondPlayerKnow;
	vector<Tile> badTilesSecondPlayerKnow;
	bool killed[10];
	bool killedFirstPlayersShips[10];
	bool firstPlayerWin;
	bool secondPlayerWin;
	size_t counterTurns;
public:
	Game()
	{
		ifstream read("gameOption.txt");
		read >> gameOption;
		read.close();

		counterTurns = 0;
		if (gameOption == 1)
		{
			firstPlayerShips = field.getShips();
			secondPlayerShips = field.defaultShips();
		}

		if (gameOption == 3)
		{
			system("cls");
			cleanScreen();
			cout << "                          FIRST PLAYER TURN";
			firstPlayerLocate.draw();
			firstPlayerLocate.drawSettingShips();
			firstPlayerShips = firstPlayerLocate.getShips();
			Sleep(1000);

			system("cls");
			cleanScreen();
			cout << "                          SECOND PLAYER TURN";
			secondPlayerLocate.draw();
			secondPlayerLocate.drawSettingShips();
			secondPlayerShips = secondPlayerLocate.getShips();

			system("cls");
			cleanScreen();
			drawFields();
		}

		if (gameOption == 2)
		{
			firstPlayerShips = field.getShips();
		}

		firstPlayerWin = false;
		secondPlayerWin = false;
		for (size_t i = 0; i < 10; ++i)
		{
			killed[i] = false;
			killedFirstPlayersShips[i] = false;
		}
	}

	void cleanScreen()
	{
		SelectObject(hDC, hPenBLACK);

		hNewBrush = CreateSolidBrush(RGB(0, 0, 0));
		hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
		Rectangle(hDC, 0, 0, 2000, 2000);

		DeleteObject(hOldBrush);
		DeleteObject(hNewBrush);
	}

	void drawSquare(int x, int y, string color = "blue")
	{
		if (color == "green")
		{
			hNewBrush = CreateSolidBrush(0x00ff00);
		}
		else
		{
			if (color == "red")
			{
				hNewBrush = CreateSolidBrush(0x0000ff);
			}
			else
			{
				hNewBrush = CreateSolidBrush(0xff0000);
			}
		}

		hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);
		Rectangle(hDC, x, y, x + TileSize, y + TileSize);
		DeleteObject(hOldBrush);
		DeleteObject(hNewBrush);
	}

	void drawOnlySidesOfSquare(int correctionX, int correctionY, int x, int y, string color = "red")
	{
		x += correctionX;
		y += correctionY;
		SelectObject(hDC, hPenRED);
		MoveToEx(hDC, x, y, &op);
		LineTo(hDC, x, y + TileSize);
		LineTo(hDC, x + TileSize, y + TileSize);
		LineTo(hDC, x + TileSize, y);
		LineTo(hDC, x, y);
	}

	void drawFields()
	{
		SelectObject(hDC, hPenBLUE);
		for (size_t i = 0; i < 11; ++i)
		{
			MoveToEx(hDC, 100 + TileSize * i, 100, &op);
			LineTo(hDC, 100 + TileSize * i, 600);

			MoveToEx(hDC, 100, 100 + TileSize * i, &op);
			LineTo(hDC, 600, 100 + TileSize * i);

			MoveToEx(hDC, 700 + TileSize * i, 100, &op);
			LineTo(hDC, 700 + TileSize * i, 600);

			MoveToEx(hDC, 700, 100 + TileSize * i, &op);
			LineTo(hDC, 1200, 100 + TileSize * i);
		}
	}

	void setFields()
	{
		if (gameOption != 2)
		{
			for (size_t i = 0; i < 10; ++i)
			{
				for (size_t j = 0; j < firstPlayerShips[i].numberOfDecks; ++j)
				{
					firstPlayersField.push_back(firstPlayerShips[i].tiles[j]);
				}

				for (size_t j = 0; j < secondPlayerShips[i].numberOfDecks; ++j)
				{
					secondPlayersField.push_back(secondPlayerShips[i].tiles[j]);
				}
			}
		}
	}

	virtual void drawCheckIfFirstPlayerKill()
	{
		int counter = 0;
		for (size_t i = 0; i < 10; ++i)
		{
			if (!killed[i])
			{
				killed[i] = true;
				for (size_t j = 0; j < secondPlayerShips[i].numberOfDecks; ++j)
				{
					bool thisDeckKilled = false;
					for (size_t k = 0; k < goodTilesFirstPlayerKnow.size(); ++k)
					{
						if (goodTilesFirstPlayerKnow[k] == secondPlayerShips[i].tiles[j])
						{
							thisDeckKilled = true;
							break;
						}
					}

					if (!thisDeckKilled)
					{
						killed[i] = false;
						break;
					}
				}
			}
			if (killed[i])
			{
				counter++;
				for (size_t j = 0; j < 3 * secondPlayerShips[i].numberOfDecks + 7; ++j)
				{
					bool notShip = true;
					for (size_t k = 0; k < secondPlayerShips[i].numberOfDecks; ++k)
					{
						if (secondPlayerShips[i].adjancedTiles()[j] == secondPlayerShips[i].tiles[k])
						{
							notShip = false;
							break;
						}
					}

					if (notShip)
					{
						badTilesFirstPlayerKnow.push_back(secondPlayerShips[i].adjancedTiles()[j]);
					}
				}

				secondPlayerShips[i].drawShipInColor(secondPlayerShips[i].tiles[0].firstCoordinate * TileSize + 700, secondPlayerShips[i].tiles[0].secondCoordinate * TileSize + 100, "red");
			}
		}

		if (counter > 9)
		{
			firstPlayerWin = true;
		}

		SelectObject(hDC, hPenBLUE);
		for (size_t i = 0; i < badTilesFirstPlayerKnow.size(); ++i)
		{
			if (badTilesFirstPlayerKnow[i].firstCoordinate >= 0 && badTilesFirstPlayerKnow[i].secondCoordinate >= 0 && badTilesFirstPlayerKnow[i].firstCoordinate <= 9 && badTilesFirstPlayerKnow[i].secondCoordinate <= 9)
			{
				badTilesFirstPlayerKnow[i].drawInColor(badTilesFirstPlayerKnow[i].firstCoordinate * TileSize + 700, badTilesFirstPlayerKnow[i].secondCoordinate * TileSize + 100, "blue");
			}
		}
	}

	void drawCheckIfSecondPlayerKill()
	{
		int counter = 0;
		for (size_t i = 0; i < 10; ++i)
		{
			if (!killedFirstPlayersShips[i])
			{
				killedFirstPlayersShips[i] = true;
				for (size_t j = 0; j < firstPlayerShips[i].numberOfDecks; ++j)
				{
					bool thisDeckKilled = false;
					for (size_t k = 0; k < goodTilesSecondPlayerKnow.size(); ++k)
					{
						if (goodTilesSecondPlayerKnow[k] == firstPlayerShips[i].tiles[j])
						{
							thisDeckKilled = true;
							break;
						}
					}

					if (!thisDeckKilled)
					{
						killedFirstPlayersShips[i] = false;
						break;
					}
				}
			}
			if (killedFirstPlayersShips[i])
			{
				counter++;
				for (size_t j = 0; j < 3 * firstPlayerShips[i].numberOfDecks + 7; ++j)
				{
					bool notShip = true;
					for (size_t k = 0; k < firstPlayerShips[i].numberOfDecks; ++k)
					{
						if (firstPlayerShips[i].adjancedTiles()[j] == firstPlayerShips[i].tiles[k])
						{
							notShip = false;
							break;
						}
					}

					if (notShip)
					{
						badTilesSecondPlayerKnow.push_back(firstPlayerShips[i].adjancedTiles()[j]);
					}
				}

				firstPlayerShips[i].drawShipInColor(firstPlayerShips[i].tiles[0].firstCoordinate * TileSize + 100, firstPlayerShips[i].tiles[0].secondCoordinate * TileSize + 100, "red");
			}
		}

		if (counter > 9)
		{
			secondPlayerWin = true;
		}

		SelectObject(hDC, hPenBLUE);
		for (size_t i = 0; i < badTilesSecondPlayerKnow.size(); ++i)
		{
			if (badTilesSecondPlayerKnow[i].firstCoordinate >= 0 && badTilesSecondPlayerKnow[i].secondCoordinate >= 0 && badTilesSecondPlayerKnow[i].firstCoordinate <= 9 && badTilesSecondPlayerKnow[i].secondCoordinate <= 9)
			{
				badTilesSecondPlayerKnow[i].drawInColor(badTilesSecondPlayerKnow[i].firstCoordinate * TileSize + 100, badTilesSecondPlayerKnow[i].secondCoordinate * TileSize + 100, "blue");
			}
		}


	}

	void draw()
	{
		system("cls");

		setOptions();
		setFields();
		cleanScreen();
		drawFields();
		drawStartFirstPlayerYellowShips();

		while (!firstPlayerWin && !secondPlayerWin)
		{
			drawFirstPlayerShoot();
			drawSecondPlayerShoot();

			firstPlayerWin = true;
			secondPlayerWin = true;
			for (size_t i = 0; i < 10; ++i)
			{
				if (!killed[i])
				{
					firstPlayerWin = false;
				}
				if (!killedFirstPlayersShips[i])
				{
					secondPlayerWin = false;
				}
			}
		}

		if (firstPlayerWin && !secondPlayerWin)
		{
			system("cls");
			cleanScreen();

			for (size_t i = 0; i < 7; ++i)
			{
				cout << endl;
			}
			string spaces;
			for (size_t i = 0; i < 30; ++i)
			{
				spaces += " ";
			}
			if (gameOption == 1)
			{
				cout
					<< spaces << "     YOU WIN!!!" << endl
					<< spaces << "  CONGRATULATIONS!" << endl
					<< endl << endl << endl
					<< spaces << "PRESS ANY KEY TO EXIT" << endl;
			}
			if (gameOption == 3)
			{
				cout
					<< spaces << "FIRST PLAYER WIN!!!" << endl
					<< spaces << "  CONGRATULATIONS!" << endl
					<< endl << endl << endl
					<< spaces << "PRESS ANY KEY TO EXIT" << endl;
			}
			char c;
			c = _getch();
		}
		if (!firstPlayerWin && secondPlayerWin)
		{
			system("cls");
			cleanScreen();

			for (size_t i = 0; i < 7; ++i)
			{
				cout << endl;
			}
			string spaces;
			for (size_t i = 0; i < 30; ++i)
			{
				spaces += " ";
			}
			if (gameOption == 1)
			{
				cout
					<< spaces << "     YOU LOSE..." << endl
					<< spaces << "  TRY ONE MORE TIME" << endl
					<< endl << endl << endl
					<< spaces << "PRESS ANY KEY TO EXIT" << endl;
			}
			if (gameOption == 3)
			{
				cout
					<< spaces << "SECOND PLAYER WIN!!!" << endl
					<< spaces << "  CONGRATULATIONS!" << endl
					<< endl << endl << endl
					<< spaces << "PRESS ANY KEY TO EXIT" << endl;
			}
			char c;
			c = _getch();
		}
		if (firstPlayerWin && secondPlayerWin)
		{
			system("cls");
			cleanScreen();

			for (size_t i = 0; i < 7; ++i)
			{
				cout << endl;
			}
			string spaces;
			for (size_t i = 0; i < 25; ++i)
			{
				spaces += " ";
			}
			cout
				<< spaces << "                    IT IS DRAW!" << endl
				<< endl << endl << endl
				<< spaces << "                PRESS ANY KEY TO EXIT" << endl;

			char c;
			c = _getch();
		}

	}

	void drawTilesFirstPlayerKnow()
	{
		for (size_t i = 0; i < goodTilesFirstPlayerKnow.size(); ++i)
		{
			if (goodTilesFirstPlayerKnow[i].firstCoordinate >= 0 && goodTilesFirstPlayerKnow[i].secondCoordinate >= 0 && goodTilesFirstPlayerKnow[i].firstCoordinate <= 9 && goodTilesFirstPlayerKnow[i].secondCoordinate <= 9)
			{
				goodTilesFirstPlayerKnow[i].drawInColor(goodTilesFirstPlayerKnow[i].firstCoordinate * TileSize + 700, goodTilesFirstPlayerKnow[i].secondCoordinate * TileSize + 100, "green");
			}
		}

		drawCheckIfFirstPlayerKill();
	}

	void drawTilesSecondPlayerKnow()
	{
		for (size_t i = 0; i < goodTilesSecondPlayerKnow.size(); ++i)
		{
			if (goodTilesSecondPlayerKnow[i].firstCoordinate >= 0 && goodTilesSecondPlayerKnow[i].secondCoordinate >= 0 && goodTilesSecondPlayerKnow[i].firstCoordinate <= 9 && goodTilesSecondPlayerKnow[i].secondCoordinate <= 9)
			{
				goodTilesSecondPlayerKnow[i].drawInColor(goodTilesSecondPlayerKnow[i].firstCoordinate * TileSize + 100, goodTilesSecondPlayerKnow[i].secondCoordinate * TileSize + 100, "green");
			}
		}

		drawCheckIfSecondPlayerKill();
	}

	void drawStartFirstPlayerYellowShips()
	{
		for (size_t i = 0; i < 10; ++i)
		{
			firstPlayerShips[i].drawShipInColor(firstPlayerShips[i].tiles[0].firstCoordinate * TileSize + 100, firstPlayerShips[i].tiles[0].secondCoordinate * TileSize + 100, "yellow");
		}
	}

	void drawStartSecondPlayerYellowShips()
	{
		for (size_t i = 0; i < 10; ++i)
		{
			secondPlayerShips[i].drawShipInColor(secondPlayerShips[i].tiles[0].firstCoordinate * TileSize + 700, secondPlayerShips[i].tiles[0].secondCoordinate * TileSize + 100, "yellow");
		}
	}

	virtual void setOptions()
	{
	}

	virtual void drawFirstPlayerShoot() = 0;

	virtual void drawSecondPlayerShoot() = 0;
};