#pragma once
#include "View.h"
#include "Printer.h"
#include "Navigation.h"

class OptionsView : public View
{
	enum class HighlightedELement
	{
		language,
		difficulty,
		color,
		back
	};

	static int numberOfEmptyLines;

	HighlightedELement highlightedElement;

public:
	OptionsView();

	void draw();

	View* handle();

private:
	void drawLanguage();

	void drawDifficulty();

	void drawColor();

	void drawBack();

	void handleUpDownMove(HighlightedELement, HighlightedELement);

	void handleRightLeftMove(HighlightedELement, Button);

	void handleDifficulty(HighlightedELement, Button);

	void handleLanguage(HighlightedELement, Button);

	void handleColor(HighlightedELement, Button);
};

