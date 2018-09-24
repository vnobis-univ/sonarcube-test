#pragma once
#include "View.h"

class ResultView : public View
{
	unsigned currentScore;
	bool achievedHScore;

	void updateScores(string name, int score);
public:
	ResultView(unsigned scores);
	virtual void draw();
	virtual View* handle();
};
