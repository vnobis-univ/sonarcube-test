#pragma once
#include "View.h"
#include "Field.h"
#include "Ship.h"
class GameView : public View
{
	unsigned numberOfSelectedShip;
	Field myField;
	Field oponentsField;
	Ship arrayOfShips[sizeOfField];
	Ship arrayOfOponentsShips[sizeOfField];
	Ship selectedShip;
	Ship oponentsShip;
	Cell selectedCell;
	View * nextView();
	void drawPreviousShips();
	void nearOrMiss(Field &field, int startOfField, CellStatus stat);
	void oponentField();
	int placeOfSelectedCellX;
	int placeOfSelectedCellY;
	void drawCross(int x, int y);
	void drawDot(int x, int y);
	void drawOponentsShips();
	void killingTheShip();
	void myShipsKilling(int &i, int & j);
	void drowMissed(Ship ship , Field & field, int startOfField);
	bool myWIn();
	bool oponentsWIn();
public:
	GameView(Languages _lang, TypeOfGame _type);
	void draw();
	View* handle();
};

