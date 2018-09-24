#pragma once
#include <string>
#include "View.h"
#include "Utils.h"
#include "Field.h"
#include "Levels.h"

using std::string;


class Result:public View
{

private:
	int currentScore;
	LevelState state;
	bool achieved;
	void printMen();


public:
	Result(int m_currentScore, LevelState lvl, Language m_lang);
	

	void draw();
	View* handle();

};
