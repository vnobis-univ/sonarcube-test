#pragma once
#include "Cell.h"
#include <vector>

using std::vector;


class Field;

enum class DIRECTION {DOWN, UP, LEFT, RIGHT};

class Ship
{
	vector<Cell> ship;
	void draw(HPEN pen, Field& field);
	
	void rotate(Field& field);
	void move(DIRECTION, Field& field);

	bool isLegal(Field& field);       //check for ships-neigbourh..
//	bool notOutOfRange(Field& field); //check for ship being inside of field
public:
	
	Ship(int size=1);
	

	void placeManualy(Field& field);
	bool placeRandom(Field& field);

	Cell getCoord(int index);
	vector<Cell> getCellsAround(Field& field);

	int getSize();
	
};