#include "Game.h"



void GameAllocationView::displayShip(Ship ship, FrameState frame, CellState cell)
{
	switch ((int)ship.orient)
	{
	case 0:
		for (int i = ship.head.x; i > ship.head.x - ship.length; --i)
		{
			drawCell(330, Coordinate(i, ship.head.y), frame, rPlayer.isHereShips(i, ship.head.y) ? CellState::ShipLocation : cell);

		}
		break;

	case 1:
		for (int i = ship.head.y; i > ship.head.y - ship.length; --i)
		{
			drawCell(330, Coordinate(ship.head.x, i), frame, rPlayer.isHereShips(ship.head.x, i) ? CellState::ShipLocation : cell);
		}
		break;
	}
}

void GameAllocationView::drawScribles()
{
	string scrible = translater.getName("Ships located");
	int pos = 40 - scrible.length() / 2 - 2;
	setCursor(pos, 2);
	cout << scrible << ": " << rPlayer.getCount() << endl;

	scrible = translater.getName("Press H/V (eng) to make ship horizontal/vertical");
	pos = 40 - scrible.length() / 2;
	setCursor(pos, 19);
	cout << scrible << endl;
}

void GameAllocationView::drawShips()
{
	for (int i = 0; i < rPlayer.getCount(); ++i)
	{
		displayShip(rPlayer[i], FrameState::Simple, CellState::ShipLocation);
	}
	drawScribles();
}

void GameAllocationView::drawGameField()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			drawCell(330, Coordinate(i, j), FrameState::Simple);
		}
	}
	drawScribles();
}

View* GameAllocationView::end()
{
	return new GamePreview(rPlayer);
}

GameAllocationView::GameAllocationView(realPlayer& player) :
rPlayer(player)
{
}

void GameAllocationView::draw()
{
	clear();
	drawFrame();
	drawGameField();
}

View* GameAllocationView::handleInput()
{
	while (rPlayer.getCount() != 10)
	{
		currShip = rPlayer[rPlayer.getCount()];
		int count = rPlayer.getCount();
		while (count == rPlayer.getCount())
		{
			drawShips();
			if (rPlayer.canBePlaced(currShip))
			{
				displayShip(currShip);
			}
			else
			{
				displayShip(currShip, FrameState::Intersected);
			}
			rPlayer[rPlayer.getCount()] = currShip;
			Button but = getButton(possibleButtons, 8);
			int hor = currShip.head.x; //hor - horizontal
			int vert = currShip.head.y; //ver - vertical
			switch (but)
			{
			case Button::UP:
				vert--;
				break;
			case Button::DOWN:
				vert++;
				break;
			case Button::LEFT:
				hor--;
				break;
			case Button::RIGHT:
				hor++;
				break;
			case Button::H:
				displayShip(currShip, FrameState::Simple);
				if (currShip.length - 1 > currShip.head.x)
				{
					rPlayer[rPlayer.getCount()].head = Coordinate(currShip.length - 1, currShip.head.y);
				}
				rPlayer[rPlayer.getCount()].orient = Orientation::Horizontal;
				currShip = rPlayer[rPlayer.getCount()];
				break;
			case Button::V:
				displayShip(currShip, FrameState::Simple);
				if (currShip.length - 1 > currShip.head.y)
				{
					rPlayer[rPlayer.getCount()].head = Coordinate(currShip.head.x, currShip.length - 1);
				}
				rPlayer[rPlayer.getCount()].orient = Orientation::Vertical;
				currShip = rPlayer[rPlayer.getCount()];
				break;
			case Button::ENTER:
				if (rPlayer.canBePlaced(currShip))
				{
					rPlayer.placeTheShip(currShip);
					break;
				}
			}
			if (hor >= (currShip.orient == Orientation::Horizontal ? currShip.length - 1 : 0) && hor < 10)
			{
				displayShip(currShip, FrameState::Simple);
				currShip.head.x = hor;
			}
			if (vert >= (currShip.orient == Orientation::Vertical ? currShip.length - 1 : 0) && vert < 10)
			{
				displayShip(currShip, FrameState::Simple);
				currShip.head.y = vert;
			}
		}

	}
	drawShips();
	return end();
}

GameAllocationView::~GameAllocationView()
{
	delete[] possibleButtons;
}