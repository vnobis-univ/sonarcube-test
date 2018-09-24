#include "Field.h"
#include "Utils.h"
#include "Ship.h"
#include "Cell.h"
#include <string>
using namespace std;

Ship& Field::getShipAt(int x, int y)
{
	Ship& ship = crew[0];

	for (int i = 0; i < crew.size(); i++) {
		for (int j = 0; j < crew[i].getSize(); j++)
		{
			if (crew[i].getCoord(j).getX() == x && crew[i].getCoord(j).getY() == y) {
				return crew[i];
			}
		}
	}

	return ship;
}

Field::Field(int _x, int _y): coordX(_x), coordY(_y), crew(vector<Ship>(10))
{
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 12; j++) {
			field[i][j] = Cell(i, j, State::EMPTY);
		}
	}

	// creating ships
	crew[0] = Ship(4);
	crew[1] = Ship(3);
	crew[2] = Ship(3);
	for (int i =3 ; i < 6; ++i)
	{
		crew[i] = Ship(2);
	}
	for (int i = 6; i < 10; ++i)
	{
		crew[i] = Ship(1);
	}
}

void Field::draw()
{
	for (int i = 0; i < 12; i++) {
		field[11][i].draw(coordX, coordY, blackPen);
		field[i][11].draw(coordX, coordY, blackPen);
	}

	for (int i = 1; i<11; i++) {
		for (int j = 1; j < 11; j++) {
				field[i][j].draw(coordX,coordY, bluePen);
			}
	}

}

void Field::positioningPlayer()
{
	for (auto& i : crew)
	{
		i.placeManualy(*this);
	}
	
}

void Field::positioningComp()
{
	for (auto& i : crew) {
		bool placed = false;
		while (!placed) {
			placed = i.placeRandom(*this);
		}
	}
}

void Field::makeMovePlayer(int& count, int& playerScores)
{
	bool done = false;
	Cell selected(1, 1);
	

	State state;

	while (!done) {
		
		Cell previous = selected;
		selected.draw(coordX, coordY, greenPen);

		switch (_getwch())
		{
		case 77:   //right
			selected.setX(selected.getX() + 1);
			break;
		case 75:   //left
			selected.setX((selected.getX() - 1));
			break;
		case 80:
			selected.setY((selected.getY() + 1));//down
			break;
		case 72:   //up
			selected.setY((selected.getY() - 1));
			break;
		case 13:
			state = field[selected.getX()][selected.getY()].getState();
			
			if ( state == State::EMPTY || state == State::SHIP) {			

				if (state == State::SHIP) 
				{
					Ship& ship = getShipAt(selected.getX(), selected.getY());

					field[selected.getX()][selected.getY()].drawCross(coordX, coordY, redPen);
					field[selected.getX()][selected.getY()].setState(State::DAMAGED);
					

					bool killed = true;


					for (int i = 0; i < ship.getSize(); i++)
					{
						if (field[ship.getCoord(i).getX()][ship.getCoord(i).getY()].getState() != State::DAMAGED)
						{
							
							killed = false;
							
							
							//break;
						}
					}

					if (killed) {
						for (auto& i : ship.getCellsAround(*this)) {
							
							if (i.isValid() && field[i.getX()][i.getY()].getState() == State::EMPTY) {
								field[i.getX()][i.getY()].setState(State::DOT);
								field[i.getX()][i.getY()].drawDot(coordX, coordY, bluePen);
							}
										
					   }

						count--;

						if (count == 0) 
						{
							return;
						}
					}
				}

				if (state == State::EMPTY) 
				{
					field[selected.getX()][selected.getY()].drawDot(coordX, coordY, bluePen);
					field[selected.getX()][selected.getY()].setState(State::DOT);
					done = true;
					if (playerScores > 0)
					{
						--playerScores;
					}
				}
			}
			break;
		default:
		//	lightAquaOnBlack.printOnCenter(4, "DEF");
			break;
		}

		if (selected.isValid())
		{
			previous.draw(coordX, coordY, bluePen);
			selected.draw(coordX, coordY, greenPen);
		}
		else {
			selected = previous;
		}
		//update();
	}

}

void Field::makeMoveGPU(int& count, int _x, int _y)
{

	int x = _x;
	int y = _y;


	bool done = false;
	while (!done)
	{
		while (field[x][y].getState() == State::DAMAGED || field[x][y].getState() == State::DOT
			|| field[x][y].getState() == State::KILLED)
		{
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
		}

		if (field[x][y].getState() == State::SHIP)
		{
			field[x][y].drawCross(coordX, coordY, redPen);
			field[x][y].setState(State::DAMAGED);

			Ship& ship = getShipAt(x, y);

			bool killed = true;

			for (int i = 0; i < ship.getSize(); i++)
			{
				if (field[ship.getCoord(i).getX()][ship.getCoord(i).getY()].getState() != State::DAMAGED)
				{
					killed = false;
					break;
				}
			}

			if (killed)
			{
				for (auto& i : ship.getCellsAround(*this))
				{
					if (i.isValid() && field[i.getX()][i.getY()].getState() == State::EMPTY)
					{
						field[i.getX()][i.getY()].setState(State::DOT);
						field[i.getX()][i.getY()].drawDot(coordX, coordY, bluePen);
					}
				}
				count--;

				if (count == 0)
				{
					return;
				}

				makeMoveGPU(count, 4, 4);
			}

		}

		if (field[x][y].getState() == State::EMPTY)
		{
			done = true;
			field[x][y].drawDot(coordX, coordY, redPen);
			field[x][y].setState(State::DOT);
		}
	}
	
}

void Field::update()
{
	for (int i = 1; i < 11; ++i)
	{
		for (int j = 1; j < 11; ++j)
		{
			if (field[i][j].getState() == State::SHIP)
			{
				field[i][j].draw(coordX, coordY, redPen);
			}
		}
	}
}
