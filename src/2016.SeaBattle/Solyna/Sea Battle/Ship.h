#pragma once
#include "globals.h"
#include "Cell.h"
enum class Visibility
{
	Visible,
	Invisible
};
enum class Orientation
{
	Horizontal,
	Vertical
};
enum class ShipStatus
{
	Killed,
	NotKilled
};
class Ship
{
	int size;
	Cell * arrayOfCells;
	Visibility visibility;
	Orientation orientation;
	ShipStatus status;
	int coordinateX;
	int coordinateY;
	int red;
	int green;
	int blue;
public:
	Ship();
	Ship(int _size, Visibility _visibility, int _red, int _green, int _blue);
	void draw(int _coordinateX, int _coordinateY);
	void setCoordinateX(int _coordinateX);
	void setCoordinateY(int _coordinateY);
	void setVisibility(Visibility visib);
	void setOrientation(Orientation orient);
	void setStatus(ShipStatus stat);
	int getCoordinateX();
	int getCoordinateY();
	int getSize();
	ShipStatus getStatus();
	Visibility getVisibility();
	void changeColor();
	void backToColor();
	void toMainColor();
	Cell &getCell(int i);
	Orientation getOrientation();
	void turning();
};

