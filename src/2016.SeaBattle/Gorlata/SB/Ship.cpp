#include "Ship.h"
#include "Field.h"
#include "Utils.h"
#include "Cell.h"

void Ship::draw(HPEN pen, Field& field)
{
	for (auto& i : ship) 
	{
		i.draw(field.coordX, field.coordY, pen);
	}
}

void Ship::rotate(Field& field)
{
	Ship temp = *this;

	bool isLegal = true;
	
	if (this->ship.size() > 1)
	{
		bool horizontal = ship[0].getY() == ship[1].getY();

		for (int i = 1; i < ship.size(); ++i)
		{
			if (horizontal) {
				ship[i].setX(ship[0].getX());
				ship[i].setY(ship[0].getY() + i);
			}
			else {
				ship[i].setY(ship[0].getY());
				ship[i].setX(ship[0].getX() + i);
			}
			if (!ship[i].isValid()) {
				isLegal = false;
				break;
			}
		
		}
		if (isLegal)
		{
			temp.draw(bluePen, field);
			this->draw(redPen, field);
			field.update();
		}
		else {
			 *this = temp;
		}
	}
};

void Ship::move(DIRECTION direct, Field& field)
{
	Ship updated = *this;

	switch (direct)
	{
	case DIRECTION::DOWN:
		for (auto& i : updated.ship) { i.setY(i.getY() + 1); }
		break;
	case DIRECTION::UP:
		for (auto& i : updated.ship) { i.setY(i.getY() - 1); }
		break;
	case DIRECTION::RIGHT:
		for (auto& i : updated.ship) { i.setX(i.getX() + 1); }
		break;
	case DIRECTION::LEFT:
		for (auto& i : updated.ship) { i.setX(i.getX() - 1); }
		break;
	default:
		break;
	}

	bool isValid = true;
	for (auto& i : updated.ship) {
		if (!i.isValid()) {
			isValid = false;
			break;
		}
	}

	if (isValid)
	{
		this->draw(bluePen, field);
		*this = updated;
		this->draw(redPen, field);
		field.update();
	}

}
Ship::Ship(int size):ship(vector<Cell>(size))
{
	for (int i = 0; i < size;++i)
	{
		ship[i] = Cell(i+1, 1,State::EMPTY);
	}
}

void Ship::placeManualy(Field& field)
{
	draw(redPen, field);

	bool placed = false;
	while (!placed) 
	{
	//	Ship prew = *this;
	//	Ship moved = prew;

		switch (_getwch())
		{
		case 77:   //right
			move(DIRECTION::RIGHT, field);
			break;
		case 75:   //left
			move(DIRECTION::LEFT, field);
			break; 
		case 80:
			move(DIRECTION::DOWN,field);//down
			break;
		case 72:   //up
			move(DIRECTION::UP, field);
			break;
		case 32:
			rotate(field);
			break;
		case 13:
			if (isLegal(field))
			{
				for (auto& i : ship) {
					field.field[i.getX()][i.getY()].setState(State::SHIP);
				}
				placed = true;
			}
			break;
		}
	}
}

bool Ship::placeRandom(Field& field)
{
	int x = rand() % 10 + 1;
	int y = rand() % 10 + 1;

	for (int i = 0; i < ship.size(); i++) {
		ship[i].setX(x + i);
		ship[i].setY(y);
	}

	if (rand() % 2 == 0) {
		rotate(field);
	}


	if (isLegal(field) && ship[ship.size() -1].getX() <= 10) 
	{
		for (auto& i : ship) {
			field.field[i.getX()][i.getY()].setState(State::SHIP);
		}

		field.draw();
		return true;
	}
	
	return false;
}

Cell Ship::getCoord(int index)
{
	return ship[index];
}

vector<Cell> Ship::getCellsAround(Field& field)
{
	 vector<Cell> around;
	 for (auto i : ship) 
	 {
		 around.push_back(field.field[i.getX()][i.getY()]);
			 around.push_back(field.field[i.getX() - 1][i.getY()]);
			 around.push_back(field.field[i.getX() + 1][i.getY()]);
			 around.push_back(field.field[i.getX()][i.getY() - 1]);
			 around.push_back(field.field[i.getX()][i.getY() + 1]);
			 around.push_back(field.field[i.getX() - 1][i.getY() - 1]);
			 around.push_back(field.field[i.getX() - 1][i.getY() + 1]);
			 around.push_back(field.field[i.getX() + 1][i.getY() - 1]);
			 around.push_back(field.field[i.getX() + 1][i.getY() + 1]);
	 }
	 return around;
}

int Ship::getSize()
{
	return ship.size();
}

bool Ship::isLegal(Field& field)
{
	bool isLegal = true;
	for (auto& i : ship) {
		if (field.field[i.getX()][i.getY()].getState() != State::EMPTY ||
		    field.field[i.getX() - 1][i.getY()].getState() != State::EMPTY  ||
		    field.field[i.getX() + 1][i.getY()].getState() != State::EMPTY  ||
			field.field[i.getX()][i.getY() - 1].getState() != State::EMPTY  ||
			field.field[i.getX()][i.getY() + 1].getState() != State::EMPTY  || 
			field.field[i.getX() - 1][i.getY() - 1].getState() != State::EMPTY ||
			field.field[i.getX() - 1][i.getY() + 1].getState() != State::EMPTY || 
			field.field[i.getX() + 1][i.getY() - 1].getState() != State::EMPTY || 
			field.field[i.getX() + 1][i.getY() + 1].getState() != State::EMPTY ) 
		{
			isLegal = false;
			field.field[i.getX()][i.getY()].draw(field.coordX, field.coordY, brightRed);
			
			//break;
		}
	}
	return isLegal;
}
