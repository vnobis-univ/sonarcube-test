#include "Printer.h"
#include "StartView.h"
#include "Console.h"
#include <conio.h>
#include "OptionView.h"
#include "Color.h"

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
	if (language == "Eng")
	{
		setLangToEng();
		options[0] = "Change language";
		options[1] = "Change color";
		options[2] = "Back";
	}
	else if (language == "Ukr")
	{
		setLangToUkr();
		options[0] = "Змiнити мову";
		options[1] = "Змiнити колiр";
		options[2] = "Назад";
	}
}
View* OptionView::handle()
{
	View* nextView = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 80://Down
			selected++;
			if (selected == 3) selected = 2;
			printMenu();
			break;
		case 72://Up
			selected--;
			if (selected == -1) selected = 0;
			printMenu();
			break;
		case 13://Enter
			if (selected == 0)
			{
				if (language == "Eng")
				{
					setLangToUkr();
				}
				else if (language == "Ukr")
				{
					setLangToEng();
				}
				choose = true;
				break;
			}
			else if (selected == 1)
			{
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
				choose = true;
				break;
			}
			else if (selected == 2)
			{
				nextView = new StartView;
				choose = true;
				break;
			}
			else
			{
				exit(0);
			}
		case 27:
			nextView = new StartView;
			choose = true;
			break;
		}
	}
	clean();
	return nextView;
}