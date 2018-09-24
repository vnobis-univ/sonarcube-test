#include <vector>
#include <conio.h>
#include <iostream>
#include "Navigation.h"
#include "StartView.h"
#include "HighscoresView.h"
#include "FieldView.h"


StartView::StartView() : selectedOption(startOptions::start) {}

void StartView::drawOption(startOptions optionToDraw)
{
	std::string option;

	// getting how to draw
	switch (optionToDraw)
	{
	case startOptions::start:
		option = "START";
		break;

	case startOptions::highscores:
		option = "HIGHSCORES";
		break;

	case startOptions::exit:
		option = "EXIT";
	}

	// changing if selected
	Printer printerOption;

	if (optionToDraw == selectedOption)
	{
		option.insert(0, "*  ");
		option.insert(option.length(), "  *");

		printerOption = Printer(Color::lightAqua, Color::black);
	}
	else
	{
		printerOption = Printer(Color::aqua, Color::black);
	}

	drawAtCenter(option, printerOption);
}

void StartView::draw() 
{
	View::draw();
	View::drawBackground();

	for (size_t i = 0; i < optionsSize; ++i)
	{
		drawEmptyLines(5);

		drawOption(static_cast<startOptions> (i));
	}
}

View* StartView::getNextView() const
{
	switch (selectedOption)
	{
	case startOptions::start:
		return new FieldView();
		break;

	case startOptions::highscores:
		return new HighscoresView();
		break;

	case startOptions::exit:
		exit(1);
	}
}

View* StartView::handle()
{
	View* nextView = this;
	Button button;

	while (true)
	{
		// until one of possible buttons is not presed continue loop
		if (!getWhichButton(button))
			continue;

		switch (button)
		{
		case Button::UP: //key up
			if (selectedOption == startOptions::start) break;
			selectedOption = (startOptions)(int(selectedOption) - 1);
			break;

		case Button::DOWN: //key down
			if (selectedOption == startOptions::exit) break;
			selectedOption = (startOptions)(int(selectedOption) + 1);
			break;

		case Button::ENTER: // key enter
			nextView = getNextView();
			break;

		default:
			continue;
		}


		return nextView;
	}
	
}
