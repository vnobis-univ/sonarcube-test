#pragma once
#include "View.h"

extern int newScore;

class ResultView : public View
{
public:
	ResultView();

	View* handle();

	void draw();
};

