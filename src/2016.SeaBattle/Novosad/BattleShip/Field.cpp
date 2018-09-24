#include "Field.h"
#include <windows.h>
#include <wingdi.h>

Field::Field(int locationX, int locationY, int cell_width, int cell_height) :
	locationX_(locationX),
	locationY_(locationY),
	size_(10),
	renderer_(cell_width, cell_height),
	draw_ship_frame_(true)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			field_[j][i] = CellState::Empty;
		}
	}
}

CellState Field::getCellState(int i, int j) const
{
	return field_[j][i];
}

vector<Ship> Field::getShips()
{
	return ships_;
}

void Field::setCellState(int i, int j, CellState state)
{
	if (i >= 0 && j >= 0)
	{
		field_[j][i] = state;
	}
}

void Field::setLocationX(int x)
{
	locationX_ = x;
}

void Field::setLocationY(int y)
{
	locationY_ = y;
}

int Field::getLocationX() const
{
	return locationX_;
}

int Field::getLocationY() const
{
	return locationY_;
}

int Field::getSize() const
{
	return size_;
}

FireDetails Field::fireAt(int x, int y)
{
	FireDetails details;
	details.Result = FireResult::Miss;
	details.X = x;
	details.Y = y;
	details.ShipSize = -1;

	int shipIndex = isShipHit(x, y);
	setCellState(x, y, CellState::Missed);

	if (shipIndex >= 0)
	{
		details.Result = FireResult::Hit;

		if (x == ships_[shipIndex].getLocationX())
		{
			int shipY = y - ships_[shipIndex].getLocationY();
			ships_[shipIndex].setCellState(shipY, CellState::Hit);
		}
		else
		{
			int shipX = x - ships_[shipIndex].getLocationX();
			ships_[shipIndex].setCellState(shipX, CellState::Hit);
		}

		if (ships_[shipIndex].isNotKilled() == false)
		{
			if (allShipsKilled())
			{
				details.Result = FireResult::AllKilled;
			}
			else
			{
				details.Result = FireResult::Kill;
			}
			details.ShipSize = ships_[shipIndex].getSize();
			markKilledShipArea(ships_[shipIndex]);
		}
	}
	return details;
}

FireDetails Field::waitForFire()
{
	return FireDetails();
}
FireDetails Field::waitForComputer(Field* field)
{
	return FireDetails();
}

void Field::submitFire(FireDetails details)
{
}

bool Field::canPlace(Ship& ship)
{
	if (ship.getLocationX() < 0 || ship.getLocationY() < 0)
	{
		return false;
	}

	bool canBePlaced = true;

	int shipLocationY = ship.getLocationY() - 1;
	int shipLocationX = ship.getLocationX() - 1;
	int width = 3;
	int height = 3;

	if (ship.getOrientation() == ShipOrientation::Horizontal)
	{
		width = ship.getSize() + 2;
	}
	else
	{
		height = ship.getSize() + 2;
	}

	/*if (ship.getLocationX() < 0 ||
		ship.getLocationX() + width > 10 ||
		ship.getLocationY() < 0 ||
		ship.getLocationY() + height > 10)
	{
		return false;
	}*/

	for (int k = 0; k < ships_.size(); k++)
	{
		int placedShipX = ships_[k].getLocationX();
		int placedShipY = ships_[k].getLocationY();
		int placedShipWidth = 1;
		int placedShipHeight = 1;

		if (ships_[k].getOrientation() == ShipOrientation::Horizontal)
		{
			placedShipWidth = ships_[k].getSize();
		}
		else
		{
			placedShipHeight = ships_[k].getSize();
		}

		for (int i = shipLocationY; i < shipLocationY + height; i++)
		{
			for (int j = shipLocationX; j < shipLocationX + width; j++)
			{
				if (j >= placedShipX
					&& j < placedShipX + placedShipWidth
					&& i >= placedShipY
					&& i < placedShipY + placedShipHeight)
				{
					canBePlaced = false;
					return canBePlaced;
				}
			}
		}
	}

	return canBePlaced;
}

bool Field::place(Ship& ship)
{
	if (canPlace(ship))
	{
		ships_.push_back(ship);
		return true;
	}

	return false;
}

int Field::isShipHit(int x, int y)
{
	int shipIndex = -1;

	for (int i = 0; i < ships_.size(); i++)
	{
		for (int j = 0; j < ships_[i].getSize(); j++)
		{
			if (ships_[i].getOrientation() == ShipOrientation::Horizontal)
			{
				if (y == ships_[i].getLocationY() &&
					x >= ships_[i].getLocationX() &&
					x <= ships_[i].getLocationX() + ships_[i].getSize() - 1 &&
					ships_[i].getCellState(j) == CellState::Empty)
				{
					shipIndex = i;
					break;
				}
			}
			else
			{
				if (x == ships_[i].getLocationX() &&
					y >= ships_[i].getLocationY() &&
					y <= ships_[i].getLocationY() + ships_[i].getSize() - 1 &&
					ships_[i].getCellState(j) == CellState::Empty)
				{
					shipIndex = i;
					break;
				}
			}
		}

		if (shipIndex >= 0)
		{
			break;
		}
	}

	return shipIndex;
}

void Field::markKilledShipArea(Ship& ship)
{
	int shipLocationY = ship.getLocationY() - 1;
	int shipLocationX = ship.getLocationX() - 1;
	int width = 3;
	int height = 3;

	if (ship.getOrientation() == ShipOrientation::Horizontal)
	{
		width = ship.getSize() + 2;
	}
	else
	{
		height = ship.getSize() + 2;
	}

	for (int y = shipLocationY; y < shipLocationY + height; y++)
	{
		for (int x = shipLocationX; x < shipLocationX + width; x++)
		{
			if (y >= 0 && y <= 9 && x >= 0 && x <= 9)
			{
				setCellState(x, y, CellState::Missed);
			}
		}
	}
}

bool Field::allShipsKilled()
{
	bool result = true;
	for (int i = 0; i < ships_.size(); i++)
	{
		for (int j = 0; j < ships_[i].getSize(); j++)
		{
			if (ships_[i].isNotKilled())
			{
				result = false;
			}
		}
		if (!result)
		{
			break;
		}
	}
	return result;
}

void Field::finishBattle()
{
}

void Field::draw()
{
	COLORREF color_red = RGB(255, 0, 0);
	COLORREF color_yellow = RGB(255, 0, 0);

	// drawing field grid
	for (size_t i = 0; i < 11; i++)
	{
		renderer_.drawLine(locationX_ + i, locationY_, locationX_ + i, locationY_ + 10, color_red);
		renderer_.drawLine(locationX_, locationY_ + i, locationX_ + 10, locationY_ + i, color_red);
	}

	// drawing field cells
	for (size_t i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (field_[i][j])
			{
			case CellState::Missed:
				renderer_.drawMissedCellState(locationX_ + j, locationY_ + i, color_red);
				break;
			case CellState::Hit:
				renderer_.drawHitCellState(locationX_ + j, locationY_ + i, color_yellow);
				break;
			case CellState::Empty:;
			default:
				break;
			}
		}
	}

	// draw ships with or without frame
	for (size_t i = 0; i < ships_.size(); i++)
	{
		drawShip(ships_[i], draw_ship_frame_);
	}
}

bool Field::isReady()
{
	return true;
}

void Field::drawShip(Ship& ship, bool drawWithFrame)
{
	COLORREF color_yellow = RGB(255, 255, 3);

	if (drawWithFrame)
	{
		if (ship.getOrientation() == ShipOrientation::Horizontal)
		{
			renderer_.drawRectangle(
				locationX_ + ship.getLocationX(),
				locationY_ + ship.getLocationY(),
				ship.getSize(), 1,
				color_yellow);
		}
		else
		{
			renderer_.drawRectangle(
				locationX_ + ship.getLocationX(),
				locationY_ + ship.getLocationY(),
				1, ship.getSize(),
				color_yellow);
		}
	}

	for (int i = 0; i < ship.getSize(); i++)
	{
		if (ship.getOrientation() == ShipOrientation::Horizontal && ship.getCellState(i) == CellState::Hit)
		{
			renderer_.drawHitCellState(
				locationX_ + ship.getLocationX() + i,
				locationY_ + ship.getLocationY(),
				color_yellow);
		}
		else if (ship.getOrientation() == ShipOrientation::Vertical && ship.getCellState(i) == CellState::Hit)
		{
			renderer_.drawHitCellState(
				locationX_ + ship.getLocationX(),
				locationY_ + ship.getLocationY() + i,
				color_yellow);
		}
	}
}

void Field::toggleShipFrame()
{
	draw_ship_frame_ = !draw_ship_frame_;
}
