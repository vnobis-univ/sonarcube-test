#pragma once
#include "View.h"
#include "scores.h"
#include <fstream>

class HightScoresView :public View
{
	vector<hightScore> vec;

	void readScores();	
public:
	HightScoresView();

	virtual void draw();
	virtual View* handle();
};