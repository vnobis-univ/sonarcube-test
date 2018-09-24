#pragma once
#include "View.h"
#include "HighscoresView.h"

class ResultView : public View
{
	bool isAchieve;
	short score;
public:
	ResultView(bool, short);
	void draw();
	View* handle();
	string getName();
};