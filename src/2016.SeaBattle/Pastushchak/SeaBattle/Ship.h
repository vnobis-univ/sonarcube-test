#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <conio.h>
#include <Windows.h>
#include <string>
#include "Color.h"
#include "Tile.h"
#include "SetConsoleSize.h"
#include <ctime>
#include <vector>
using namespace std;

//magic
//do not touch this global variables!!!
const int TileSize = 50;
POINT op;
HWND hWnd = GetConsoleWindow();
HDC hDC = GetDC(hWnd);
HPEN hPenBLUE = CreatePen(PS_SOLID, 0, RGB(0, 0, 255));
HPEN hPenBLACK = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
HPEN hPenGREEN = CreatePen(PS_SOLID, 0, RGB(0, 255, 0));
HPEN hPenRED = CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
HPEN hPenYELLOW = CreatePen(PS_SOLID, 0, RGB(255, 255, 0));
HBRUSH hNewBrush;
HBRUSH hOldBrush;

class Ship
{
public:
	int numberOfDecks;
	bool isHorizontal;
	Tile* tiles;
	bool isAlive;
public:
	Ship(int n = 1, bool is = true, int headX = 0, int headY = 0) :
		numberOfDecks(n),
		isHorizontal(is),
		isAlive(true)
	{
		tiles = new Tile[numberOfDecks];
		for (size_t i = 0; i < numberOfDecks; ++i)
		{
			if (isHorizontal)
			{
				tiles[i].firstCoordinate = headX + i;
				tiles[i].secondCoordinate = headY;
			}
			else
			{
				tiles[i].firstCoordinate = headX;
				tiles[i].secondCoordinate = headY + i;
			}
		}
	}

	Ship& operator=(const Ship& s)
	{
		numberOfDecks = s.numberOfDecks;
		isHorizontal = s.isHorizontal;
		isAlive = s.isAlive;

		tiles = new Tile[numberOfDecks];
		for (size_t i = 0; i < numberOfDecks; ++i)
		{
			tiles[i] = s.tiles[i];
		}

		return *this;
	}

	bool operator==(const Ship& s)
	{
		if (numberOfDecks != s.numberOfDecks)
		{
			return false;
		}

		for (size_t i = 0; i < numberOfDecks; ++i)
		{
			if (tiles[i] != s.tiles[i])
			{
				return false;
			}
		}

		if (isHorizontal != s.isHorizontal)
		{
			return false;
		}

		return true;
	}

	Tile* adjancedTiles()
	{
		Tile* t = new Tile[3 * (numberOfDecks + 2)];

		if (isHorizontal)
		{
			for (int i = 0; i < numberOfDecks + 2; ++i)
			{
				t[i] = Tile(tiles[0].firstCoordinate - 1 + i, tiles[0].secondCoordinate - 1);
			}

			for (int i = 0; i < numberOfDecks + 2; ++i)
			{
				t[i + numberOfDecks + 2] = Tile(tiles[0].firstCoordinate - 1 + i, tiles[0].secondCoordinate);
			}

			for (int i = 0; i < numberOfDecks + 2; ++i)
			{
				t[i + 2 * numberOfDecks + 4] = Tile(tiles[0].firstCoordinate - 1 + i, tiles[0].secondCoordinate + 1);
			}
		}
		else
		{
			for (size_t i = 0; i < numberOfDecks + 2; ++i)
			{
				t[i] = Tile(tiles[0].firstCoordinate - 1, tiles[0].secondCoordinate - 1 + i);
			}

			for (size_t i = 0; i < numberOfDecks + 2; ++i)
			{
				t[i + numberOfDecks + 2] = Tile(tiles[0].firstCoordinate, tiles[0].secondCoordinate - 1 + i);
			}

			for (size_t i = 0; i < numberOfDecks + 2; ++i)
			{
				t[i + 2 * numberOfDecks + 4] = Tile(tiles[0].firstCoordinate + 1, tiles[0].secondCoordinate - 1 + i);
			}
		}

		return t;
	}

	void drawShip(size_t x, size_t y, string color = "green")//draw this ship in console with top left point P = (x,y)
	{
		if (color == "green")
		{
			SelectObject(hDC, hPenGREEN);
		}
		else
		{
			if (color == "yellow")
			{
				SelectObject(hDC, hPenYELLOW);
			}
			else
			{
				if (color == "red")
				{
					SelectObject(hDC, hPenRED);
				}
				else
				{
					if (color == "blue")
					{
						SelectObject(hDC, hPenBLUE);
					}
					else
					{
						SelectObject(hDC, hPenBLACK);
					}
				}
			}
		}

		MoveToEx(hDC, x, y, &op);
		if (isHorizontal)
		{
			LineTo(hDC, x, y + TileSize);
			LineTo(hDC, x + TileSize * numberOfDecks, y + TileSize);
			LineTo(hDC, x + TileSize * numberOfDecks, y);
			LineTo(hDC, x, y);
		}
		else
		{
			LineTo(hDC, x + TileSize, y);
			LineTo(hDC, x + TileSize, y + TileSize * numberOfDecks);
			LineTo(hDC, x, y + TileSize * numberOfDecks);
			LineTo(hDC, x, y);
		}
	}

	void drawShipInColor(size_t x, size_t y, string color = "green")
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
				if (color == "blue")
				{
					hNewBrush = CreateSolidBrush(0xff0000);
				}
				else
				{
					if (color == "yellow")
					{
						hNewBrush = CreateSolidBrush(0x00ffff);
					}
				}
			}
		}

		hOldBrush = (HBRUSH)SelectObject(hDC, hNewBrush);

		if (isHorizontal)
		{
			Rectangle(hDC, x, y, x + TileSize * numberOfDecks, y + TileSize);
		}
		else
		{
			Rectangle(hDC, x, y, x + TileSize, y + TileSize * numberOfDecks);
		}

		DeleteObject(hOldBrush);
		DeleteObject(hNewBrush);
	}

	friend ostream& operator<<(ostream& write, Ship& s)
	{
		write << s.numberOfDecks << " " << s.isHorizontal;
		for (size_t i = 0; i < s.numberOfDecks; ++i)
		{
			write << s.tiles[i] << " ";
		}

		write << endl;

		return write;
	}
};