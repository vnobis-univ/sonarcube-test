#pragma once
#include "View.h"
#include "string"

using std::string;
using std::endl;
using std::cout;

enum class LevelState{ EASY, MEDIUM, HARD};


class Levels : public View
{
	const string levels[3] = { " Easy ", " Medium ", " Hard " };
	const string ukr_levels[3] = { " Легкий "," Середній "," Важкий " };
	int selected;

	void printLevels();

public:

	Levels(Language m_lang = Language::ENG);

	virtual void draw();
	virtual View* handle();


};



