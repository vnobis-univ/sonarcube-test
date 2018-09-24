#pragma once
#include <string>

using namespace std;

class WarShip
{
public:
	string Name;
	int Size;
	int Xcoord;
	int Ycoord;
	bool Horizontal;
	bool isKilled;
public:
	WarShip();
	WarShip(int);
	void size(int);
	void name(string);
	void setX(int);
	void setY(int);
	void setVector(bool);
	void setDeath(bool);
	int getSize()const;
	void operator=(WarShip&);
};