#pragma once
#include "View.h"
#include "Game.h"
#include "GameLogic.h"

class GameView: public Game, public View
{
	GameLogic gameLogic;
public:
	GameView();

	void draw();

	View* handle();

private:
	void drawWhenLose();

	void handleNoWordsSituation();
};

