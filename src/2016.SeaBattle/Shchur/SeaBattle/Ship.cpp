#include "Ship.h"

WarShip::WarShip() : Size(0) {}

WarShip::WarShip(int i) : Size(0) {}

void WarShip::size(int k)
{
	Size = k;
}

void WarShip::name(string _name)
{
	Name = _name;
}

void WarShip::setX(int x)
{
	Xcoord = x;
}

void WarShip::setY(int y)
{
	Ycoord = y;
}

void WarShip::setVector(bool horiz)
{
	Horizontal = horiz;
}

void WarShip::setDeath(bool sth)
{
	isKilled = sth;
}

int WarShip::getSize() const
{
	return Size;
}

void WarShip::operator=(WarShip & ws)
{
	Name = ws.Name;
	Size = ws.Size;
	Xcoord = ws.Xcoord;
	Ycoord = ws.Ycoord;
	Horizontal = ws.Horizontal;
}


