#pragma once
#include "View.h"
#include "Lokalization.h"
#include "HighscoresView.h"

extern Complexity compl;

class ResultView : public View
{
	Lokalization language;
	Complexity complexity;
	bool isAchieve;
	short score;
public:
	ResultView(Lokalization, Complexity, bool, short);
	void draw();
	View* handle();
	string codeComplexityToStr(Complexity);
	string getName();
};