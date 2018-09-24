#pragma once
#include "Player.h"
#include "View.h"
class HighScoresView :public View
{
	static const int size = 10;
	Player arrayOfPlayers[size];
public:
	HighScoresView(Languages l, TypeOfGame t);
	void draw();
	View* handle();
};

