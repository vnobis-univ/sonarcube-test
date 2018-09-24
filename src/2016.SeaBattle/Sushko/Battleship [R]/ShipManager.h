#pragma once
#include <vector>
#include <Windows.h>
#include <string>
using std::string;
using std::vector;

enum class Direction { HORIZONTAL, VERTICAL };

struct Ship_Coord {
	COORD coord;
	bool damaged;

	Ship_Coord(COORD coord = { -1,-1 }, bool _damaged = false);
	
};

struct Ship {

	vector<Ship_Coord> coords;
	Ship(size_t _size = 0);
	void setDamage(COORD coord);
	bool destroyed();
	
	string getCoords();
};

class Field;

class ShipManager {

	Field* field;
	vector<Ship> fleet;

	bool isLegal(vector<COORD>& illegal, Ship& ship);
	bool validCoords(COORD& coord, Ship& ship, Direction dir);
	void rotateShip(Ship& ship, Direction& dir, COORD coord);
	void drawShip(HPEN pen,COORD& coord, Ship& ship, Direction dir);

public:
	ShipManager(Field* fld = nullptr);
	
	Ship& getShipWithCoords(COORD coord, vector<Ship>& fleet);

	void deployShips();

	
};