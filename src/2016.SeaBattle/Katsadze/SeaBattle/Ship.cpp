#include "Ship.h"

WarShip::WarShip() : Size(0) {}

WarShip::WarShip(int i) : Size(0) {}

void WarShip::operator=(WarShip & ship)
{
	Name = ship.Name;
	Size = ship.Size;
	XPos = ship.XPos;
	YPos = ship.YPos;
	isHorizontal = ship.isHorizontal;
}

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
	XPos = x;
}

void WarShip::setY(int y)
{
	YPos = y;
}

void WarShip::setVector(bool _horisontal)
{
	isHorizontal = _horisontal;
}


void WarShip::setReady(bool sth)
{
	isKilled = sth;
}

int WarShip::getSize() const
{
	return Size;
}

