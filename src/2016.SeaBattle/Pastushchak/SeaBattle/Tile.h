#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <conio.h>
#include <vector>
#include <Windows.h>
#include "Color.h"
#include "SetConsoleSize.h"
using namespace std;

extern HBRUSH hOldBrush;
extern HBRUSH hNewBrush;
extern HDC hDC;
extern const int TileSize;

class Tile
{
public:
	int firstCoordinate;
	int secondCoordinate;
public:
	Tile(int a = 0, int b = 0) :
		firstCoordinate(a),
		secondCoordinate(b)
	{
	}

	Tile& operator=(const Tile& t)
	{
		firstCoordinate = t.firstCoordinate;
		secondCoordinate = t.secondCoordinate;

		return *this;
	}

	void drawInColor(size_t x, size_t y, string color = "blue")
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

	vector<Tile> adjancedTiles()
	{
		vector<Tile> vec;

		for (int i = 0; i < 10; ++i)
		{
			for (size_t j = 0; j < 10; ++j)
			{
				int a = firstCoordinate - i;
				int b = secondCoordinate - j;
				if (abs(a) <= 1 && abs(b) <= 1)
				{
					Tile t(i, j);
					vec.push_back(t);
				}
			}
		}

		return vec;
	}

	bool operator!=(const Tile& t)
	{
		return !(firstCoordinate == t.firstCoordinate && secondCoordinate == t.secondCoordinate);
	}

	bool operator==(const Tile& t)
	{
		return (firstCoordinate == t.firstCoordinate && secondCoordinate == t.secondCoordinate);
	}
	
	friend ostream& operator<<(ostream& write, Tile& t)
	{
		write << (char)(t.firstCoordinate + 65) << " " << t.secondCoordinate + 1;
		return write;
	}
	friend istream& operator>>(istream& read, Tile& t)
	{
		char a;
		int b;
		read >> a >> b;
		t = Tile((int)(a -  65), b - 1);
		return read;
	}
};