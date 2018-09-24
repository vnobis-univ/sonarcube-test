#include "Printer.h"
#include "StartView.h"
#include "Console.h"
#include <conio.h>
#include "OptionView.h"
#include "Color.h"
#include "Language.h"

Printer selectedMenu1(Color::LIGHT_RED, Color::BLACK);

OptionView::OptionView() : selected(0) {}

void OptionView::printMenu()
{
	for (int i = 0; i < 3; ++i)
	{
		int pos = 3 * i;
		i == selected ? printAtCenterOfLine(pos + 15, options[i], selectedMenu1) :
			printAtCenterOfLine(pos + 15, options[i], defaultPrinter);
	}
}
void OptionView::draw()
{
	setOptions();
	View::draw();
	printMenu();
}
void OptionView::setOptions()
{
	setOptionForOptionMenu(options);
}
View* OptionView::getNextAction(int selectedOpt)
{
	View* view = NULL;
	switch (selectedOpt)
	{
	case 0://option is to change a language
		view = new OptionView;
		if (language == Language::ENGLISH)
		{
			setLangToUkr();
		}
		else if (language == Language::UKRAINIAN)
		{
			setLangToEng();
		}
		break;
	case 1://option is to change a color
		view = new OptionView;
		if (defaultPrinter == Printer(Color::LIGHT_BLUE, Color::BLACK)
			&& defaultPrinterBg == Printer(Color::BLACK, Color::LIGHT_BLUE))
		{
			defaultPrinter = Printer(Color::LIGHT_GREEN, Color::BLACK);
			defaultPrinterBg = Printer(Color::BLACK, Color::LIGHT_GREEN);
		}
		else if (defaultPrinter == Printer(Color::LIGHT_GREEN, Color::BLACK)
			&& defaultPrinterBg == Printer(Color::BLACK, Color::LIGHT_GREEN))
		{
			defaultPrinter = Printer(Color::LIGHT_BLUE, Color::BLACK);
			defaultPrinterBg = Printer(Color::BLACK, Color::LIGHT_BLUE);
		}
		break;
	case 2://return to start view
		view = new StartView;
		break;
	}
	return view;
}
View* OptionView::handle()
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
			nextView = getNextAction(selected);
			choose = true;
			break;
		case Button::ESC:
			nextView = new StartView;
			choose = true;
			break;
		}
		if (selected < 0)
		{
			selected = 0;
		}
		else if (selected > 2)
		{
			selected = 2;
		}
		printMenu();
	}
	clean();
	return nextView;
}