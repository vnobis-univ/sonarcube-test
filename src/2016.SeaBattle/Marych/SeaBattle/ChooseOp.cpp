#include "FieldView.h"
#include "GameLogic.h"
#include "Console.h"

Printer selectedMenu4(Color::LIGHT_RED, Color::BLACK);

ChooseOp::ChooseOp() : selected(1) {}
ChooseOp::ChooseOp(Status** scheeme) : selected(1)
{
	for (size_t i = 0; i < 10; i++)
	{
		schemee[i] = new Status[10];
		for (size_t j = 0; j < 10; j++)
		{
			schemee[i][j] = scheeme[i][j];
		}
	}
}

void ChooseOp::printMenu()
{
	printAtCenterOfLine(7, options[0], defaultPrinter);
	for (int i = 1; i < 4; ++i)
	{
		int pos = 4 * i;
		i == selected ? printAtCenterOfLine(pos + 11, options[i], selectedMenu4) :
			printAtCenterOfLine(pos + 11, options[i], defaultPrinter);
	}
}
void ChooseOp::draw()
{
	setOptions();
	View::draw();
	printMenu();
}

void ChooseOp::setOptions()
{
	setOptionForGameMenu(options);
}
View* ChooseOp::getNextView1(int selectedOpt)
{
	View* view = NULL;
	switch (selectedOpt)
	{
	case 1://option is GameComputer
		view = new GameComputer(schemee);
		break;
	case 2://option is GameComputer
		view = new GameComputer(schemee);
		break;
	case 3:
		//to exit a game view should be NULL
		break;
	}
	return view;
}
View* ChooseOp::handle()
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
			nextView = getNextView1(selected);
			choose = true;
			break;
		case Button::ESC:
			exit(0);
		}
		if (selected < 1)
		{
			selected = 1;
		}
		else if (selected > 3)
		{
			selected = 3;
		}
		printMenu();
	}

	return nextView;
}