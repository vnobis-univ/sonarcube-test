#pragma once
#include "Field.h"
#include "Ship.h"
#include <vector>

class ComputerField : public Field
{
	FireDetails last_details_;
	void setRandomEnemyShips();
	bool needsToFinishShip(int& indexOfShip, vector<Ship> myShips);
public:
	ComputerField(
		int locationX, 
		int locationY, 
		int cell_width, 
		int cell_height);

	void submitFire(FireDetails details) override;
	FireDetails ComputerField::waitForFire() override;
	FireDetails ComputerField::waitForComputer(Field* field) override;
};
