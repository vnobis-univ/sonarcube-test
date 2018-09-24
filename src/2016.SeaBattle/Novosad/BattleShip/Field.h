#pragma once
#include "CellState.h"
#include "RenderHelper.h"
#include <vector>
#include "Ship.h"
#include "FireDetails.h"

using namespace std;

class Field
{
protected:
	int locationX_;
	int locationY_;
	int size_;
	bool draw_ship_frame_;
	CellState field_[10][10];
	vector<Ship> ships_;
	RenderHelper renderer_;
	int isShipHit(int x, int y);
	void markKilledShipArea(Ship& ship);
	void drawShip(Ship& ship, bool drawWithFrame);
	void toggleShipFrame();
public:
	Field(int locationX, int locationY, int cell_width, int cell_height);
	CellState getCellState(int i, int j) const;
	vector<Ship> getShips();
	void setCellState(int i, int j, CellState state);
	void setLocationX(int x);
	void setLocationY(int y);
	int getLocationX() const;
	int getLocationY() const;
	int getSize() const;
	bool canPlace(Ship& ship);
	bool place(Ship& ship);
	void draw();
	virtual bool isReady();
	virtual bool allShipsKilled();
	virtual void finishBattle();
	virtual void submitFire(FireDetails details);
	virtual FireDetails waitForFire();
	virtual FireDetails waitForComputer(Field* field);
	virtual FireDetails fireAt(int x, int y);
};
