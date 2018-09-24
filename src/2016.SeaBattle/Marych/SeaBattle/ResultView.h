#pragma once
#include "View.h"

class ResultView : public View
{
	bool isAchieve;
	short score;
	bool isWin;
public:
	ResultView(bool, int, bool);
	string getName();
	void draw();
	View* handle();
};
