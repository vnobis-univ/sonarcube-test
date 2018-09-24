#pragma once
#include "View.h"
#include "Lokalization.h"
#include "StartView.h"
#include "Ship.h"

enum PlacementStatus
{
	Empty, TempShip, ShipPlace
};

enum EndStatus
{
	EmptyField, Ship, Buffer
};

class PreFieldView : public View
{
	Lokalization language;
	int landslide_x;
	int landslide_y;
	short selectX;
	short selectY;
	PlacementStatus scheme[10][10];
	EndStatus** field;
	string alphabetEn[10] = { "R", "E", "S", "P", "U", "B", "L", "I", "C", "A" };
	string alphabetUa[10] = { "Ð", "Å", "Ñ", "Ï", "Ó", "Á", "Ë", "²", "Ê", "À" };
	WarShip* ship;
	int counterOfShip;
	bool horizontal;
public:
	PreFieldView();
	PreFieldView(Lokalization);
	void draw();
	View* handle();
	void printField();
	void drawAlphabet();
	PlacementStatus getSchemeStatus(short, short)const;
	void printAllPlacementCell();
	bool isSelected(short, short);
	void printPlacementCell(PlacementStatus, EndStatus, short, short);
	void shipsInitialiser();
	void changeShipPlace();
	bool canPlaceShip();
	void placeShip();
	void deleteTrace(Buttons);
	void startOfGame();
	void help();
	EndStatus getFieldStatus(short, short)const;
};