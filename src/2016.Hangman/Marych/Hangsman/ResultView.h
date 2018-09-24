#pragma once
#include "View.h"

class ResultView : public View
{
	bool isAchieve;
	short score;
	int life;
public:
	ResultView(bool, short, int);
	string getName();
	void draw();
	View* handle();
};
