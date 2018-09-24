#pragma once
#include "View.h"
#include "GlobalVar.h"

class HighScoreView : public View
{
public:
	HighScoreView();
	void draw();
	View * handle();
};