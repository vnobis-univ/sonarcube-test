#pragma once
#include "View.h"
#include "Navigation.h"
#include "LanguageManipulator.h"

class HighscoresView : public View
{
	Language choosenLanguage;

public:
	HighscoresView();

	void draw();

	View* handle();

private:
	void drawMainRow(Language = LanguageManipulator().getGameLanguage());

	void drawLines();

	void drawDifficultyNames();

	void drawResults(Language = LanguageManipulator().getGameLanguage());

	void drawHighscoresFooter();

	void clearTable();

	void handleRightLeftMove(Button);
};

