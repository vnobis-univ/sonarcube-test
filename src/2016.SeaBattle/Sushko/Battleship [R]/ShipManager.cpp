#include "ShipManager.h"
#include "ExternUtils.h"
#include "Field.h"
#include <iostream>

using std::to_string;

Ship::Ship(size_t _size) : coords(vector<Ship_Coord>(_size)) {
	//for (int i = 0; i < _size; i++)
	//	coords[i] = COORD{ -1,-1 };
}

void Ship::setDamage(COORD coord)
{
	for (auto& i : coords) {
		if (i.coord.X == coord.X && i.coord.Y == coord.Y) {
			i.damaged = true;
			return;
		}
	}
}

bool Ship::destroyed() {

	for (auto& i : coords) {
		white.midLinePrint(23, to_string(i.damaged) + " ");
		if (!i.damaged)
			return false;
	}

	return true;
}

string Ship::getCoords()
{
	string request = "";

	for (auto i : coords) {
		request += to_string(i.coord.X);
		request += to_string(i.coord.Y);
	}

	return request;
}

bool ShipManager::isLegal(vector<COORD>& illegal, Ship& ship)
{
	bool legal = true;

	for (auto& i : illegal) {
		for (auto& j : ship.coords) {
			if (i.X == j.coord.X && i.Y == j.coord.Y) {
				legal = false;
				field->field[i.X][i.Y].draw(field->edge, red);
			}
		}
	}

	if(!legal) Sleep(200);
	
	return legal;
}

bool ShipManager::validCoords(COORD& moved, Ship& i, Direction direct)
{
	if (direct == Direction::HORIZONTAL) {
		return moved.X >= 0 && moved.X + i.coords.size() <= 10 && moved.Y >= 0 && moved.Y <= 9;
	}
	else
		return moved.Y >= 0 && moved.X >= 0 && moved.X <= 9 && moved.Y + i.coords.size() <= 10;
}

void ShipManager::rotateShip(Ship& ship, Direction& dir, COORD coord) {

	if (dir == Direction::HORIZONTAL && validCoords(coord, ship, Direction::VERTICAL)) {
		drawShip(blue, coord, ship, dir);
		dir = Direction::VERTICAL;
	}
	else if (dir == Direction::VERTICAL  && validCoords(coord, ship, Direction::HORIZONTAL)) {
		drawShip(blue, coord, ship, dir);
		dir = Direction::HORIZONTAL;
	}
}

void ShipManager::drawShip(HPEN pen, COORD& coord, Ship& ship, Direction dir)
{
	field->drawCells(true);
	field->field[coord.X][coord.Y].draw(field->edge, pen);
	ship.coords[0].coord = { coord.X, coord.Y };
	
	if (dir == Direction::HORIZONTAL) {
		for (int i = coord.X + 1, k = 1; i < coord.X + ship.coords.size(); i++) {
			ship.coords[k++].coord = { (short)i, coord.Y };
			field->field[i][coord.Y].draw(field->edge, pen);
		}
	}
	else {
		for (int i = coord.Y + 1, k=1; i < coord.Y + ship.coords.size(); i++) {
			ship.coords[k++].coord = { coord.X, (short)i };
			field->field[coord.X][i].draw(field->edge, pen);
		}
	}
}

ShipManager::ShipManager(Field* fld): field(fld), fleet(vector<Ship>(10)) {

	fleet[0] = Ship(4);
	fleet[1] = Ship(3);
	fleet[2] = Ship(3);
	fleet[3] = Ship(2);
	fleet[4] = Ship(2);
	fleet[5] = Ship(2);
	fleet[6] = Ship(1);
	fleet[7] = Ship(1);
	fleet[8] = Ship(1);
	fleet[9] = Ship(1);
}

Ship& ShipManager::getShipWithCoords(COORD coord, vector<Ship>& _fleet){
	
	for (auto& i : _fleet) {
		for (auto j : i.coords) {
			white.midLinePrint(23, to_string(j.coord.X) + " ");
			if (j.coord.X == coord.X && j.coord.Y == coord.Y)
				return i;
		}
	}
}

void ShipManager::deployShips()
{
	vector<COORD> illegal;
	
	for (Ship& i : fleet) {
	
		COORD coord = { 0,0 };
		COORD moved = coord;
		Direction dir = Direction::HORIZONTAL;

		bool deployed = false;
		while (!deployed) {

			drawShip(yellowPen, coord, i, dir);

			switch (_getwch())
			{
			case 77:          // right arrow
				moved.X++;
				break;
			case 75:          // left  arrow
				moved.X--;
				break;
			case 72:          // down arrow
				moved.Y--;
				break;
			case 80:          // up arrow
				moved.Y++;
				break;
			case 13:
				if (validCoords(coord, i, dir)) {
					if (isLegal(illegal, i)) {
						deployed = true;
						field->ships.push_back(i);

						for (int j = 0; j < i.coords.size(); j++) {
							field->field[i.coords[j].coord.X][i.coords[j].coord.Y].setState(CELL_STATE::SHIP);

							for (int k = 0; k < i.coords.size(); k++) {
								illegal.push_back(i.coords[j].coord);
							
								illegal.push_back({ i.coords[j].coord.X + 1, i.coords[j].coord.Y });					
								illegal.push_back({ i.coords[j].coord.X - 1, i.coords[j].coord.Y });
								illegal.push_back({ i.coords[j].coord.X, i.coords[j].coord.Y + 1 });
								illegal.push_back({ i.coords[j].coord.X + 1, i.coords[j].coord.Y - 1 });
								illegal.push_back({ i.coords[j].coord.X + 1, i.coords[j].coord.Y - 1 });
								illegal.push_back({ i.coords[j].coord.X - 1, i.coords[j].coord.Y - 1 });
								illegal.push_back({ i.coords[j].coord.X + 1, i.coords[j].coord.Y + 1 });
								illegal.push_back({ i.coords[j].coord.X - 1, i.coords[j].coord.Y + 1 });
							}
						}
						field->drawCells();
					}
				}
				break;
			case 113:
			case 1081:
				rotateShip(i, dir, coord);
				break;
			}

			if (!deployed) {
				if (validCoords(moved, i, dir)) {
					drawShip(blue, coord, i, dir);
					coord = moved;
				}
				else
					moved = coord;
			}
		}
	}

	field->ships = fleet;
}

Ship_Coord::Ship_Coord(COORD _coord, bool _damaged): coord(_coord), damaged(_damaged)
{
}
