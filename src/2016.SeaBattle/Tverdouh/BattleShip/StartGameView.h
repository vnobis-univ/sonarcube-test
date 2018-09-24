#pragma once
#include "Ship.h"
#include <Windows.h>
#include "Buttons.h"
#include "Colors.h"
#include "FunctionsForGame.h"

enum PoleStatus
{
	Empty, TempShip, ShipPlace
};

enum EndStatus
{
	EmptyField, Ship, Buffer
};

class StartGameView
{

	int lines_x;
	int lines_y;
	short selectX;
	short selectY;
	PoleStatus pole[10][10];
	EndStatus** field;
	WarShip* ship;
	int counterOfShip;
	bool horizontal;
public:
	StartGameView();
	void drawMenu();
	void draw();
	void printField();
	PoleStatus getpoleStatus(short, short)const;
	void printAllPlacementCell();
	bool isSelected(short, short);
	void printPlacementCell(PoleStatus, EndStatus, short, short);
	void shipsInitialiser();
	void changeShipPlace();
	bool canPlaceShip();
	void placeShip();
	void deleteTrace(Buttons);
	void startOfGame();
	void help();
	EndStatus getFieldStatus(short, short)const;
};