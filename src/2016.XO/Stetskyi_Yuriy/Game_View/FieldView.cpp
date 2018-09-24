#pragma once

#include <vector>

#include "SysUtils.h"
#include "ConsoleCustomize.h"
#include "GameFunctions.h"

extern const int CONSOLE_WIDTH;
extern const int CONSOLE_HEIGHT;
extern const int FONT_WIDTH;
extern const int FONT_HEIGHT;

using namespace std;

FieldView fieldView;

FieldView::FieldView()
	: selectedCell(0, 0)
{
}

void FieldView::draw()
{
	clear();

	vector<Cell> fields;
	int coordY = (CONSOLE_HEIGHT*FONT_HEIGHT) / 3;
	int coordX = (CONSOLE_WIDTH*FONT_WIDTH) / 3;
	fields.push_back(Cell(coordX, coordY, 50));

	//calculating cells' coordinates

	for (size_t i = 1; i <= 8; ++i)
	{
		if (i % 3 == 0)
		{
			coordX = (CONSOLE_WIDTH*FONT_WIDTH) / 3;
			coordY += 50;
		}
		else
		{
			coordX += 50;
		}

		fields.push_back(Cell(coordX, coordY, 50));
	}

	// painting cells in the window

	for (size_t i = 0; i < fields.size(); ++i)
	{
		fields[i].draw(RGB(100, 0, 0), RGB(200, 200, 0));
	}

	// GameFunctions.h function 
	playGame(fields);
}