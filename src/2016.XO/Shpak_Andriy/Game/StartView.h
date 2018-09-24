#pragma once
#include "View.h"

class StartView : public View
{
	enum class startOptions
	{
		start,
		highscores,
		exit
	};

	const int optionsSize = 3;
	startOptions selectedOption;

public:
	StartView();

	View* getNextView() const;

	View* handle();

	void drawOption(startOptions);

	void draw();
};

