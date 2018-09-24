#pragma once
#include <vector>
using namespace std;


enum class StateOfShipCell
{
	Killed,
	NotKilled
};

enum class PositionOfShip
{
	Horizontal,
	Vertical
};

class Ship
{
private:
	int size;
	int coordinateXOfTopOfShip;
	int coordinateYOfTopOfShip;
	PositionOfShip position;
	StateOfShipCell* shipCells;
	void drawCell(double i, int j);
public:
	Ship(int _size = 4, PositionOfShip _position = PositionOfShip::Horizontal);
	Ship(int x, int y, int _size, PositionOfShip _position);
	void draw(int x, int y);
	PositionOfShip getPosition();
	int getSize();
	int getCoordinateXOfTopOfShip();
	int getCoordinateYOfTopOfShip();
	StateOfShipCell getStateOfShipCell(int x);
	void setStateOfShipCell(int x, StateOfShipCell state);
	void setPosition(PositionOfShip _position);
	void setX(int x);
	void setY(int y);
	bool isNotKilled();
	void getIndexOfFirstAndLastKilledCell(int&i, int&j);
};

