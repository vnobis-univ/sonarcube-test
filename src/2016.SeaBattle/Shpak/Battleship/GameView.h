#pragma once
#include "View.h"
#include "GameField.h"
#include "GameLogic.h"

class GameView: public View
{
	enum class moveDirection;

	GameField playerField;

	GameLogic* gameLogic;

public:
	GameView(bool, bool = 0);

	~GameView();

	void draw();

	View* handle();

private:
	bool handleShipPlacement();

	bool handleOneShip(int);

	void showNewShipPosition(int, int, int, int, int, GameField::Direction, GameField::Direction);

	bool isOkayToMakeMove(int, int);

	bool isOkayToMakeMove(int, int, int, GameField::Direction);

	bool handleGame();

	bool handlePlayerChoice(int, int, bool&);
};

