#pragma once
#include "View.h"
#include "StartView.h"
#include "Ship.h"
#include "Buttons.h"

enum PlacementStatus
{
	Empty, TempShip, ShipPlace
};

enum FinalStatus
{
	EmptyField, Ship, Around
};

class PreFieldView : public View
{
	int landslide_x;
	int landslide_y;
	unsigned short selectedX;
	unsigned short selectedY;
	PlacementStatus matrix[10][10];
	FinalStatus** field;
	string numerationString[10] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };
	int numerationInt[10] = { 1,2,3,4,5,6,7,8,9,10 };
	WarShip* ship;
	int shipCounter;
	bool horizontal;
public:
	PreFieldView();
	void draw();
	void help();
	View* handle();
	void printField();
	FinalStatus getFieldStatus(short, short)const;
	PlacementStatus getStatus(short, short)const;
	void printAllPlacementCell();
	bool isSelected(short, short);
	void printPlacementCell(PlacementStatus, FinalStatus, short, short);
	void createShips();
	void deletePlace(unsigned short);
	void changePosition();
	bool isPlaceForShip();
	void placeShip();
	void drawNumeration();
	void beginGame();
	
	
};