#include "Game.h"

void GameBattleView::drawEnemyStrikes()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (enemy->isHereStrikes(i, j) && rPlayer.isHereShips(i, j))
			{
				drawCell(530, Coordinate(i, j), FrameState::Simple, CellState::RightHit);
			}
			else if (enemy->isHereStrikes(i, j) && !rPlayer.isHereShips(i, j))
			{
				drawCell(530, Coordinate(i, j), FrameState::Simple, CellState::WrongHit);
			}
		}
	}
}

void GameBattleView::drawCoord()
{
	if (rPlayer.isHereStrikes(currCoord.x, currCoord.y) && enemy->isHereShips(currCoord.x, currCoord.y))
		drawCell(130, currCoord, FrameState::Intersected, CellState::RightHit);
	else if (rPlayer.isHereStrikes(currCoord.x, currCoord.y) && !enemy->isHereShips(currCoord.x, currCoord.y))
		drawCell(130, currCoord, FrameState::Intersected, CellState::WrongHit);
	else drawCell(130, currCoord, FrameState::Chosen);
}

void GameBattleView::drawPlayerStrikes()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (rPlayer.isHereStrikes(i, j) && enemy->isHereShips(i, j))
			{
				drawCell(130, Coordinate(i, j), FrameState::Simple, CellState::RightHit);
			}
			else if (rPlayer.isHereStrikes(i, j) && !enemy->isHereShips(i, j))
			{
				drawCell(130, Coordinate(i, j), FrameState::Simple, CellState::WrongHit);
			}
		}
	}
	drawCoord();
}

void GameBattleView::drawFields()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			drawCell(130, Coordinate(i, j), FrameState::Simple);
			if (rPlayer.isHereShips(i, j))
			{
				drawCell(530, Coordinate(i, j), FrameState::Simple, CellState::ShipLocation);
			}
			else
			{
				drawCell(530, Coordinate(i, j), FrameState::Simple);
			}
		}
	}
	drawCoord();
}

Ship GameBattleView::findShip(Coordinate coord, int length, int orient)
{
	switch (orient)
	{
	case 0:
		for (int i = coord.x; i < coord.x + length + 1; ++i)
		{
			if (!enemy->isHereShips(i, coord.y))
			{
				i--;
				return Ship(i, coord.y, length, (Orientation)orient);
			}
		}
	case 1:

		for (int i = coord.y; i < coord.y + length + 1; ++i)
		{
			if (!enemy->isHereShips(coord.x, i))
			{
				i--;
				return Ship(coord.x, i, length, (Orientation)orient);
			}
		}
	}
}

void GameBattleView::drawScribles()
{
	printAtMiddle(translater.getName("Your score is:") + " " + to_string(rPlayer.getScore()) + "   "
		+ translater.getName("Enemy ships destroyed:") + " " + to_string(10 - enemy->getCount()) + "   "
		+ translater.getName("Your ships alive:") + " " + to_string(rPlayer.getCount()) + " ", 2, Printer(Color::lRed));
}

Coordinate GameBattleView::userStep(string answer)
{
	while (true)
	{
		if (answer == "Hit")
		{
			rPlayer.setScore(rPlayer.getScore() + 20);
			drawScribles();
			answer = "Miss";
		}
		if (answer[0] == 'K')
		{
			switch (answer[4])
			{
			case '1':
				rPlayer.setScore(rPlayer.getScore() + 100);
				break;
			case '2':
				rPlayer.setScore(rPlayer.getScore() + 60);
				break;
			case '3':
				rPlayer.setScore(rPlayer.getScore() + 50);
				break;
			case '4':
				rPlayer.setScore(rPlayer.getScore() + 40);
				break;
			}
			drawScribles();
			Ship ship = findShip(currCoord, answer[4] - 48, answer[5] - 48);
			answer = "Miss";
			rPlayer.enemyShipDestroyed(ship);
			drawPlayerStrikes();
		}
		Button but = getButton(possibleButtons, 6);
		int hor = currCoord.x; //hor - horizontal
		int vert = currCoord.y; //vert - vertical
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
		case Button::ENTER:
			if (!rPlayer.isHereStrikes(currCoord.x, currCoord.y))
			{
				rPlayer.shot(currCoord);
				return currCoord;
			}
			break;
		case Button::ESC:
			rPlayer.shot(Coordinate(-1, -1));
			return Coordinate(-1, -1);
			break;
		}
		drawCell(130, currCoord, FrameState::Simple);
		if (hor >= 0 && hor < 10)
		{
			currCoord.x = hor;
		}
		if (vert >= 0 && vert < 10)
		{
			currCoord.y = vert;
		}
		drawPlayerStrikes();
	}
}

View* GameBattleView::end()
{
	if (rPlayer.getCount() == 0 && enemy->getCount() != 0)
	{
		drawResult(false);
		wait();
		return new ResultView(rPlayer.getScore());
	}
	else if (rPlayer.getCount() != 0 && enemy->getCount() == 0)
	{
		drawResult(true);
		wait();
		return new GameAllocationView(realPlayer(rPlayer.getScore()));
	}
	else
	{
		drawEnd();
		wait();
		return new ResultView(rPlayer.getScore());
	}
}

void GameBattleView::drawEnd()
{
	clear();
	drawFrame();
	printAtMiddle(translater.getName("You or your enemy refused to continue game, press enter to exit..."), 11, Printer(Color::dRed));
}

void GameBattleView::drawResult(bool win)
	{
	clear();
	drawFrame();
	!win ? printAtMiddle(translater.getName("You lost, press enter to exit..."), 11, Printer(Color::dRed)) :
		printAtMiddle(translater.getName("You won, press enter to continue..."), 11, Printer(Color::dRed));
	printAtMiddle(translater.getName("Your score is: ") + to_string(rPlayer.getScore()), 12, Printer(Color::dRed));
}

bool GameBattleView::isEnd(string answ)
{
	if (rPlayer.getCount() == 0 || enemy->getCount() == 0 || answ == "End")
	{
		return true;
	}
	return false;
}

GameBattleView::GameBattleView(realPlayer& player) :
	rPlayer(player)
{
	if (player.getOpt() == GameOptions::Single)
	{
		enemy = new computerPlayer(rPlayer);
	}
	else
	{
		enemy = new OnlinePlayer();
	}
}

void GameBattleView::draw()
{
	clear();
	drawFrame();
	drawFields();
	drawScribles();
}

View* GameBattleView::handleInput()
{
	string answ;
	enemy->join(rPlayer.getId());
	while (true)
	{
		if (rPlayer.getMode() == OnlineModes::Join)
		{
			printAtMiddle(translater.getName("Your enemies turn now, please wait"), 19, Printer(Color::dBlue));
			answ = rPlayer.answer(enemy->shot());
			if (isEnd(answ)) return end();
			drawEnemyStrikes();
			while (answ != "Miss")
			{
				answ = rPlayer.answer(enemy->shot());
				drawEnemyStrikes();
				if (isEnd(answ)) return end();
			}
		}
		drawScribles();
		printAtMiddle("             " + translater.getName("Your turn now...") + "             ", 19, Printer(Color::dBlue));
		answ = enemy->answer(userStep());
		if (isEnd(answ)) return end();
		drawPlayerStrikes();
		while (answ != "Miss")
		{
			answ = enemy->answer(userStep(answ));
			if (isEnd(answ)) return end();
			drawPlayerStrikes();
		}
		if (rPlayer.getMode() == OnlineModes::Create)
		{
			printAtMiddle(translater.getName("Your enemies turn now, please wait"), 19, Printer(Color::dBlue));
			answ = rPlayer.answer(enemy->shot());
			drawEnemyStrikes();
			while (answ != "Miss")
			{
				answ = rPlayer.answer(enemy->shot(answ));
				if (isEnd(answ)) return end();
				drawEnemyStrikes();
			}
		}
		drawScribles();
	}
}

GameBattleView::~GameBattleView()
{
	delete[] possibleButtons;
}