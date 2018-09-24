#pragma once
#include "View.h"
#include "FieldView.h"
#include "HighScoresView.h"
#include <fstream>
class ResulView : public View
{
public:
	void draw();
	View * handle();
};

