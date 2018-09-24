#pragma once
#include "GameField.h"

class GameLogic
{
protected:
	GameField oponentField;

public:
	GameLogic(COORD);

	virtual bool handlePlayerChoice(int, int, bool&, bool&) = 0;

	virtual bool handleOponentChoice(GameField&, bool&) = 0;

	virtual bool isOnlineJoinedGame() const = 0;

	virtual int getScore();

	virtual bool connectToGame();

	void handleMove(int, int, bool);
};

