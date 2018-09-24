#include "Printer.h"
#include "StartView.h"
#include "Console.h"
#include <conio.h>
#include "ChooseComplexView.h"
#include "Color.h"
#include "HelpView.h"
#include "Complexity.h"

Printer selectedMenu3(Color::LIGHT_RED, Color::BLACK);

ChooseComplexView::ChooseComplexView() : selected(0) {}

void ChooseComplexView::printMenu()
{
	for (int i = 0; i < 3; ++i)
	{
		int pos = 3 * i;
		i == selected ? printAtCenterOfLine(pos + 15, options[i], selectedMenu3) :
			printAtCenterOfLine(pos + 15, options[i], defaultPrinter);
	}
}
void ChooseComplexView::draw()
{
	setOptions();
	View::draw();
	printMenu();
}
void ChooseComplexView::setOptions()
{
	if (language == "Eng")
	{
		setLangToEng();
		options[0] = "Hard";
		options[1] = "Medium";
		options[2] = "Easy";
	}
	else if (language == "Ukr")
	{
		setLangToUkr();
		options[0] = "Тяжкий";
		options[1] = "Середнiй";
		options[2] = "Легкий";
	}
}
View* ChooseComplexView::handle()
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
				parseStrToComplexity(options[0]);
				nextView = new HelpView;
				choose = true;
				break;
			}
			else if (selected == 1)
			{
				parseStrToComplexity(options[1]);
				nextView = new HelpView;
				choose = true;
				break;
			}
			else if (selected == 2)
			{
				parseStrToComplexity(options[2]);
				nextView = new HelpView;
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