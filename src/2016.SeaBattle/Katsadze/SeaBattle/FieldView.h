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
	FightStatus playerField[10][10];
	FightStatus computerField[10][10];
	FinalStatus computerPort[10][10];
	short selectedX;
	short selectedY;
	int counterOfYourShips;
	int counterOfEnemyShips;
	int counter;
	WarShip* navy;
	WarShip* botNavy;
	short score;
public:
	FieldView(FinalStatus**, WarShip*);
	void draw();
	View* handle();
	void printAllYourCells();
	void printAllEnemyCells(bool);
	void printYourCell(FightStatus, bool, short, short);
	void printEnemyCell(FightStatus, bool, short, short);
	void revealEnemyCell(FightStatus, FinalStatus, short, short);
	bool isSelected(int, int);
	FightStatus getYourFieldStatus(int, int)const;
	FinalStatus getEnemyFieldStatus(int, int)const;
	FightStatus getEnemyFightStatus(int, int)const;
	void createBotShips();
	bool isThereEnemyShip(int, int);
	void enemyTurn();
	void againEnemyTurn(int, int);
	bool canplaceBotShip(int, int, int);
	void placeBotShip();
	void placeBotShips();
	void killedYourShips();
	void killedEnemyShips();
	void wasShipKilled(WarShip, FightStatus[10][10]);
	void congratulations();
	void loseSign();

	string getName();
	void scoreHandler();
};