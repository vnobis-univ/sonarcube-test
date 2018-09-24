#pragma once

#include "View.h"

using namespace std;

class ResultView : public View
{
	PlayerData p;
public:

	ResultView(PlayerData = PlayerData());

	void draw();

	View* handle();
};