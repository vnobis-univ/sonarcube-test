#include "Printer.h"
#include "StartView.h"
#include "Console.h"
#include <conio.h>
//#include "FieldView.h"
#include "HighScoreView.h"
#include "OptionView.h"
#include "Color.h"
#include "ChooseComplexView.h"

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
	if (language == "Eng")
	{
		setLangToEng();
		options[0] = "New Game";
		options[1] = "High Scores";
		options[2] = "Options";
		options[3] = "Exit";
	}
	else if (language == "Ukr")
	{
		setLangToUkr();
		options[0] = "Нова Гра";
		options[1] = "Результати";
		options[2] = "Параметри";
		options[3] = "Вихiд";
	}
}
View* StartView::handle()
{
	View* nextView = this;
	bool choose = false;
	while (!choose)
	{
		switch (_getch())
		{
		case 80://Down
			selected++;
			if (selected == 4) selected = 3;
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
				nextView = new ChooseComplexView;
				choose = true;
				break;
			}
			else if (selected == 1)
			{
				nextView = new HighscoreView;
				choose = true;
				break;
			}
			else if (selected == 2)
			{
				nextView = new OptionView;
				choose = true;
				break;
			}
			else
			{
				exit(0);
			}
		case 27:
			exit(0);
		}
	}
	clean();
	return nextView;
}
