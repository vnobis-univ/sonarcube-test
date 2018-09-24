#pragma once
#include <string>

using namespace std;

class WarShip
{
public:
	string Name;
	int Size;
	int XPos;
	int YPos;
	bool isKilled;
	bool isHorizontal;
public:
	WarShip();
	WarShip(int);
	void size(int);
	void name(string);
	void setX(int);
	void setY(int);
	void setVector(bool);
	void setReady(bool);
	int getSize()const;
	void operator=(WarShip&);
};