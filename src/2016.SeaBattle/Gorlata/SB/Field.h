#pragma once
#include "Cell.h"
#include "Ship.h"
#include <vector>
#include "LanguageSelection.h"

using std::vector;



class Field
{
	int coordX;        //coords of top left edge
	int coordY;
	
	Cell field[12][12];
	vector<Ship> crew;
	Ship& getShipAt(int x, int y);

public:
	Field(int _x, int _y);
	void draw();

	void positioningPlayer();
	void positioningComp();

	void makeMovePlayer(int& count, int& playerScores);
	void makeMoveGPU(int& count, int x, int y);


	void update();

	friend class Ship;


};