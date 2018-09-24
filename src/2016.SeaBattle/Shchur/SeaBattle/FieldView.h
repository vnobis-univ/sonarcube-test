#pragma once
#include <time.h>
#include "PreFieldView.h"
#include "HighscoresView.h"

enum FightStatus
{
	EmptyF, ShipF, Pass, Hit
};

class FieldView : public PreFieldView
{
	Lokalization language;
	FightStatus playerField[10][10];
	FightStatus computerField[10][10];
	EndStatus computerPort[10][10];
	short selectX;
	short selectY;
	int landslide_x;
	int landslide_y;
	int counterOfYourShips;
	int counterOfEnemyShips;
	int counter;
	WarShip* navy;
	WarShip* enemyNavy;
	short score;
public:
	FieldView(Lokalization, EndStatus**, WarShip*);
	void draw();
	View* handle();
	void printAllYourCells();
	void printAllEnemyCells(bool);
	void printYourCell(FightStatus, bool, short, short);
	void printEnemyCell(FightStatus, bool, short, short);
	void revealEnemyCell(FightStatus, EndStatus, short, short);
	bool isSelected(int, int);
	FightStatus getYourFieldStatus(int, int)const;
	EndStatus getEnemyFieldStatus(int, int)const;
	FightStatus getEnemyFightStatus(int, int)const;
	void enemyNavyInitializer();
	bool isThereEnemyShip(int, int);
	void enemyTurn();
	void againEnemyTurn(int, int);
	bool canPlaceComputerShip(int, int, int);
	void placeComputerShip();
	void placeComputerShips();
	void killedYourShips();
	void killedEnemyShips();
	void wasShipKilled(WarShip, FightStatus[10][10]);
	void congratulations();
	void loseSign();

	string getName();
	void scoreHandler();
};