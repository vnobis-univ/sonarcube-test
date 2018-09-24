#pragma once
#include "View.h"

class ResultView : public View
{
private:
	int score;
	bool hasAchievedHighscore();
public:
	ResultView();
	ResultView(int score);
	int getScore();
	void draw();
	View* handle();
	
};

