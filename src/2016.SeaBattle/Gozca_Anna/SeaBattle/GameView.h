#pragma once
#include "View.h"
#include "Field.h"
#include <vector>
#include "Ship.h"
#include "LanguageView.h"

class GameView :public View
{
private:
	Language language;
	int score;
	Ship currentShip;
	Field myField;
	vector<Ship> myShips;
	Field enemyField;
	vector<Ship> enemyShips;
	int currentX = 0;
	int currentY = 0;
	int counter = 0;
	bool areMyShipsSet = false;
	const static int amountOfShips = 10;
	bool shipIsPlaced[amountOfShips];
	void drawMyShip(Ship myShip);
	int getSizeOfCurrShip();
	void setRandomEnemyShips();
	bool isPossibleToPutShipHere(int x, int y, int size, PositionOfShip pos, vector<Ship> vector);
	bool isShipHit(int x, int y, vector<Ship> ships, int& indexOfShip, int& indexOfCellOfShip);
	void computerMakesMove();
	bool playerWon(vector<Ship> ships);
	bool needsToFinishShip(int& indexOfShip);
	void changeStatesAroundKilledShip(Ship ship, Field& field);
	int getExtraPointsForKillingShip(int indexOfShip);
public:
	GameView();
	GameView(Language _language, int _score = 0);
	void draw();
	void printLogo();
	View* handle();
};