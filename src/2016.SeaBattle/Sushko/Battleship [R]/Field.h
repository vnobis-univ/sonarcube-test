#pragma once
#include <Windows.h>
#include "ShipManager.h"

enum class CELL_STATE {EMPTY, SHIP, DAMAGED_SHIP, DESTROYED_SHIP, MISSED};

class Cell {
	
	static const int cellSize = 24;
	CELL_STATE state;
	int x;
	int y;
public:
	Cell(int _x = 0, int _y = 0, CELL_STATE st = CELL_STATE::EMPTY);
	
	CELL_STATE getState() const;
	void setState(CELL_STATE st);

	void draw(COORD edge, HPEN pen);
	void drawX(COORD edge, HPEN pen);
	void drawDot(COORD edge, HPEN pen);
};

class FieldView;

class Field {

	COORD edge;
	Cell field[10][10];
	vector<Ship> ships;

	void drawCells(bool update = false);
	void drawLatinNumbers();
public:
	Field(COORD _topLeftEdge);

	void draw();
	void deployShips();

	friend class FieldView;
	friend class ShipManager;
};