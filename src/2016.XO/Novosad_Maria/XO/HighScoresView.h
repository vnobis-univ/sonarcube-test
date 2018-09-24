#pragma once
#include "View.h"
#include "Player.h"

class HighScoresView: public View
{
public:
	HighScoresView();
	void draw();
	View* handle();
};

