#pragma once

#include "View.h"

using namespace std;

class ResultView : public View
{
	Player p;
public:

	ResultView(Player = Player());

	void draw();

	View* handle();
};