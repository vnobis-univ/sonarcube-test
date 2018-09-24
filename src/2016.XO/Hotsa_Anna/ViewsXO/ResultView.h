#pragma once
#include "View.h"

class ResultView:public View
{
private:
	int score;
public:
	ResultView();
	ResultView(int score1);
	bool hasAchievedHighscore();
	void draw();
	View* handle();
};