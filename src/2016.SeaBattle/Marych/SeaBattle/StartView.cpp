#include "StartView.h"
#include "Console.h"
#include <conio.h>
#include "FieldView.h"
#include "HighScoreView.h"
#include "OptionView.h"
#include "Color.h"

Printer selectedMenu(Color::LIGHT_RED, Color::BLACK);

StartView::StartView() : selected(0) {}
void StartView::printMenu()
{
	for (int i = 0; i < 4; ++i)
	{
		int pos = 4 * i;
		i == selected ? printAtCenterOfLine(pos + 11, options[i], selectedMenu) :
			printAtCenterOfLine(pos + 11, options[i], defaultPrinter);
	}
}
void StartView::draw()
{
	setOptions();
	View::draw();
	printMenu();
}
void StartView::setOptions()
{
	setOptionForStartMenu(options);
}
View* getNextView(int selectedOpt)
{
	View* view = NULL;
	switch (selectedOpt)
	{
	case 0://option is New Game
		view = new FieldView;
		break;
	case 1://option is High Score
		view = new HighscoreView;
		break;
	case 2://option is Option
		view = new OptionView;
		break;
	case 3:
		//to exit a game view should be NULL
		break;
	}
	return view;
}
View* StartView::handle()
{
	View* nextView = this;
	Button button;
	bool choose = false;
	while (!choose)
	{
		button = getNavigationAction(allowedButtons, allowedButtonsSize);
		switch (button)
		{
		case Button::UP:
			selected--;
			break;
		case Button::DOWN:
			selected++;
			break;
		case Button::ENTER:
			nextView = getNextView(selected);
			choose = true;
			break;
		case Button::ESC:
			exit(0);
		}
		if (selected < 0)
		{
			selected = 0;
		}
		else if (selected > 3)
		{
			selected = 3;
		}
		printMenu();
	}

	return nextView;
}