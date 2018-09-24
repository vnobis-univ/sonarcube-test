#pragma once

#include "View.h"

class HighScoreView : public View
{
public:
	HighScoreView();

	void draw();

	View* handle();
};