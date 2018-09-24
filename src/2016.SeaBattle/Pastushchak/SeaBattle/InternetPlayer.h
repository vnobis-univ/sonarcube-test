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
//this works almost correctly
//but there are some bugs in internert server connection
class InternetPlayer : public Game//to be continued
{
private:
	vector<Ship> yourShips;
	int counterKilled;
	bool createOrJoin;//0 - creator of room, 1 - joined to room
	string prevQuest;
	string quest;
public:
	InternetPlayer() :
		createOrJoin(false),
		counterKilled(0)
	{
	}

	void drawKnownTiles()
	{
		for (size_t i = 0; i < goodTilesFirstPlayerKnow.size(); ++i)
		{
			goodTilesFirstPlayerKnow[i].drawInColor(goodTilesFirstPlayerKnow[i].firstCoordinate * TileSize + 700, goodTilesFirstPlayerKnow[i].secondCoordinate * TileSize + 100, "green");
		}

		for (size_t i = 0; i < badTilesFirstPlayerKnow.size(); ++i)
		{
			badTilesFirstPlayerKnow[i].drawInColor(badTilesFirstPlayerKnow[i].firstCoordinate * TileSize + 700, badTilesFirstPlayerKnow[i].secondCoordinate * TileSize + 100, "blue");
		}

		for (size_t i = 0; i < goodTilesSecondPlayerKnow.size(); ++i)
		{
			goodTilesSecondPlayerKnow[i].drawInColor(goodTilesSecondPlayerKnow[i].firstCoordinate * TileSize + 100, goodTilesSecondPlayerKnow[i].secondCoordinate * TileSize + 100, "green");
		}

		for (size_t i = 0; i < badTilesSecondPlayerKnow.size(); ++i)
		{
			badTilesSecondPlayerKnow[i].drawInColor(badTilesSecondPlayerKnow[i].firstCoordinate * TileSize + 100, badTilesSecondPlayerKnow[i].secondCoordinate * TileSize + 100, "blue");
		}
	}

	void setOptions()
	{
		cleanScreen();
		system("cls");

		int selectedOption = 0;
		bool pressedEnter = false;

		while (!pressedEnter)
		{
			system("cls");
			SetConsoleTextAttribute(hConsole, Blue);

			for (size_t i = 0; i < 10; ++i)
				cout << endl;

			const string spaces = "                                 ";

			switch (selectedOption)
			{

			case 0:
			{
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << "CREATE  ROOM" << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				cout << spaces << "JOIN TO ROOM" << endl;
				break;
			}

			case 1:
			{
				cout << spaces << "CREATE  ROOM" << endl;
				SetConsoleTextAttribute(hConsole, Green);
				cout << spaces << "JOIN TO ROOM" << endl;
				SetConsoleTextAttribute(hConsole, Blue);
				break;
			}

			}

			char selectOption = ' ';
			selectOption = _getch();

			switch (selectOption)
			{
			case 72:
			{
				--selectedOption;
				break;
			}

			case 75:
			{
				--selectedOption;
				break;
			}

			case 77:
			{
				++selectedOption;
				break;
			}

			case 80:
			{
				++selectedOption;
				break;
			}

			case 13:
			{
				pressedEnter = true;
				break;
			}

			default:
			{
				break;
			}
			}

			if (selectedOption < 0) selectedOption += 2;
			if (selectedOption > 1) selectedOption -= 2;
		}

		if (selectedOption == 0)
		{
			createOrJoin = false;
			connection.getNewRoom();
			system("cls");
			for (size_t i = 0; i < 10; ++i)
			{
				cout << endl;
			}

			for (size_t i = 0; i < 30; ++i)
			{
				cout << " ";
			}

			wstring s = connection.getNewRoom();
			wcout << "ROOM'S ID: " << s << endl<<endl<<endl;

			connection.setID(s);

	
			bool join = false;
			while (!join)
			{
				Sleep(1000);
				if (connection.get() == "Joined")
				{
					join = true;
				}
			}
		}
		else
		{
			createOrJoin = true;
			system("cls");
			for (size_t i = 0; i < 10; ++i)
			{
				cout << endl;
			}

			for (size_t i = 0; i < 25; ++i)
			{
				cout << " ";
			}

			cout << "PLEASE WRITE ROOM'S ID"<<endl;
			wstring idRoom;
			wcin >> idRoom;
			connection.setID(idRoom);
			system("cls");
			for (size_t i = 0; i < 23; ++i)
			{
				cout << " ";
			}

			connection.postMessage("Joined");
		
			
		}

		yourShips = firstPlayerShips;
	}

	void yourAnswer()
	{
		while (prevQuest == quest)
		{
			prevQuest = quest;
			quest = connection.get();
			Sleep(1000);
		}

		string enemyTurn = quest;

		int firstCoord, secondCoord;
		firstCoord = (int)enemyTurn[0] - 65;
		secondCoord = (int)enemyTurn[1] - 48;

		Tile t(firstCoord, secondCoord);

		bool land = false;
		for (size_t i = 0; i < 10; ++i)
		{
			for (size_t j = 0; j < yourShips[i].numberOfDecks; ++j)
			{
				if (t == yourShips[i].tiles[j])
				{
					land = true;
					break;
				}
			}
		}

		if (land)
		{
			goodTilesSecondPlayerKnow.push_back(t);
			connection.postMessage("Land");
			yourAnswer();
		}
		else
		{
			badTilesSecondPlayerKnow.push_back(t);
			connection.postMessage("Miss");
		}

		drawKnownTiles();
	}

	string getAnswer()
	{
		string prev = connection.get();
		string now = connection.get();

		while (prev == now)
		{
			prev = now;
			now = connection.get();			
			Sleep(1000);
		}

		return now;
	}

	void drawFirstPlayerShoot()
	{		
		if (createOrJoin == true)
		{
			yourAnswer();
		}

		drawKnownTiles();
		if (!secondPlayerWin && !secondPlayerWin)
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

			drawKnownTiles();

			Tile yourShoot(xCoord, yCoord);
			string turn;
			turn += (char)(xCoord + 65);
			turn += to_string(yCoord + 1);

			connection.postMessage(turn);

			string answer = getAnswer();

			if (answer == "Land")
			{
				goodTilesFirstPlayerKnow.push_back(yourShoot);
				drawFirstPlayerShoot();
			}
			else
			{
				badTilesFirstPlayerKnow.push_back(yourShoot);
			}
		}
	}

	void drawSecondPlayerShoot()
	{
		drawKnownTiles();
	}
};